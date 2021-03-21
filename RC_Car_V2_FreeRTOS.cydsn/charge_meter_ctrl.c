/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "charge_meter_ctrl.h"
#include "i2c_ctrl.h"
#include "project.h"
#include "utilities.h"
#include "data.h"
#include "led_ctrl.h"


#define CMD_DATA    (0x01)
#define WR_BUF_SIZE (1u)

#define HIGH_TH     (80u)
#define LOW_TH      (40u)


/* Sets up pointers to charger i2c index */ 
i2c_requests_t* charger_requests = &i2c_requests[CHARGER_ID];


void charge_meter_setup(void)
{
    uint8 chgr_wr_buf[WR_BUF_SIZE] = {CMD_DATA};
    
    request_buffer[CHARGER_ID] = FALSE;
    
    charger_requests->device_addr = CHARGER_ADDR;
    memcpy(charger_requests->wr_buff, chgr_wr_buf, sizeof(chgr_wr_buf));  // Sets the write buffer
    charger_requests->wr_len = sizeof(chgr_wr_buf);  // Sets the write length 
}


static uint8 i2c_cheksum_calc(meter_data_t *buffer)
{    
    uint16 packet_sum = 0;
    uint8 cheksum_buff[sizeof(i2c_meter_data_t)];
    
    memcpy(&cheksum_buff, buffer, sizeof(i2c_meter_data_t));
    
    for(uint8 i = 0; i < sizeof(meter_data_t); i++)
    {
        packet_sum += cheksum_buff[i];
    }
    
    if((packet_sum & 0xFF) == i2c_meter_data.cheksum)
        return TRUE;
    else return FALSE;
}


static void battery_monitor_read(void)
{    
    if(request_buffer[CHARGER_ID] == TRUE)
        return;
    
    memcpy(&i2c_meter_data, charger_requests->rd_buff, sizeof(i2c_meter_data_t));
    uint8 checksum_status = i2c_cheksum_calc(&i2c_meter_data.charge_data);

    if(checksum_status)
        tx_data.charge_level = i2c_meter_data.charge_data.charge_level;
    
    /* Set the buffer to request data */
    request_buffer[CHARGER_ID] = TRUE;
}


void battery_monitor_process(void)
{   
    battery_monitor_read();
    
    /* Light the corresponding LED based on the battery voltage level */
    if(tx_data.charge_level >= HIGH_TH)
    {
        led_sel(LED_GREEN_1, TRUE);
        led_sel(LED_YELLOW, FALSE);
        led_sel(LED_RED, FALSE);
    }
    else if(tx_data.charge_level >= LOW_TH && tx_data.charge_level < HIGH_TH)
    {
        led_sel(LED_GREEN_1, FALSE);
        led_sel(LED_YELLOW, TRUE);
        led_sel(LED_RED, FALSE);
    }
    else if(tx_data.charge_level < LOW_TH)
    {
        led_sel(LED_GREEN_1, FALSE);
        led_sel(LED_YELLOW, FALSE);
        led_sel(LED_RED, TRUE);
    }
}

/* [] END OF FILE */

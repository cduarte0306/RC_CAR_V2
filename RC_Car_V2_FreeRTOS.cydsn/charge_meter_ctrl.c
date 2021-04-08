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

#include "stdbool.h"


#define CMD_DATA    (0x01)
#define WR_BUF_SIZE (1u)

#define HIGH_TH     (80u)
#define LOW_TH      (40u)


/* Sets up pointers to charger i2c index */ 
i2c_requests_t* charger_requests = &i2c_parameters[CHARGER_ID];

static bool has_entered_low;
static bool has_entered_mid;
static bool has_entered_high;


void charge_meter_setup(void)
{
    uint8 chgr_wr_buf[WR_BUF_SIZE] = {CMD_DATA};    
    charger_requests->device_addr = CHARGER_ADDR;
    memcpy(charger_requests->wr_buff, chgr_wr_buf, sizeof(chgr_wr_buf));  // Sets the write buffer
    charger_requests->wr_len = sizeof(chgr_wr_buf);  // Sets the write length 
    charger_requests->rd_len = sizeof(i2c_meter_data_t);
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
    memcpy(&i2c_meter_data, &charger_requests->rd_buff, sizeof(i2c_meter_data_t));
    uint8 checksum_status = i2c_cheksum_calc(&i2c_meter_data.charge_data);

    if(checksum_status)
        tx_data.charge_level = i2c_meter_data.charge_data.charge_level;
    
    /* Set the buffer to request data */
    i2c_add_queue(REQ_CHARGER);
}


void battery_monitor_process(void)
{   
    battery_monitor_read();
    
    /* Light the corresponding LED based on the battery voltage level */
    if(tx_data.charge_level >= HIGH_TH)
    {
        if(has_entered_high)
            return;

        has_entered_low = false;
        has_entered_mid = false;
        has_entered_high = true;

        led_add_queue(LED_GREEN_1, TRUE);
        led_add_queue(LED_YELLOW, FALSE);
        led_add_queue(LED_RED, FALSE);
    }
    else if(tx_data.charge_level >= LOW_TH && tx_data.charge_level < HIGH_TH)
    {
        if(has_entered_mid)
            return;

        has_entered_low = false;
        has_entered_mid = true;
        has_entered_high = false;

        led_add_queue(LED_GREEN_1, FALSE);
        led_add_queue(LED_YELLOW, TRUE);
        led_add_queue(LED_RED, FALSE);
    }
    else if(tx_data.charge_level < LOW_TH)
    {
        if(has_entered_low)
            return;

        has_entered_low = true;
        has_entered_mid = false;
        has_entered_high = false;

        led_add_queue(LED_GREEN_1, FALSE);
        led_add_queue(LED_YELLOW, FALSE);
        led_add_queue(LED_RED, TRUE);
    }
}

/* [] END OF FILE */

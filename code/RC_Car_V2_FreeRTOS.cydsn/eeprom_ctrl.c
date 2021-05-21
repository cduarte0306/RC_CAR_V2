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

#include "eeprom_ctrl.h"
#include "project.h"
#include "data.h"
#include "utilities.h"


/* Space to define EEPROM addresses. The following variables 
   will be stored:
   Kp (proportional gain)
   Ki (Integral gain)
   Kd (Derivative gain) */
#define KP_ADDR     (*(void)(CYDEV_EE_BASE + ADDR_OFFSET + 16*0))
#define KI_ADDR     (*(void)(CYDEV_EE_BASE + ADDR_OFFSET + 16*1))
#define KD_ADDR     (*(void)(CYDEV_EE_BASE + ADDR_OFFSET + 16*2))

#define EEPROM_ARRAY_SIZE   (3u)

#define SAVE_KP     (0u)
#define SAVE_KI     (1u)
#define SAVE_KD     (2u)


/* Defines the array of values to be stored. The array size is defined as 4
   since the EEPROM rows are 16-bytes wide and floats are 4 bytes */
static float kp_array[4];
static float ki_array[4];
static float kd_array[4];

static uint8 last_cmd = 0;


void eeprom_load_values(void)
{
    
}


void eeprom_init(void)
{
    EEPROM_Start();
    eeprom_load_values();
    tx_data.eeprom_flag = FALSE;
}


static uint8 save_kp(void)
{
    //memcpy(kp_array, &rx_data.pid_calib.kp, sizeof(rx_data.pid_calib.kp));

    uint8 ret = EEPROM_Write((uint8*)kp_array, 16 * 0);
    if(ret == CYRET_LOCKED)  // Write to row 0 on EEPROM
        return TRUE;
    else return FALSE;
}


static uint8 save_ki(void)
{
    //memcpy(kp_array, &rx_data.pid_calib.ki, sizeof(rx_data.pid_calib.ki));

    uint8 ret = EEPROM_Write((uint8*)ki_array, 16 * 1);
    if(ret == CYRET_LOCKED)  // Write to row 1 on EEPROM
        return TRUE;
    else return FALSE;
}


static uint8 save_kd(void)
{
    //memcpy(kp_array, &rx_data.pid_calib.kd, sizeof(rx_data.pid_calib.kd));

    uint8 ret = EEPROM_Write((uint8*)kd_array, 16 * 0);
    if(ret == CYRET_LOCKED)  // Write to row 0 on EEPROM
        return TRUE;
    else return FALSE;
}


void eeprom_process(unsigned char kx)
{
    /* Only enter the function once per call */
    if((rx_data.cmd & SAVE_BIT) == last_cmd)
        return;

    /* Plan for failure */
    tx_data.eeprom_flag = FALSE;

    if(kx == SAVE_KP)
        tx_data.eeprom_flag = save_kp();
    else if(kx == SAVE_KI)
        tx_data.eeprom_flag = save_ki();
    else if(kx == SAVE_KD)
        tx_data.eeprom_flag = save_kd();
        
    last_cmd = (rx_data.cmd & SAVE_BIT);

        
}

/* [] END OF FILE */

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

#ifndef CHARGE_METER_CTRL_H
#define CHARGE_METER_CTRL_H

#include <cytypes.h>
       
    
typedef struct __attribute__((__packed__))  /* Defining incoming data structure   */
{
    uint8 charge_level;
} meter_data_t;
  
typedef struct __attribute__((__packed__))  /* Defining incoming data structure   */
{
    meter_data_t charge_data;
    uint8 cheksum;
} i2c_meter_data_t;

meter_data_t meter_data;
i2c_meter_data_t i2c_meter_data;


void battery_monitor_process(void);
void charge_meter_setup(void);

#endif
/* [] END OF FILE */

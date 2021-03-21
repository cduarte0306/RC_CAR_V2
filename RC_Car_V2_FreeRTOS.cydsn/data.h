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

#ifndef DATA_H
#define DATA_H
    
#include <cytypes.h>
#include "utilities.h"

    
/* Defining GPS macros */
#define MSG_SIZE  (80u)

/* Defining cmd bits */
#define SAVE_BIT    0b001
#define CRS_BIT     0b010


/* The following values will be used to calibrate the PID controller
   form the GUI. Values will come from the transmitter and stored 
   upon reception of the SAVE command */
typedef struct __attribute__((__packed__))
{
    float kp;
    float ki;
    float kd;
    float theta;
} pid_calib_t;
        

/* Defining incoming data structure   */
typedef struct __attribute__((__packed__))
{
    uint16 motor;
    uint16 servo;
    uint8 drive_mode_bits;
    uint8 speed_set;
    pid_calib_t pid_calib;
    uint8 cmd;
} rx_data_t;


typedef struct __attribute__((__packed__))
{
    uint8 speed;
    float front_distance;
    float right_distance;
    float left_distance;
    uint16 x_axis;
    uint16 y_axis;
    uint16 z_axis;
    uint8 gngga_msg[MSG_SIZE];
    uint8 charge_level;
    uint8 eeprom_flag;
} tx_data_t;


typedef struct __attribute__((__packed__))
{
    uint8 speed;
    uint16 front_distance_msb;
    uint16 right_distance;
    uint16 left_distance;
    uint16 x_axis;
    uint16 y_axis;
    uint16 z_axis_lsb;
    uint8 gngga_msg[MSG_SIZE];
} tx_data_jetson;


typedef struct __attribute__((__packed__))
{
    uint16 steer_angle;
    uint16 speed;
} rx_data_jetson;
    

rx_data_t rx_data;  
tx_data_t tx_data;
tx_data_t tx_jetson;
rx_data_jetson rx_jetson;
    
#endif

/* [] END OF FILE */

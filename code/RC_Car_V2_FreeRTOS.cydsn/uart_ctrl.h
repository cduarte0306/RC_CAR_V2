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
#ifndef UART_CTRL_H
#define UART_CTRL_H
    
#include <cytypes.h>
#include "data.h"
    
    
#define RX_MESSAGE_NUM      (9u)
#define START_DELIM         (0x7E)
#define CR                  '\r'
#define LF                  '\n'

#define NO_OP        (0u)  // No operation
#define MOTOR_CMD    (1u)  // Motor direction command
#define CALIB_CMD    (2u)  // Calibration command
#define SET_MODE_CMD (3u)  // Mode setting command


typedef struct __attribute__((__packed__))
{
    uint16 motor;
    uint16 servo;
} drive_cmd_t;


typedef struct __aatribute__((__packed__))
{
    uint8 cmd;
    
} calib_cmd_t;


typedef struct __attribute__((__packed__))
{
    uint32 key;
    uint32 firmware_version;
} metadata_t;


/* The following struct serves to define the cmd and end of message structs */
typedef struct __attribute__((__packed__))
{
    uint8 uart_cmd;
    uint8* cmd_pointer;
    metadata_t metadata;
} rx_cmd_struct_t;
    
    
typedef struct __attribute__((__packed__))  /* Defining structure for data out */
{
    uint8 start_byte;
    tx_data_t data_out;
    uint8 cheksum;
    uint8 line_feed;
    uint8 carriage_return;
} uart_buff_data_out_t;


typedef struct __attribute__((__packed__))  /* Defining structure for data out */
{
    rx_cmd_struct_t rx_cmd_struct;
    uint8 line_feed
    uint8 carriage_return;
} uart_buff_data_in_t;


uart_buff_data_out_t uart_buff_data_out;
uart_buff_data_in_t uart_buff_data_in;

    
//void uart_receive_data(void);
void uart_init();
void uart_process();
void uart_send_data();
    
#endif

/* [] END OF FILE */

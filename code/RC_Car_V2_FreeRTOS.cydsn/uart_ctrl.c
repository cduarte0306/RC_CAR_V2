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

#include <project.h>
#include "uart_ctrl.h"
#include "data.h"
#include "utilities.h"
#include "led_ctrl.h"
#include "stdbool.h"


#define TIMEOUT     2000u


static uint8 rx_index = 0;  // Circular buffer index
static uint8 tx_buffer[sizeof(uart_buff_data_out_t)];
static uint8 rx_data_buffer[sizeof(uart_buff_data_in_t)];
static uint8 cheksum_buff[sizeof(rx_data_t)];
static uint8 cheksum_in;
static uint8 packet_ok = 0;
static uint8 msg_status = 0;

static bool has_been_set_high;
static bool has_been_set_low;


CY_ISR(rx_handler)
{    
    rx_data_buffer[rx_index] = UART_Radio_RXDATA_REG;  // Read from UART register
    
    if(rx_data_buffer[rx_index] == START_DELIM)  
    {
        rx_index = 0;  // Sets the rx_index to 0 in the case of a start byte detected
    }
        
    if(rx_data_buffer[rx_index] == CR && rx_index == sizeof(uart_buff_data_in_t) - 1u)
    {
        packet_ok = TRUE;
    }
    else
    {
        rx_index++;
        
        if(rx_index >= sizeof(uart_buff_data_in_t)) 
            rx_index = 0;
    }
    
    rx_isr_ClearPending();  // Clears the ISR to continue with normal operation
}


void uart_init(void)
{
    /* Specify the start and end bytes */
    uart_buff_data_out.start_byte = START_DELIM;
    uart_buff_data_out.end_char = CR;
    
    rx_isr_Start();
    rx_isr_StartEx(rx_handler);
}

  
static uint8 cheksum_in_calc( rx_data_t* buffer)
{
    uint16 packet_sum_in = 0;  // Resets to 0 on every entry
    memcpy(&cheksum_buff, buffer, sizeof(rx_data_t));
    
    for(uint8 i = 0; i < sizeof(rx_data_t); i++)
    {
        /* Calculate the sum of all bytes received */
        packet_sum_in += cheksum_buff[i];
    }
    
    if((packet_sum_in & 0xFF) == uart_buff_data_in.cheksum)  /* Function checks if the cheksum equals the value at the buffer index */
        return TRUE;
    else return FALSE;
}


// Function calculates the cheksum sent out by the receiver
static void cheksum_out_calc( tx_data_t* buffer )
{       
    uint16 packet_sum_out = 0;  // Resets to 0 on every entry
    uint8 checksum_calc_buff[sizeof(tx_data_t)];
    
    memcpy(&checksum_calc_buff, buffer, sizeof(tx_data_t));
    
    /* Calculate the sum of all bytes transmitted */
    for(uint8 i = 0; i < sizeof(tx_data_t); i ++)
    {
        packet_sum_out += checksum_calc_buff[i];
    }
        
    uart_buff_data_out.cheksum = (packet_sum_out & 0xFF);
}


static void uart_unpack_data(void)
{
    if(packet_ok == FALSE)
        return;
    
    // The incoming data is placed in the UART buffer for pre-processing before it is placed into the main data  
    memcpy(&uart_buff_data_in, &rx_data_buffer, sizeof(uart_buff_data_in_t));  // Addressign is subject to change, might have to remove the &
    cheksum_in = cheksum_in_calc(&uart_buff_data_in.data_in); 
    
    if(cheksum_in ==  TRUE)
    {
        memcpy(&rx_data, &uart_buff_data_in.data_in, sizeof(rx_data_t));
        UART_Radio_ClearRxBuffer();
        
        if(!has_been_set_high)
        {
            led_add_queue(LED_BLUE, TRUE);
            has_been_set_high = true;
            has_been_set_low = false;
        }
    }
    
    msg_status = FALSE;
    packet_ok = FALSE;
}


void uart_send_data()
{
    memcpy(&uart_buff_data_out.data_out, &tx_data, sizeof(tx_data));
    cheksum_out_calc(&uart_buff_data_out.data_out); // Populates the checksum member with the calculated checksum
    
    // Use mcmcpy to copy the contents of one memory location onto another
    memcpy(&tx_buffer, &uart_buff_data_out, sizeof(uart_buff_data_out_t));
    UART_Radio_PutArray(tx_buffer, sizeof(uart_buff_data_out_t));
    
    // Clears the contents of the tx buffer once the FIFO is empty
    UART_Radio_ClearTxBuffer();
        
    return;
}


void uart_process(void)
{
    static uint32 time_out;
    uart_unpack_data();
    
    if(!msg_status)
        time_out ++;
    else 
        time_out = 0;
    
    if(time_out > TIMEOUT)
    {
        if(!has_been_set_low)
        {
            led_add_queue(LED_BLUE, FALSE);    
            has_been_set_low = true;
            has_been_set_high = false;
        }
        
        time_out = 0;
    }
}


/* [] END OF FILE */

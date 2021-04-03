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

#include "project.h"
#include "led_ctrl.h"
#include "utilities.h"
#include "i2c_ctrl.h"

// FreeRTOS libraies
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#define WR_BUFF_SIZE    (2u)
#define CMD_SIZE        (6)

#define QUEUE_SIZE      (4u)


// /* LED request queue setup */
// typedef struct node
// {
//     uint8 value;
//     struct node *next;
// } node;


// typedef struct
// {
//     node* head;
//     node* tail;
// } queue;


typedef struct
{
    uint8 data*;  // Buffer
    uint8 count;               // Elements present on the queue
    uint8* head;               // Pointer to the head of the queue
    uint8* tail;               // Pointer to the tail of the queue
} buff_t;

typedef struct
{
    uint8 field;
} queue_t;

queue_t queue[QUEUE_SIZE];

/* Set up pointer to the i2c controller buffer */
i2c_requests_t* led_i2c_param = &i2c_parameters[LED_ID];
buff_t* buff;


static void init_queue(void)
{
    buff->count = 0;

    /* Initialize the head and tail pointers. Points to the first element of the array */
    buff->head = buff->data;
    buff->tail = buff->data;

    memset(queue, 0, sizeof(queue));
}


static void led_sel(uint8 led, uint8 status)
{
    switch(led)
    {        
        case NO_COM:
            break;
       
        case LED_GREEN_1: 
            I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            uint8 stat = I2C_MasterStatus();
            while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            
            break;
        
        case LED_YELLOW:            
            I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            
            while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            
            break;
        
        case LED_RED:    
            I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            
            while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            
            break;
        
        case LED_BLUE: 
            I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            
            while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            
            break;
            
        case LED_GREEN_2:
            I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            
            while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            
            break;
    }
    
    I2C_MasterClearStatus();
}


/* Setup the led peripheral */
void led_setup( void )
{
    uint8 setup_commands[CMD_SIZE] = 
    {
        0x00, 0x00,
        0x0C, 0xFF,
        0x0D, 0xFF
    };
    uint8 wr_buff[WR_BUFF_SIZE];

    uint8 index = 0;

    for(uint8 i = 0; i < sizeof(setup_commands); i ++)
    {
        index ++;
        if(index != 2)
            continue;

        index = 0;
        wr_buff[0] = setup_commands[i - 1];
        wr_buff[1] = setup_commands[i];

        I2C_MasterWriteBuf(LED_ADDR, led_buffer, WR_BUFF_SIZE, I2C_MODE_COMPLETE_XFER);
        while(0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
    }

    /* Initialize queue */
    init_queue();
}


void led_process(void)
{   
    /* If the queue is empty, then do not enter */
    if(buff.count == 0)
        return;

    /* Pull the next request from the queue */
    queue_t* field = (*queue_t)pull_queue_req();
}


/* Submit a request to the queue */
void uint8 led_enqueue(uint8 field)
{
    if(buff.count >= QUEUE_SIZE)
        return QUEUE_FULL;

    

    buff_ptr -> data[buff_ptr->count] = field;
    buff_ptr -> count++;
    buff_ptr -> head = 
}

/* [] END OF FILE */

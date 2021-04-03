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
#include "queue_ctrl.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#define WR_BUFF_SIZE    (2u)
#define CMD_SIZE        (6)

#define QUEUE_SIZE      (4u)


typedef struct
{
    uint8 field;
} led_req_t;

led_req_t req_queue[QUEUE_SIZE];
queue_t led_queue;

/* Set up pointer to the i2c controller buffer */
i2c_requests_t* led_i2c_param = &i2c_parameters[LED_ID];


static void led_sel(uint8 led)
{
    switch(led)
    {        
        case NO_COM:
            break;
       
        case LED_GREEN_1:   
                      
            break;
        
        case LED_YELLOW:               
            break;
        
        case LED_RED:

            break;
        
        case LED_BLUE:

            break;
            
        case LED_GREEN_2:
            break;

        case default:
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

        I2C_MasterWriteBuf(LED_ADDR, wr_buff, WR_BUFF_SIZE, I2C_MODE_COMPLETE_XFER);
        while(0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
    }

    /* Initialize queue */
    queue_init(&led_queue, QUEUE_SIZE, req_queue);
}


void led_process(void)
{   
    /* If the queue is empty, then do not enter */
    if(queue_empty(&led_queue))
        return;

    /* Pull the next request from the queue */
    led_req_t* led_req = (led_req_t*)queue_get_exec(&led_queue, sizeof(led_req_t));
    led_sel(led_req);

    queue_inc_exec_ptr(&led_queue);
}


/* Submit a request to the queue */
void uint8 led_enqueue(uint8 field)
{
    if(buff.count >= QUEUE_SIZE)
        return QUEUE_FULL;

    
}

/* [] END OF FILE */

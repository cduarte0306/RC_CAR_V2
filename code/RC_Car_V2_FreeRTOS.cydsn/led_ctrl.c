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
#define CMD_SIZE        (6u)
#define SUB_CMD         (2u)

#define QUEUE_SIZE      (10u)


/* Selects the led to turn on and the level */
typedef struct
{
    uint8 field;
    uint8 scale;
} led_req_t;

static led_req_t req_queue[QUEUE_SIZE];
static queue_t led_queue;

/* Set up pointer to the i2c controller buffer */
static i2c_requests_t* led_i2c_param = &i2c_parameters[LED_ID];


static void led_sel(uint8 led, uint8 scale)
{
    switch(led)
    {        
        case NO_COM:
            break;
       
        case LED_GREEN_1:   
            led_i2c_param->wr_buff[0] = LED_GREEN_1_ADDR;
            led_i2c_param->wr_buff[1] = (scale == TRUE) ? FULL_SCALE : 0;    

            break;
        
        case LED_YELLOW:   
            led_i2c_param->wr_buff[0] = LED_YELLOW_ADDR;
            led_i2c_param->wr_buff[1] = (scale == TRUE) ? FULL_SCALE : 0;            
            break;
        
        case LED_RED:
            led_i2c_param->wr_buff[0] = LED_RED_ADDR;
            led_i2c_param->wr_buff[1] = (scale == TRUE) ? FULL_SCALE : 0;
            break;
        
        case LED_BLUE:
            led_i2c_param->wr_buff[0] = LED_BLUE_ADDR;
            led_i2c_param->wr_buff[1] = (scale == TRUE) ? FULL_SCALE : 0;
            break;
            
        case LED_GREEN_2:
            led_i2c_param->wr_buff[0] = LED_GREEN_2_ADDR;
            led_i2c_param->wr_buff[1] = (scale == TRUE) ? FULL_SCALE : 0;
            break;

        default:
            break;
    }
    
    i2c_add_queue(REQ_LED);
}


/* Setup the led peripheral */
void led_setup( void )
{
    uint8 setup_commands[CMD_SIZE][SUB_CMD] = 
    {
        {0x00, 0x00},
        {0x0C, 0xFF},
        {0x0D, 0xFF}
    };

    uint8 wr_buff[WR_BUFF_SIZE];

    // uint8 index = 0;

    for(uint8 i = 0; i < sizeof(CMD_SIZE); i ++)
    {
        wr_buff[0] = setup_commands[i][0];
        wr_buff[1] = setup_commands[i][1];

        I2C_MasterWriteBuf(LED_ADDR, wr_buff, WR_BUFF_SIZE, I2C_MODE_COMPLETE_XFER);
        while(0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
    }

    led_i2c_param->device_addr = LED_ADDR;
    led_i2c_param->wr_len = WR_BUFF_SIZE;
    
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
    led_sel(led_req->field, led_req->scale);

    queue_inc_exec_ptr(&led_queue);
}


/* Submit a request to the queue */
void led_add_queue(uint8 field, uint8 scale)
{
    led_req_t* led_req = (led_req_t*)queue_get_req(&led_queue, sizeof(led_req_t));
    led_req->field = field;
    led_req->scale = scale;

    queue_inc_req_ptr(&led_queue);
}

/* [] END OF FILE */

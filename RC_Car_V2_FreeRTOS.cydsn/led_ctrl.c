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

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#define WR_BUFF_SIZE    (2u)
#define CMD_SIZE        (6)


/* LED request queue setup */
typedef struct node
{
    uint8 value;
    struct node *next;
} node;


typedef struct
{
    node* head;
    node* tail;
} queue;

i2c_parameters_t led_i2c_param = &i2c_parameters[LED_ID];


static void init_queue(queue *q)
{
    q -> head = NULL;
    q -> tail = NULL;
}


static bool enqueue(queue *q, uint8 value)
{
    /* Allocate memory for new node */
    node* newnode = malloc(sizeof(node));

    if(newnode == NULL)

        return FALSE;
    newnode -> value = value;

    /* The next points to NULL since the new value goes to the end of 
       the list and it will not have anything after */
    newnode -> value = NULL;

    if(q ->tail != NULL)
    {
        q -> tail -> next = newnode;
    }

    q -> tail = newnode;

    /* If this is the first value, the head will also be equal to the new node */
    if(q -> head == NULL)
    {
        q -> head = newnode;
    }

    return TRUE;
}


static uint8 dequeue(queue* q)
{
    /* If there are no values left in the queue, return */
    if(q -> head == NULL)
        return FALSE;

    node *tmp = q -> head;
    int result = tmp -> value;

    /* Pop off */
    q -> head = q -> head -> next;
    if(q -> head == NULL)
    {
        q -> tail = NULL;
    }

    free(tmp);
    return result;

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


void led_process(void)
{
}

/* [] END OF FILE */

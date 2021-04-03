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
#include "i2c_ctrl.h"
#include "utilities.h"
#include "queue_ctrl.h"


#define REQ_BUFF_SIZE  (10u)


typedef struct
{
    uint8 field;
} i2c_req_t;

i2c_req_t req_queue[REQ_BUFF_SIZE];
queue_t i2c_queue;


static void i2c_led_update(void)
{
    I2C_MasterWriteBuf( i2c_parameters[LED_ID].device_addr,
                        i2c_parameters[LED_ID].wr_buff, 
                        i2c_parameters[LED_ID].wr_len,
                        I2C_MODE_COMPLETE_XFER
    );

    while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
}


static void i2c_charger_update(void)
{
    /* Wait if there is a trasnfer in progress */
    while(1u == (I2C_MasterStatus() & I2C_MSTAT_XFER_INP)){};
    
    /* Write data to slave */
    I2C_MasterWriteBuf( i2c_parameters[CHARGER_ID].device_addr, 
                        i2c_parameters[CHARGER_ID].wr_buff, 
                        i2c_parameters[CHARGER_ID].wr_len, 
                        I2C_MODE_NO_STOP
    );
    
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT)){};
    
    /* Read incoming data from charger monitor */
    I2C_MasterReadBuf( i2c_parameters[CHARGER_ID].device_addr,
                       i2c_parameters[CHARGER_ID].rd_buff,
                       i2c_parameters[CHARGER_ID].rd_len,
                       I2C_MODE_REPEAT_START);

    while (0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT)){};
}


static void perform_process(uint8 field)
{
    switch(field)
    {
        case REQ_LED:
            i2c_led_update();
            break;
        
        case REQ_CHARGER:
            i2c_charger_update();
            break;

        case REQ_ACCELEROMETER:
            //i2c_accelerometer_update();
            break;

        default:
            break;
    }
}


void init_i2c(void)
{
    /* Initialize queue */
    queue_init(&i2c_queue, REQ_BUFF_SIZE, req_queue);
}


/* To be called on main I2C process */
void i2c_process(void)
{   
    /* If the queue is empty, then do not enter */
    if(queue_empty(&i2c_queue))
        return;

    /* Pull the next request from the queue */
    i2c_req_t* i2c_req = (i2c_req_t*)queue_get_exec(&i2c_queue, sizeof(i2c_req_t));
    perform_process(i2c_req->field);

    queue_inc_exec_ptr(&i2c_queue);
}


/* Submit a request to the queue */
void i2c_add_queue(uint8 field)
{
    i2c_req_t* i2c_req = (i2c_req_t*)queue_get_req(&i2c_queue, sizeof(i2c_req_t));
    i2c_req->field = field;

    queue_inc_req_ptr(&i2c_queue);
}

/* [] END OF FILE */

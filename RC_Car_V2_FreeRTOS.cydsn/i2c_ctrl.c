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


#define REQ_BUFF_SIZE  (10u)


/* Define the size of the queue buffer */
static uint8 queue_buffer[REQ_BUFF_SIZE];
static uint8 is_queue_empty = FALSE;
static int8 queue_index = 0;


static void process_queue(void);


/* Function reads from slave */
static void i2c_buffer_read(uint8 slave_addr, uint8* wr_buff, uint8 wr_size, uint8* read_buffer, uint8 read_size )
{
    /* Wait if there is a trasnfer in progress */
    while(1u == (I2C_MasterStatus() & I2C_MSTAT_XFER_INP)){};
    
    /* Write data to slave */
    I2C_MasterWriteBuf(slave_addr, wr_buff, wr_size, I2C_MODE_NO_STOP);
    
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT)){};
    
    I2C_MasterReadBuf(slave_addr, read_buffer, read_size, I2C_MODE_REPEAT_START); /* Returns status of read  */
    
    while (0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT)){};
}


/* Function writes to slave */
static void i2c_buffer_write(uint8 slave_addr, uint8 *wr_buff, uint8 num_bytes)
{
    /* Wait while I2C is busy */
    while(1u == (I2C_MSTAT_XFER_INP & I2C_MasterStatus()))

    I2C_MasterWriteBuf(slave_addr, wr_buff, num_bytes, I2C_MODE_COMPLETE_XFER);
            
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
}


static void perform_process(uint8 field)
{

}


/* To be called on main I2C process */
void i2c_process(void)
{ 
    /* Check if there are any requests */
    if(is_queue_empty)
        return;

    process_queue();
}


/* Process queue requests and empy queue space. Shift index */
static void dequeue(void)
{
    uint8 request = queue_buffer[queue_index];
    queue_index = queue_index < 0 ? 0 : queue_index --;  // Decrease index
    perform_process(request);
}


/* This fucntion is to be called when submitting a request */
void queue_req(uint8 field)
{
    queue_buffer[queue_index] = field;  // Place the request in the buffer
    queue_index++;  // Increase queue index for every request
}

/* [] END OF FILE */

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

#include "accelerometer_ctrl.h"
#include "data.h"
#include "i2c_ctrl.h"
#include "project.h"

#define SETUP_RD_BUFF   (1u)
#define SETUP_WR_BUFF   (1u)


/* Sets up pointer to accelerometer i2c index */
i2c_requests_t* accelerometer_requests = &i2c_parameters[ACCELEROMETER_ID];


/* This fucntion requests the device ID in order to perform a handshake */
static uint8 accelerometer_request_id(void)
{
    uint8 wr_buff[SETUP_RD_BUFF] = {0x0D};
    uint8 id_rd_buff[SETUP_RD_BUFF] = {0};

     /* Wait if there is a transfer in progress */
    while(1u == (I2C_MasterStatus() & I2C_MSTAT_XFER_INP)){};

    /* Write data to slave */
    uint8 err_ret = I2C_MasterWriteBuf(ACCELEROMETER_ADDR, 
                        wr_buff, 
                        sizeof(wr_buff), 
                        I2C_MODE_NO_STOP
    );
    
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT)){};
    
    /* Read incoming data from charger monitor */
    err_ret = I2C_MasterReadBuf(ACCELEROMETER_ADDR,
                       id_rd_buff,
                       sizeof(id_rd_buff),
                       I2C_MODE_REPEAT_START);

    while (0u == (I2C_MasterStatus() & I2C_MSTAT_RD_CMPLT)){};
    
    return TRUE;
}


void accelerometer_setup(void)
{
    uint8 ret = accelerometer_request_id();
    // accelerometer_requests->device_addr = ACCELEROMETER_ADDR;
}

/* [] END OF FILE */

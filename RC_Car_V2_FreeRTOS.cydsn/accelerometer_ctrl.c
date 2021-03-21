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


/* Sets up pointer to accelerometer i2c index */
i2c_requests_t* accelerometer_requests = &i2c_requests[ACCELEROMETER_ID];


/* This fucntion requests the device ID in order to perform a handshake */
static uint8 accelerometer_request_id(void)
{
    
}


void accelerometer_setup(void)
{
    accelerometer_requests->device_addr = ACCELEROMETER_ADDR;
}

/* [] END OF FILE */

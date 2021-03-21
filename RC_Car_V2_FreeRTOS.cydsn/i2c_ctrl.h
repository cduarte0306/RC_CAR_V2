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

#ifndef I2C_CTRL_H
#define I2C_CTRL_H
    
#include <cytypes.h>
       
    
#define CHARGER_ADDR        (0x04)
#define LED_ADDR            (0x20)
#define ACCELEROMETER_ADDR  (0x0C)

/* I2C requests index */
#define DEFAULT_REQ         (0u)
#define REQ_LED             (1u)
#define REQ_CHARGER         (2u)
#define REQ_ACCELEROMETER   (3u)
    
#define BUFF_LEN            (10u)  // Maximum buffer length of 80 Bytes (20 words)
#define NUM_REQUESTS        (3u)   // Number of request IDs

    
typedef struct __attribute__((__packed__))  /* Defining incoming data structure   */
{
    uint8 device_addr;
    uint8 wr_buff[BUFF_LEN];
    uint8 rd_buff[BUFF_LEN];
    uint8 wr_len;
    uint8 rd_len;
} i2c_requests_t;

uint8 request_buffer[NUM_REQUESTS + 1u];
i2c_requests_t i2c_requests[NUM_REQUESTS + 1u];

void i2c_process(void);
void queue_req(uint8 field);
    
#endif

/* [] END OF FILE */

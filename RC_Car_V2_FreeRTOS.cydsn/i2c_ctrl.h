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

/* IDs */
#define CHARGER_ID          (1u)
#define LED_ID              (2u)
#define ACCELEROMETER_ID    (3u)

#define NUM_REQUESTS        (3u)   // Number of request IDs
#define BUFF_LEN            (10u)  // Maximum buffer length of 80 Bytes (20 words)

    
typedef struct __attribute__((__packed__))  /* Defining incoming data structure   */
{
    uint8 device_addr;
    uint8 wr_buff[BUFF_LEN];
    uint8 rd_buff[BUFF_LEN];
    uint8 wr_len;
    uint8 rd_len;
} i2c_requests_t;

i2c_requests_t i2c_parameters[NUM_REQUESTS + 1u];


void init_i2c(void);
void i2c_process(void);
void i2c_add_queue(uint8 field);
    
#endif

/* [] END OF FILE */

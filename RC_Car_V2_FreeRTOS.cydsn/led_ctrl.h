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
#ifndef LED_CTRL_H
#define LED_CTRL_H
    
#include <cytypes.h>
    

#define NO_COM           (0u)
#define LED_GREEN_1      (1u)
#define LED_YELLOW       (2u)
#define LED_RED          (3u)
#define LED_GREEN_2      (4u)
#define LED_BLUE         (5u)

#define LED_GREEN_1_ADDR (0x06)
#define LED_YELLOW_ADDR  (0x05)
#define LED_RED_ADDR     (0x04)
#define LED_GREEN_2_ADDR (0x03)
#define LED_BLUE_ADDR    (0x02)

#define FULL_SCALE         (0xFF)
#define OFF                (0x00)

#define QUEUE_AVAILABLE (0x00)
#define QUEUE_FULL      (0x01)
    

void led_setup( void );
void led_process(void);
void led_add_queue(uint8 field, uint8 scale);
    
#endif

/* [] END OF FILE */

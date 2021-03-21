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


#define WR_BUFF_SIZE    (2u)


uint8 led_buffer[WR_BUFF_SIZE] = {0, 0};

void led_setup( void )
{
    led_buffer[0]=0x00;
    led_buffer[1]=0x00;
    
    I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
    
    led_buffer[0]=0x0c;
    led_buffer[1]=0xFF;
    
    I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
    
    led_buffer[0]=0x0d;
    led_buffer[1]=0xFF;
    
    I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
    while(0u == (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
    
    led_buffer[0] = LED_YELLOW_ADDR;
    led_buffer[1] = OFF;
    
    I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            
    while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
}


void led_sel(uint8 led, uint8 status)
{
    static uint8 last_green;
    static uint8 last_yellow;
    static uint8 last_red;
    static uint8 last_blue_1;
    static uint8 last_blue_2;
    
    switch(led)
    {        
        case NO_COM:
            break;
       
        case LED_GREEN_1: 
            if(last_green == status)
                return;
            
            last_green = status;
            
            if(status == TRUE)
            {
            led_buffer[0]=LED_GREEN_1_ADDR;
            led_buffer[1]=FULL_SCALE;   
            }
            else 
            {
                led_buffer[0]=LED_GREEN_1_ADDR;
                led_buffer[1]=OFF;  
            }
            
            I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            uint8 stat = I2C_MasterStatus();
            while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            
            break;
        
        case LED_YELLOW:
            if(last_yellow == status)
                break;
            
            last_yellow = status;
            
            if(status == TRUE)
            {
                led_buffer[0]=LED_YELLOW_ADDR;
                led_buffer[1]=FULL_SCALE;         
            }
            else 
            {
                led_buffer[0] = LED_YELLOW_ADDR;
                led_buffer[1] = OFF;
            }
            
            I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            
            while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            
            break;
        
        case LED_RED:    
            if(last_red == status)
                return;
            
            last_red = status;
            
            if(status == TRUE)
            {
            led_buffer[0]=LED_RED_ADDR;
            led_buffer[1]=FULL_SCALE;   
            }
            else 
            {
                led_buffer[0]=LED_RED_ADDR;
                led_buffer[1]=OFF;  
            }         
            
            I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            
            while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            
            break;
        
        case LED_BLUE: 
            
            if(last_blue_1 == status)
                break;
            
            last_blue_1 = status;
            
            if(status == TRUE)
            {
            led_buffer[0]=LED_BLUE_ADDR;
            led_buffer[1]=FULL_SCALE;   
            }
            else 
            {
                led_buffer[0]=LED_BLUE_ADDR;
                led_buffer[1]=OFF;  
            }
            
            I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            
            while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            
            break;
            
        case LED_GREEN_2:
            if(last_blue_2 == status)
                break;
            
            last_blue_2 = status;
                        
            if(status == TRUE)
            {
                led_buffer[0]=LED_GREEN_2_ADDR;
                led_buffer[1]=FULL_SCALE;            
            }
            else
            {
                led_buffer[0]=LED_GREEN_2_ADDR;
                led_buffer[1]=OFF;
            }
            
            I2C_MasterWriteBuf(LED_ADDR, led_buffer, 2, I2C_MODE_COMPLETE_XFER);
            
            while(0u != (I2C_MasterStatus() & I2C_MSTAT_WR_CMPLT));
            
            break;
    }
    
    I2C_MasterClearStatus();
}

/* [] END OF FILE */

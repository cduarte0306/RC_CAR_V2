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
#define CMD_SIZE        (6)


uint8 led_buffer[WR_BUFF_SIZE] = {0, 0};


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


void led_sel(uint8 led, uint8 status)
{
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

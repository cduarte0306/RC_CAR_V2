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

#include <project.h>
#include "utilities.h"
#include "ultrasonic_ctrl.h"
#include "data.h"


#define COUNTDOWN   (65535u)


void get_distance(int* distance1, int* distance2, int* distance3)
{ 
    /* Front distance (echo 2) */
    /* Reset trigger generator */
    trigger_reset_Write(TRUE);
    
    while(!trigger_reset_Read()){}
    
    trigger_reset_Write(FALSE);
    
    while(trigger_reset_Read()){}
    
    /* Wait for all echos to be low and start generator */
    while(echo_2_Read() == FALSE)
    {
        PWM_trigger_Start();
    }
    
    /* Stop trigger generator and read */
    PWM_trigger_Stop(); 
    
    while(echo_2_Read()){}
    
    *distance2 = COUNTDOWN - Timer_echo_2_ReadCounter();
    
    /* Right distance (echo 3) */
    trigger_reset_Write(TRUE);
    
    while(!trigger_reset_Read()){}
    
    trigger_reset_Write(FALSE);
    
    while(trigger_reset_Read()){}
    
    /* Wait for all echos to be low and start generator */
    while(echo_3_Read() == FALSE)
    {
        PWM_trigger_Start();
    }
    
    /* Stop trigger generator and read */
    PWM_trigger_Stop(); 
    
    while(echo_3_Read()){}
    
    *distance3 = COUNTDOWN - Timer_echo_3_ReadCounter();
    
    /* Left distance */
    trigger_reset_Write(TRUE);
    
    while(!trigger_reset_Read()){}
    
    trigger_reset_Write(FALSE);
    
    while(trigger_reset_Read()){}
    
    /* Wait for all echos to be low and start generator */
    while(echo_1_Read() == FALSE)
    {
        PWM_trigger_Start();
    }
    
    /* Stop trigger generator and read */
    PWM_trigger_Stop(); 
    
    while(echo_1_Read()){}
    
    *distance1 = COUNTDOWN - Timer_echo_1_ReadCounter();    
}


/* [] END OF FILE */

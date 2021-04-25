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
    /* Wait while all inputs are high, if not, read the timer register */    
    while(echo_2_Read()){}
    
    *distance2 = COUNTDOWN - Timer_echo_2_ReadCounter();
    
    while(echo_3_Read()){}
    
    *distance3 = COUNTDOWN - Timer_echo_3_ReadCounter();
    
    while(echo_1_Read()){}
    
    *distance1 = COUNTDOWN - Timer_echo_1_ReadCounter();    
}


/* [] END OF FILE */

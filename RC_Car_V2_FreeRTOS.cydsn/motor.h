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
#ifndef MOTOR_H
#define MOTOR_H
    
#include <cytypes.h> 
    

#define MOTOR_FORWARD_TH        (540u)
#define MOTOR_REVERSE_TH        (400u)
#define MOTOR_MAX               (900u)
#define SERVO_TH_LOW            (1400u)
#define SERVO_TH_HIGH           (1600u)


void motor_setup(void);
void motor_process(void);
    
#endif

/* [] END OF FILE */

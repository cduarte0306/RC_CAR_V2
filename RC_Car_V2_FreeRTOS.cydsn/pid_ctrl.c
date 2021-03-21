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
#include "pid_ctrl.h"
#include "utilities.h"
#include "data.h"

float proportional;
float integral;
float derivative;
float last_der;
float p_i_d;
float error;


void pid( uint16 speed )
{
    error = speed - tx_data.speed;

    /* Calculated proportional, integral, and derivatives */
    proportional = error * KP;
    integral += error * KI;
    derivative = (error - last_der) * KD;

    last_der = derivative;
    p_i_d = proportional + integral;// + derivative;
    p_i_d = bound(0, p_i_d, PID_MAX);  // FUnction bounds the PID output between 0 and the defined MAX
    
    /* Typecast value onto the PWM driver register */
    CY_SET_REG16(PWM_Motor_COMPARE1_LSB_PTR, (uint16) p_i_d);
}

/* [] END OF FILE */

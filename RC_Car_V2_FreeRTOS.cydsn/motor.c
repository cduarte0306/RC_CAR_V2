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
#include "motor.h"
#include "utilities.h"
#include "pid_ctrl.h"
#include "led_ctrl.h"
#include "rc_car.h"
#include "data.h"


#define SPEED_PLUS     0x02
#define SPEED_MINUS    0x04

#define MOTOR_DEFAULT  (500u)


static uint16 speed_set;


void motor_setup(void)
{
    rx_data.motor = MOTOR_DEFAULT;
}


static void motor(void)
{    
    uint16 forward;
    uint16 reverse;
    
    if(rx_data.motor > MOTOR_FORWARD_TH)
    {
        PWM_Motor_Start();
        PWM_Motor_WriteCompare2(0);  // Both shall not be on at the same time
        forward = (1000/460)*rx_data.motor - (1000/460)*540;
        forward = (forward >= MOTOR_MAX) ? (forward = MOTOR_MAX) : (forward = forward);
        PWM_Motor_WriteCompare1(forward);
    }
    else if(rx_data.motor < MOTOR_REVERSE_TH)
    {
        PWM_Motor_Start();
        PWM_Motor_WriteCompare1(0);  // Both shall not be on at the same time
        reverse = -2*rx_data.motor + 1000;
        reverse = (reverse >= MOTOR_MAX) ? (reverse = MOTOR_MAX) : (reverse = reverse);
        PWM_Motor_WriteCompare2(reverse);
    }
    else
    {
        PWM_Motor_WriteCompare1(0);
        PWM_Motor_WriteCompare2(0);
        PWM_Motor_Stop();
    }
}


void servo(void)
{
    if(rx_data.servo <= SERVO_TH_LOW || rx_data.servo >= SERVO_TH_HIGH)
    {
        PWM_Servo_Start();
        PWM_Servo_WriteCompare(rx_data.servo);
    }
    //else PWM_Servo_Stop();
}


void motor_process(void)
{
    // If cruise control is enabled, manual motor control is disabled and PID is enabled  
    if(rx_data.drive_mode_bits == FALSE)
    {
        motor();
        led_sel(LED_GREEN_2, FALSE);
    }
    else
    {
        PWM_Motor_Start();
        PWM_Motor_WriteCompare2(FALSE);
        pid(rx_data.speed_set);
        led_sel(LED_GREEN_2, TRUE);
    }
    
    servo();   
}

/* [] END OF FILE */

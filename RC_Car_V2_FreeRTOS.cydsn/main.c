/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 * 
 * Engineers: Nini, Winnie, TyTy
 * ========================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "project.h"

// FreeRTOS libraies
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"

// Driver libraries
#include "uart_ctrl.h"
#include "led_ctrl.h"
#include "data.h"
#include "motor.h"
#include "rc_car.h"
#include "ultrasonic_ctrl.h"
#include "i2c_ctrl.h"
#include "charge_meter_ctrl.h"
#include "gps_ctrl.h"
#include "eeprom_ctrl.h"


/* Wait constants */
#define WAIT_1MS    (1u)
#define WAIT_20MS   (20u)
#define WAIT_50MS   (50u)


/* The following ISR handles any alarms in the case of motor overcurrent */
CY_ISR(alert_handler)
{
    /* Stops the motor in the event of an interrupt */
    if(!Alert_Read())
        PWM_Motor_Stop();
    else
        PWM_Motor_Start();

    Alert_ClearInterrupt();
}


extern void FreeRTOS_Start();


// None RTOS functions (i.e Hardare initialization)
void hardware_init(void)
{
    PWM_Servo_Start();
    PWM_Motor_Start();
    UART_Radio_Start();
    UART_GPS_Start();
    UART_Jetson_Start();
    I2C_Start();
    VREF_Start();
    PWM_trigger_Start();
    Timer_echo_1_Start();
    Timer_echo_2_Start();
    Timer_echo_3_Start();

    /* ISRs */
    alert_isr_Start();
    alert_isr_StartEx(alert_handler);
}


void code_initialization(void)
{
    uart_init();
    led_setup();
    charge_meter_setup();
    UART_Radio_ClearRxBuffer();
    UART_Radio_ClearTxBuffer();
    motor_setup();
    gps_setup();
    trigger_reset_Write(TRUE);
    eeprom_init();
    
    /* Initialize motor PWM at 0 */
    PWM_Motor_WriteCompare1(0);
    PWM_Motor_WriteCompare2(0);
}


/* Task space - All calbacks will be defined in other files and called on their respective tasks. 
   The application switches between tasks based on the internal core timer*/
void uart_task(void *ptr);
void uart_send_task(void* ptr);
void motor_task(void *ptr);
void ultrasonic_task(void *ptr);
void charger_monitor_task(void *ptr);
void speed_task(void *ptr);
void i2c_update_task(void *ptr);
void gps_task(void* ptr);
void jetson_task(void* ptr);

///* All handle declarations here */
TaskHandle_t uart_rx_handle    = NULL;
TaskHandle_t uart_tx_handle    = NULL;
TaskHandle_t motor_handle      = NULL;
TaskHandle_t ultrasonic_handle = NULL; 
TaskHandle_t charger_handle    = NULL;
TaskHandle_t speed_ctrl_handle = NULL; 
TaskHandle_t i2c_update_handle = NULL;
TaskHandle_t gps_handle        = NULL;
TaskHandle_t jetson_handle     = NULL; 


int main(void)
{     
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /* All function initializations get called here */  
    hardware_init();
    code_initialization();
    
    FreeRTOS_Start();  
    
    /* All task callbacks go here */
    xTaskCreate(uart_task, 
                "uart task", 
                1024, 
                NULL, 
                3, 
                &uart_rx_handle); 
    
    xTaskCreate(uart_send_task, 
                "uart send task", 
                1024, 
                NULL, 
                1, 
                &uart_tx_handle); 

    xTaskCreate(motor_task, 
                "motor task", 
                1024, 
                NULL, 
                2, 
                &motor_handle);

    xTaskCreate(ultrasonic_task, 
                "ultrasonic task",
                1024, 
                NULL, 
                1, 
                &ultrasonic_handle);

    xTaskCreate(speed_task, 
                "speed task", 
                512, 
                NULL, 
                1, 
                &speed_ctrl_handle);

    xTaskCreate(charger_monitor_task, 
                "charger task",
                512, 
                NULL, 
                1, 
                &charger_handle);

    xTaskCreate(i2c_update_task, 
                "i2c task",
                512, 
                NULL, 
                1, 
                &i2c_update_handle);

    xTaskCreate(gps_task, 
                "gps task", 
                1024, 
                NULL, 
                1, 
                &gps_handle);

    xTaskCreate(jetson_task, 
                "gps task", 
                1024, 
                NULL, 
                1, 
                &jetson_handle);
    
    vTaskStartScheduler();
   
    while(1)
    {
        /* Do not write any code here as it will not execute */
    }
}


void uart_task(void *ptr)
{
    while(1)
    {
        uart_process();
        vTaskDelay(WAIT_1MS / portTICK_PERIOD_MS);
    }
}


void uart_send_task(void *ptr)
{
    while(1)
    {
        uart_send_data();
        vTaskDelay(WAIT_20MS / portTICK_PERIOD_MS);
    }
}


void motor_task(void *ptr)
{
    while(1)
    {   
        motor_process();
        vTaskDelay(WAIT_1MS / portTICK_PERIOD_MS);
    }
}


void ultrasonic_task(void *ptr)
{
    while(1)
    {
        distance_update();
    }
}


void charger_monitor_task(void *ptr)
{
    while(1)
    {
        battery_monitor_process();
            
        vTaskDelay(WAIT_50MS / portTICK_PERIOD_MS);
    }
}


void speed_task(void *ptr)
{
    while(1)
    {
        speed_update();
    }
}


void i2c_update_task(void *ptr)
{    
    while(1)
    {
        i2c_process();
    }
}


void gps_task(void* ptr)
{
    while(1)
    {
        gps_process();
        
        vTaskDelay(WAIT_1MS / portTICK_PERIOD_MS);
    }
}


void jetson_task(void *ptr)
{
    while(1)
    {
         vTaskDelay(WAIT_1MS / portTICK_PERIOD_MS);
    }
}

/* [] END OF FILE */

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
#include "rc_car.h"
#include "data.h"
#include "ultrasonic_ctrl.h"


#define WEIGHT  (0.1)

    
static float distance_left_avg;
static float distance_front_avg;
static float distance_right_avg;

static int distance_left;
static int distance_front;
static int distance_right;

static float speed_avg;


float avg_filter(float* ret, uint8 val, double weight)
{
    *ret += (val - *ret) * weight;
    return *ret;
}


void distance_update(void)
{    
    get_distance(&distance_left, &distance_front, &distance_right);
    
    tx_data.front_distance = avg_filter(&distance_front_avg ,distance_front/58.0, WEIGHT);
    tx_data.right_distance = avg_filter(&distance_right_avg ,distance_right/58.0, WEIGHT);
    tx_data.left_distance  = avg_filter(&distance_left_avg, distance_left /58.0, WEIGHT); 
}


void speed_update(void)
{
    tx_data.speed = avg_filter(&speed_avg, (float)speed_Read(), N);
}

/* [] END OF FILE */

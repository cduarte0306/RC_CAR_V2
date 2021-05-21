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

#ifndef RC_CAR_H
#define RC_CAR_H
    
#include <cytypes.h>
    
    
#define N       (0.01)
    

float avg_filter(float* ret, uint8 val, double weight);
void distance_update(void);
void speed_update(void);

    
#endif

/* [] END OF FILE */

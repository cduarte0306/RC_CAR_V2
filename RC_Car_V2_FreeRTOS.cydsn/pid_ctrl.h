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

#ifndef PID_H
#define PID_H

#include <cytypes.h>


#define KP      (0.09)
#define KI      (0.3)
#define KD      (1.0)
#define PID_MAX (950u)


void pid( uint16 speed );


#endif

/* [] END OF FILE */

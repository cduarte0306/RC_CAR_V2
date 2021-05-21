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
#ifndef UTILITIES_H
#define UTILITIES_H
    
#include "cytypes.h"
    
#ifndef TRUE
    #define TRUE    1
#endif

#ifndef FALSE
    #define FALSE   0
#endif
    
#ifndef cruise_bit
    #define cruise_bit(x) (((uint8)x) & 0x01)
#endif

#ifndef speed_set_bits
    #define speed_set_bits(x) (((uint8)x) & 0x06)
#endif

#ifndef min
    #define min(a, b) (a <= b) ? b : a
#endif

#ifndef max
    #define max(a, b) (a >= b) ? b : a
#endif

#ifndef bound
    #define bound(a,b,c) (b <= a) ? a : (b >= c) ? c : b
#endif

#endif

/* [] END OF FILE */

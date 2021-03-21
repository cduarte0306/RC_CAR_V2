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

#ifndef EEPROM_CTRL_H
#define EEPROM_CTRL_H

#include <cytypes.h>


void eeprom_init(void);
void eeprom_process(unsigned char kx);
void process_queue(void);

#endif

/* [] END OF FILE */

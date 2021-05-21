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

#ifndef QUEUE_CTRL_H
#define QUEUE_CTRL_H

#include <cytypes.h>


typedef struct
{
    void* data;      // Points to the data
    uint8 size;      // Max size
    uint8 req_ptr;   // Points to the latest led request
    uint8 exec_ptr;  // Points to the current command
} queue_t;


void queue_init(queue_t* queue, uint8 size, void* data);
uint8 queue_empty(queue_t* queue);
uint8 queue_inc_exec_ptr(queue_t* queue);
uint8 queue_inc_req_ptr(queue_t* queue);
void* queue_get_exec(queue_t* queue, uint8 type_size);
void* queue_get_req(queue_t* queue, uint8 type_size);
uint8 queue_get_num(queue_t* queue);

#endif

/* [] END OF FILE */

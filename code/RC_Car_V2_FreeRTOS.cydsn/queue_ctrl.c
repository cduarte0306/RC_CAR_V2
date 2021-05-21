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

#include "queue_ctrl.h"


void queue_init(queue_t* queue, uint8 size, void* data)
{
    queue->data = data;
    queue->size = size;
    queue->req_ptr  = 1;
    queue->exec_ptr = 0;
}


uint8 queue_empty(queue_t* queue)
{
    uint8 next_val = (queue->exec_ptr + 1 < queue->size)? (queue->exec_ptr + 1): 0;
    if(next_val == queue->req_ptr) return 1;
    
    return 0;
}


uint8 queue_inc_exec_ptr(queue_t* queue)
{
    uint8 next_val = (queue->exec_ptr + 1 < queue->size)? (queue->exec_ptr + 1): 0;
    if(next_val == queue->req_ptr) return 0;
    
    queue->exec_ptr = next_val;
    return 1;
}


uint8 queue_dec_exec_ptr(queue_t* queue)
{
    uint8 next_val = (queue->exec_ptr - 1 >= 0)? (queue->exec_ptr - 1): queue->size - 1;
    if(next_val == queue->req_ptr) return 0;
    
    queue->exec_ptr = next_val;
    return 1;
}


uint8 queue_inc_req_ptr(queue_t* queue)
{
	uint8 next_val = (queue->req_ptr + 1 < queue->size)? (queue->req_ptr + 1): 0;
    if(next_val == queue->exec_ptr) return 0;

    queue->req_ptr = next_val;
    return 1;
}


void* queue_get_exec(queue_t* queue, uint8 type_size)
{
    // Execution ptr is always trailing behind one because it starts at 0 and req_ptr starts at 1
    uint8 exec_ptr = (queue->exec_ptr + 1 < queue->size)? (queue->exec_ptr + 1): 0;
    return queue->data + exec_ptr*type_size;
}


void* queue_get_req(queue_t* queue, uint8 type_size)
{
    return queue->data + queue->req_ptr*type_size;
}


uint8 queue_get_num(queue_t* queue)
{
    if(queue->exec_ptr < queue->req_ptr)
    {
    	return queue->req_ptr - queue->exec_ptr - 1;
    }

    return queue->size - queue->exec_ptr + queue->req_ptr - 1;
}


/* [] END OF FILE */

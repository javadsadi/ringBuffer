/*
 * ringBuffer.h
 *
 *  Created on: May 23, 2022
 *      Author: Sadi
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct ringBuffer
{
	uint8_t *buffer;
	uint16_t lenght;
	uint16_t rIndex,wIndex;
}ringBuffer_t;

uint8_t ringBuffer_init(ringBuffer_t *rbuff,uint16_t lenght);
void ringBuffer_push(ringBuffer_t *rbuff,uint8_t input);
uint8_t ringBuffer_get(ringBuffer_t *rbuff,uint16_t index);
uint8_t ringBuffer_get_offset(ringBuffer_t *rbuff,uint16_t index,int offset);
uint16_t ringBuffer_calc_offset(ringBuffer_t *rbuff,uint16_t index,int offset);
void ringBuffer_add_rIndex(ringBuffer_t *rbuff,int count);
uint16_t ringBuffer_exiting_bytes(ringBuffer_t *rbuff);
void ringBuffer_reset_wIndex(ringBuffer_t *rbuff);
void ringBuffer_copy(ringBuffer_t *rbuff, uint8_t *dest,int lenght, uint16_t index,int count);

#endif /* INC_RING_BUFFER_H_ */

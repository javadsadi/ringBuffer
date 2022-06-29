/*
 * ringBuffer.c
 *
 *  Created on: May 23, 2022
 *      Author: Sadi
 */

#include "ringBuffer.h"

uint8_t ringBuffer_init(ringBuffer_t *rbuff,uint16_t lenght)
{
	rbuff->buffer = (uint8_t*)malloc(sizeof(uint8_t*) * lenght);
	rbuff->lenght = lenght;
	rbuff->rIndex = 0;
	rbuff->wIndex = 0;
	if(rbuff->buffer != NULL)
		return 1;
	else
		return 0;
}

void ringBuffer_push(ringBuffer_t *rbuff,uint8_t input)
{
	rbuff->buffer[rbuff->wIndex++] = input;
	if(rbuff->wIndex >= rbuff->lenght)
	{
		rbuff->wIndex = 0;
	}
}

uint8_t ringBuffer_get(ringBuffer_t *rbuff,uint16_t index)
{
	return rbuff->buffer[index];
}

uint8_t ringBuffer_get_offset(ringBuffer_t *rbuff,uint16_t index,int offset)
{
	uint8_t result = 0;
	if ((index + offset) <= (rbuff->lenght-1))
	{
		result = rbuff->buffer[index + offset];
	}
	else if ((index + offset) > (rbuff->lenght-1))
	{
		result = rbuff->buffer[index + offset - rbuff->lenght];
	}
	else if ((index + offset) < 0)
	{
		result = rbuff->buffer[rbuff->lenght + (index + offset)];
	}
	return result;
}

uint16_t ringBuffer_calc_offset(ringBuffer_t *rbuff,uint16_t index,int offset)
{
	uint16_t result = 0;
	if ((index + offset) <= (rbuff->lenght-1))
	{
		result = index + offset;
	}
	else if ((index + offset) > (rbuff->lenght-1))
	{
		result = index + offset - rbuff->lenght;
	}
	else if ((index + offset) < 0)
	{
		result = rbuff->lenght + (index + offset);
	}
	return result;
}

void ringBuffer_add_rIndex(ringBuffer_t *rbuff,int count)
{
	if ((rbuff->rIndex + count) <= (rbuff->lenght-1))
	{
		rbuff->rIndex += count;
	}
	else if ((rbuff->rIndex + count) > (rbuff->lenght-1))
	{
		rbuff->rIndex = rbuff->rIndex + count - rbuff->lenght;
	}
	else if ((rbuff->rIndex + count) < 0)
	{
		rbuff->rIndex = rbuff->lenght + (rbuff->rIndex + count);
	}
}

uint16_t ringBuffer_exiting_bytes(ringBuffer_t *rbuff)
{
	uint16_t count=0;
	if (rbuff->wIndex > rbuff->rIndex)
	{
		count = rbuff->wIndex - rbuff->rIndex;
	}
	else if (rbuff->wIndex < rbuff->rIndex)
	{
		count = (rbuff->lenght - rbuff->rIndex) + rbuff->wIndex;
	}
	else if (rbuff->wIndex == rbuff->rIndex)
	{
		count = 0;
	}

	return count;
}

void ringBuffer_reset_wIndex(ringBuffer_t *rbuff)
{
	rbuff->wIndex = 0;
}

void ringBuffer_copy(ringBuffer_t *rbuff, uint8_t *dest, uint16_t index,int count)
{
	int i = 0;

	for (i = 0; i < count; i++)
	{
		dest[i] = ringBuffer_get_offset(rbuff,index,i);
	}
}

/*
 * ring_buffer.h
 *
 *  Created on: Aug 9, 2024
 *      Author: orion
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_



#include <stdint.h>
#include <stdbool.h>



#define RING_BUFFER_SIZE 128

typedef struct {
    uint8_t buffer[RING_BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} RingBuffer;

void RingBuffer_Init(RingBuffer *rb);
bool RingBuffer_IsEmpty(RingBuffer *rb);
bool RingBuffer_IsFull(RingBuffer *rb);
bool RingBuffer_Put(RingBuffer *rb, uint8_t data);
bool RingBuffer_Get(RingBuffer *rb, uint8_t *data);



#endif /* RING_BUFFER_H_ */

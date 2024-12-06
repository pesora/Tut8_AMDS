/*
 * ring_buffer.c
 *
 *  Created on: Aug 9, 2024
 *      Author: orion
 */


#include "ring_buffer.h"



void RingBuffer_Init(RingBuffer *rb) {
    rb->head = 0;
    rb->tail = 0;
}

bool RingBuffer_IsEmpty(RingBuffer *rb) {
    return rb->head == rb->tail;
}

bool RingBuffer_IsFull(RingBuffer *rb) {
    return ((rb->head + 1) % RING_BUFFER_SIZE) == rb->tail;
}

bool RingBuffer_Put(RingBuffer *rb, uint8_t data) {
    if (RingBuffer_IsFull(rb)) {
        return false; // Buffer is full
    }
    rb->buffer[rb->head] = data;
    rb->head = (rb->head + 1) % RING_BUFFER_SIZE;
    return true;
}

bool RingBuffer_Get(RingBuffer *rb, uint8_t *data) {
    if (RingBuffer_IsEmpty(rb)) {
        return false; // Buffer is empty
    }
    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
    return true;
}



/*
 * debug_uart.h
 *
 *  Created on: May 25, 2024
 *      Author: orion
 */

#ifndef UART_COMM_H_
#define UART_COMM_H_


#include <stdint.h>
#include "usart.h"
#include "ring_buffer.h"

extern RingBuffer rxBuffer[];
extern uint8_t cmd_fan_step;
extern float cmdT1, cmdT2;
extern uint8_t Cmd_Received;


extern UART_HandleTypeDef* currentUart;


void Uart_Init(void);
void switchUart(UART_HandleTypeDef* huart);
void UART_Flush(UART_HandleTypeDef *huart);

#endif /* UART_COMM_H_ */

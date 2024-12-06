/*
 * debug_uart.h
 *
 *  Created on: May 25, 2024
 *      Author: orion
 */

#ifndef DEBUG_UART_H_
#define DEBUG_UART_H_


#include <stdint.h>
#include "usart.h"
#include "ring_buffer.h"

extern RingBuffer rxBuffer;
extern uint8_t cmd_fan_step;
extern float cmdT1, cmdT2;
extern uint8_t Cmd_Received;


void DBG_Uart_Init();
uint8_t DBG_GetCommand(uint8_t* fan_step);
void uart_isr(UART_HandleTypeDef *huart);

#endif /* DEBUG_UART_H_ */

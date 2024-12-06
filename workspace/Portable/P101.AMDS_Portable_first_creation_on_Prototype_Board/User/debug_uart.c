/*
 * debug_uart.c
 *
 *  Created on: May 25, 2024
 *      Author: orion
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug_uart.h"
#include "usart.h"
#include "ring_buffer.h"


uint8_t cmd_fan_step;

RingBuffer rxBuffer;
char receivedString[RING_BUFFER_SIZE];
uint16_t rxIndex = 0;


uint8_t command[RING_BUFFER_SIZE];
uint8_t cmd_buf[RING_BUFFER_SIZE];   //copy received data in ring buff to command buff
float cmdT1, cmdT2;
uint8_t Cmd_Received = 0;



void DBG_Uart_Init()
{
  RingBuffer_Init(&rxBuffer);
}


void uart_isr(UART_HandleTypeDef *huart) {
//  uint32_t isrflags = READ_REG(huart->Instance->SR);
//  uint32_t cr1its = READ_REG(huart->Instance->CR1);
//
//  //uint8_t rx;
//
//  if (((isrflags & USART_SR_RXNE) != RESET)
//      && ((cr1its & USART_CR1_RXNEIE) != RESET)) {
//
//    huart->Instance->SR;
//    rx = (uint8_t) (huart->Instance->DR & (uint8_t) 0x00FF);
//   // RB_Write (&ring_buff, rx);
//    return;
//  }
}

//uint8_t DBG_GetFanSpeed(void)
//{
//
//}


void parseReceivedString(char* receivedString, float* cmdT1, float* cmdT2) {
    char* token;
    char* endPtr;
    int index = 0;

    token = strtok(receivedString, " ");
    while (token != NULL) {
        if (index == 1) {
            *cmdT1 = strtof(token, &endPtr); // ASCII to float 변환
        } else if (index == 2) {
            *cmdT2 = strtof(token, &endPtr); // ASCII to float 변환
        }
        token = strtok(NULL, " ");
        index++;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART3) {
        uint8_t data = rxBuffer.buffer[rxBuffer.head];
        RingBuffer_Put(&rxBuffer, data);
        rxBuffer.head = (rxBuffer.head + 1) % RING_BUFFER_SIZE; // update index
        HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxBuffer.buffer[rxBuffer.head], 1);

        //if Enter key is pressed
        if (data == '\r') {
            receivedString[rxIndex] = '\0'; // string end
            strncpy((char*)cmd_buf, (char*)&receivedString, strlen(receivedString));

            // 여기에 코드 넣어 주세요
            parseReceivedString((char*)cmd_buf, &cmdT1, &cmdT2);
            printf("cmdT1: %.2f, cmdT2: %.2f\n", cmdT1, cmdT2);

            if(cmdT1 >= 100.0 && cmdT2 >= 100.0)
              Cmd_Received = 0;
            else
              Cmd_Received = 1;
            rxIndex = 0;      // initializing index
        } else {
            receivedString[rxIndex++] = data;
            if (rxIndex >= RING_BUFFER_SIZE) {
                rxIndex = 0; // Preventing buffer overflow
            }
        }
    }
}

/*
 * debug_uart.c
 *
 *  Created on: May 25, 2024
 *      Author: orion
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usart.h"
#include "uart_comm.h"
#include "ring_buffer.h"


#define UART_PORTS 1

RingBuffer rxBuffer[UART_PORTS];
char receivedString[UART_PORTS][RING_BUFFER_SIZE];
uint16_t rxIndex[UART_PORTS] = {0};
uint8_t line_buf[UART_PORTS][RING_BUFFER_SIZE];   //copy received data
uint16_t rx_count = 0;

//Uart port selection
UART_HandleTypeDef* currentUart = &huart3; 		// Default UART

void Uart_Init() {
    for (int i = 0; i < UART_PORTS; i++) {
        RingBuffer_Init(&rxBuffer[i]);
    }
}

// Function to switch UART port
void switchUart(UART_HandleTypeDef* huart) {
    currentUart = huart;
}

// UART 버퍼를 클리어하는 함수
void UART_Flush(UART_HandleTypeDef *huart) {
    uint8_t data;
    while (HAL_UART_Receive(huart, &data, 1, 10) == HAL_OK) {
        // Do nothing, just keep reading until buffer is empty
    }
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    uint8_t uartNum = 3;

    //UART3
    if (huart->Instance == USART3) {

        uint8_t data = rxBuffer[0].buffer[rxBuffer[0].head];
        RingBuffer_Put(&rxBuffer[0], data);
        rxBuffer[0].head = (rxBuffer[0].head + 1) % RING_BUFFER_SIZE; // update index

        HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxBuffer[0].buffer[rxBuffer[0].head], 1);

        //if Enter key is pressed
        if (data == '\n' || data == '\r') {
            receivedString[0][rxIndex[0]] = '\0'; // string end
            size_t size = strlen(receivedString[0]);

            //clear line_buf
            memset((char*)line_buf[0], 0x0, sizeof(line_buf[0]));
            strncpy((char*)line_buf[0], (char*)&receivedString[0], strlen(receivedString[0]));

            // put your code
            //-----------------------------
            switchUart(&huart3);
            printf("uart%d> %s(%d)\n", uartNum, line_buf[0], size);



            //-----------------------------
            rxIndex[0] = 0;      // initializing index

        } else {
        	receivedString[0][rxIndex[0]++] = data;
            if (rxIndex[0] >= RING_BUFFER_SIZE) {
                rxIndex[0] = 0; // Preventing buffer overflow
            }
        }
    }
   else {
       return; // Unknown UART port
   }
}

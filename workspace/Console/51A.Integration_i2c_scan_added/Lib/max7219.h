/*
 * max7219.h
 *
 *  Created on: Aug 20, 2024
 *      Author: machi
 */

#ifndef MAX7219_H_
#define MAX7219_H_

#include "spi.h"

// MAX7219 레지스터 주소
#define MAX7219_NO_OP        0x00
#define MAX7219_DIGIT0       0x01
#define MAX7219_DIGIT1       0x02
#define MAX7219_DIGIT2       0x03
#define MAX7219_DECODE_MODE  0x09
#define MAX7219_INTENSITY    0x0A
#define MAX7219_SCAN_LIMIT   0x0B
#define MAX7219_SHUTDOWN     0x0C
#define MAX7219_DISPLAY_TEST 0x0F



void MAX7219_Init(void);
void Display_Number(uint32_t num);
void Display_Char(char c);
void Display_3Digit(const char* str);

#endif /* MAX7219_H_ */

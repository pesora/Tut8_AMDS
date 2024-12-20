#include "max7219.h"
#include <stdio.h>

extern SPI_HandleTypeDef hspi3;
static void MAX7219_Clear_3Digits(void);
static void MAX7219_Write(uint8_t address, uint8_t data);

const uint8_t char_map[] = {
    [' '] = 0b00000000, // 공백
    ['0'] = 0b01111110, // 0
    ['1'] = 0b00110000, // 1
    ['2'] = 0b01101101, // 2
    ['3'] = 0b01111001, // 3
    ['4'] = 0b00110011, // 4
    ['5'] = 0b01011011, // 5
    ['6'] = 0b01011111, // 6
    ['7'] = 0b01110000, // 7
    ['8'] = 0b01111111, // 8
    ['9'] = 0b01111011, // 9
    ['?'] = 0b01100101, // 9
    ['A'] = 0b01110111, // A
    ['B'] = 0b01111100, // B
    ['C'] = 0b00111001, // C
    ['D'] = 0b01111010, // D
    ['E'] = 0b01001111, // E
    ['F'] = 0b01100111, // F
};


void MAX7219_Write(uint8_t address, uint8_t data) {
    uint8_t txData[2] = {address, data};
    HAL_GPIO_WritePin(SEG_LOAD_GPIO_Port, SEG_LOAD_Pin, GPIO_PIN_RESET); // CS 핀 LOW
    HAL_SPI_Transmit(&hspi3, txData, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(SEG_LOAD_GPIO_Port, SEG_LOAD_Pin, GPIO_PIN_SET);   // CS 핀 HIGH
}

void MAX7219_Clear_All(void) {
    for (uint8_t i = 0; i < 8; i++) {
        MAX7219_Write(i, 0x0F); // 모든 digit을 OFF
    }
}

static void MAX7219_Clear_3Digits(void) {
    MAX7219_Write(MAX7219_DIGIT0, 0x0F); // 첫 번째 digit OFF
    MAX7219_Write(MAX7219_DIGIT1, 0x0F); // 두 번째 digit OFF
    MAX7219_Write(MAX7219_DIGIT2, 0x0F); // 세 번째 digit OFF
}

void MAX7219_Init(void) {
    MAX7219_Write(MAX7219_SCAN_LIMIT, 0x02);  // 3-digit 사용
    MAX7219_Write(MAX7219_DECODE_MODE, 0x00); // no decode mode
    MAX7219_Write(MAX7219_INTENSITY, 0x0F);   // 최대 밝기
    MAX7219_Write(MAX7219_SHUTDOWN, 0x01);    // 정상 작동 모드

    MAX7219_Clear_3Digits();
    Display_3Digit("   ");
}

void Display_3Digit(const char* str) {
    if (str == NULL) return;

    MAX7219_Write(MAX7219_DIGIT0, char_map[(uint8_t)str[0]]);
    MAX7219_Write(MAX7219_DIGIT1, char_map[(uint8_t)str[1]]);
    MAX7219_Write(MAX7219_DIGIT2, char_map[(uint8_t)str[2]]);
}

void Display_Number(uint32_t num) {
    char str[4]; // 최대 3자리 숫자 + null terminator
    snprintf(str, sizeof(str), "%3lu", (unsigned long)num); // 숫자를 문자열로 변환, 공백 포함

    // 맨 앞에 0이 나오는 디지트를 꺼서 표시
    if (str[0] == '0') {
        str[0] = ' ';
        if (str[1] == '0') {
            str[1] = ' ';
        }
    }

    Display_3Digit(str);
}


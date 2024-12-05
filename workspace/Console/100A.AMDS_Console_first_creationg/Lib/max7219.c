#include "max7219.h"
#include <stdio.h>

extern SPI_HandleTypeDef hspi3;
static void MAX7219_Clear_3Digits(void);
static void MAX7219_Write(uint8_t address, uint8_t data);

const uint8_t char_map[128] = {
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
    //['E'] = 0b01101111, // E
    ['F'] = 0b01100111, // F
    ['G'] = 0b01011111, // G
    ['H'] = 0b01110100, // H
    ['I'] = 0b00110000, // I
    ['J'] = 0b00011110, // J
    ['K'] = 0b01110101, // K
    ['L'] = 0b00111000, // L
    ['M'] = 0b00010101, // M
    ['N'] = 0b00110111, // N
    ['O'] = 0b00111111, // O
    ['P'] = 0b01100111, // P
    ['Q'] = 0b01110011, // Q
    ['R'] = 0b00110111, // R
    ['S'] = 0b01011011, // S
    ['T'] = 0b01111000, // T
    ['U'] = 0b00111110, // U
    ['V'] = 0b00111110, // V
    ['W'] = 0b00101010, // W
    ['X'] = 0b01110110, // X
    ['Y'] = 0b01110010, // Y
    ['Z'] = 0b01001101, // Z
    ['a'] = 0b01110111, // a
    ['b'] = 0b01111100, // b
    ['c'] = 0b00111001, // c
    ['d'] = 0b01111010, // d
    ['e'] = 0b01101111, // e
    ['f'] = 0b01100111, // f
    ['g'] = 0b01011111, // g
    ['h'] = 0b01110100, // h
    ['i'] = 0b00110000, // i
    ['j'] = 0b00011110, // j
    ['k'] = 0b01110101, // k
    ['l'] = 0b00111000, // l
    ['m'] = 0b00010101, // m
    ['n'] = 0b00110111, // n
    ['o'] = 0b00111111, // o
    ['p'] = 0b01100111, // p
    ['q'] = 0b01110011, // q
    ['r'] = 0b00000101, // r
    //['r'] = 0b00110111, // r
    ['s'] = 0b01011011, // s
    ['t'] = 0b01111000, // t
    ['u'] = 0b00111110, // u
    ['v'] = 0b00111110, // v
    ['w'] = 0b00101010, // w
    ['x'] = 0b01110110, // x
    ['y'] = 0b01110010, // y
    ['z'] = 0b01001101  // z
};

//const uint8_t char_map[128] = {
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 0-9 (NUL, SOH, STX, ETX, EOT, ENQ, ACK, BEL, BS, HT)
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 10-19 (LF, VT, FF, CR, SO, SI, DLE, DC1, DC2, DC3)
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 20-29 (DC4, NAK, SYN, ETB, CAN, EM, SUB, ESC, FS, GS)
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 30-39 (RS, US, Space, !, ", #, $, %, &, ')
//    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, // 40-49 ( (, ), *, +, ,, -, ., /, 0)
//    0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x00, // 50-59 (1, 2, 3, 4, 5, 6, 7, 8, 9, :)
//    0x00, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, 0x76, 0x06, // 60-69 (;, <, =, >, ?, @, A, B, C, D)
//    0x79, 0x71, 0x3D, 0x76, 0x06, 0x1E, 0x76, 0x38, 0x37, 0x3F, // 70-79 (E, F, G, H, I, J, K, L, M, N)
//    0x3F, 0x73, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, // 80-89 (O, P, Q, R, S, T, U, V, W, X)
//    0x76, 0x06, 0x1E, 0x76, 0x38, 0x37, 0x3F, 0x3F, 0x73, 0x67, // 90-99 (Y, Z, [, \, ], ^, _, `, a, b)
//    0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, 0x76, 0x06, 0x1E, // 100-109 (c, d, e, f, g, h, i, j, k, l)
//    0x76, 0x38, 0x37, 0x3F, 0x3F, 0x73, 0x67, 0x77, 0x7C, 0x39, // 110-119 (m, n, o, p, q, r, s, t, u, v)
//    0x5E, 0x79, 0x71, 0x3D, 0x76, 0x06, 0x1E, 0x76, 0x00,       // 120-127 (w, x, y, z, {, |, }, ~)
//};

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

    MAX7219_Write(MAX7219_DIGIT0, char_map[(uint8_t)str[2]]);
    MAX7219_Write(MAX7219_DIGIT1, char_map[(uint8_t)str[1]]);
    MAX7219_Write(MAX7219_DIGIT2, char_map[(uint8_t)str[0]]);
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


/*
 * utility.c
 *
 *  Created on: Jun 4, 2024
 *      Author: machi
 */

#include <math.h>
#include <stdio.h>
#include "utility.h"


///////////////////////////////////////////////////
// Make two 8-bit into a 16-bit word
uint16_t make16(uint8_t *hbyte, uint8_t *lbyte) {
  uint16_t data16=0;
    data16 = (uint16_t)(*hbyte);
    data16 = data16 << 8;
    data16 |= (uint16_t)(*lbyte);
    return data16;
}

///////////////////////////////////////////////////
// Seperate 16-bit into two 8-bit
uint8_t make8(uint16_t word, uint8_t pos) {
  uint8_t byte;
    byte = (uint8_t)(word>>(8*pos) & 0x00FF);
    return byte;
}

///////////////////////////////////////////////////
double Rounding( double x, int digit )
{
    return ( (double)floor( (double)(x) * pow( (double)10, digit ) + 0.5f ) / pow( (double)10, digit ) );
}

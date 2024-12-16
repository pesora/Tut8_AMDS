/*
 * utility.h
 *
 *  Created on: Jun 4, 2024
 *      Author: machi
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdint.h>

//============================================================================
//최대 최소값 마크로 정의
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

///////////////////////////////////////////////////
// ROUNDING(x, dig)
//  example : ROUNDING( 9.3453456, 5 ) = 9.34535
#define ROUNDING(x, dig)    ( floor((x) * pow(float(10), dig) + 0.5f) / pow(float(10), dig) )


///////////////////////////////////////////////////
extern uint16_t make16(uint8_t *hbyte, uint8_t *lbyte);
extern uint8_t make8(uint16_t word, uint8_t pos);
extern double Rounding( double x, int digit );


#endif /* UTILITY_H_ */

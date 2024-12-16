/*
 * process.h
 *
 *  Created on: Jun 12, 2024
 *      Author: machi
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <stdint.h>
#include <stdbool.h>

//typedef struct {
//  float Temp1;
//  float Temp2;
//  uint8_t FAN1;
//  uint8_t FAN2;
//  uint8_t DP1;
//  uint8_t DP2;
//  uint8_t DP3;
//  uint8_t MineDet_Alarm;
//  uint8_t Charger;
//  uint8_t SOC_VAL;
//} Portable_Status_t;


//extern Portable_Status_t Portable_Status;


void Process_Init(void);
void Process_Portable_Status(void);

#endif /* PROCESS_H_ */

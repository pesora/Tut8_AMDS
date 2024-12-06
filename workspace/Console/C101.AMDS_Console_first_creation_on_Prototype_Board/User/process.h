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

typedef struct {
  float Temp1;
  float Temp2;
  bool FAN1;
  bool FAN2;
  bool DP1;
  bool DP2;
  bool DP3;
  bool MineDet_Alarm;
  bool Charger;
  uint8_t SOC_VAL;
} Portable_Status_t;


extern Portable_Status_t Portable_Status;


void Process_Init(void);
void Process_Console_Status(void);

#endif /* PROCESS_H_ */

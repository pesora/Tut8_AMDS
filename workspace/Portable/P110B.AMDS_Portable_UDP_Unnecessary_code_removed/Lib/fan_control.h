/*
 * fan_control.h
 *
 *  Created on: May 25, 2024
 *      Author: orion
 */

#ifndef FAN_CONTROL_H_
#define FAN_CONTROL_H_


#include <stdint.h>
#include "fan_config.h"
#include "collect.h"


typedef struct
{
  int16_t rpm;
  uint8_t err;
} FanData_t;

extern FanData_t Fan[];

extern uint8_t fan_step;
extern uint8_t fan_done;


void FAN_Init(void);
void FAN_Set_RPM(uint8_t fan_step);
void FAN_Read_FansStatus(void);
uint8_t FAN_Read_RPM(void);
void Print_FanStatus(void);
void Stop_InputCapute(void);
void Start_InputCapute(uint8_t channel);
void Control_Fan(Portable_Status_t *Status);
void FAN_ClearFrequency(void);

#endif /* FAN_CONTROL_H_ */

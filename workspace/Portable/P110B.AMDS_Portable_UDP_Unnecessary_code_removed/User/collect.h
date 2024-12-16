/*
 * input.h
 *
 *  Created on: Jul 3, 2024
 *      Author: machi
 */

#ifndef COLLECT_H_
#define COLLECT_H_


//typedef struct {
//  float Temp1;
//  float Temp2;
//  uint8_t Temp_Range;
//  uint8_t FAN1;
//  uint8_t FAN2;
//  uint8_t PSU;
//  uint8_t DP1;
//  uint8_t DP2;
//  uint8_t DP3;
//  uint8_t MineDet_Num;
//  uint8_t Charger;
//} Console_Status_t;

typedef struct {
  float Temp1;
  float Temp2;
  uint8_t Temp_Range;
  uint8_t FAN1;
  uint8_t FAN2;
  uint8_t DP1;
  uint8_t DP2;
  uint8_t DP3;
  uint8_t MineDet_Num;
  uint8_t Charger;
  uint8_t SOC_VAL;
} Portable_Status_t;


extern float Temp_Val1;
extern float Temp_Val2;
extern uint8_t FAN_Sense1;
extern uint8_t FAN_Sense2;
extern uint8_t FAN_Sense3;
extern uint8_t FAN_Sense4;
extern uint8_t FAN_Sense5;
extern uint8_t FAN_Sense6;
extern uint8_t PSU_Status1;
extern uint8_t PSU_Status2;
extern uint8_t DP_Status1;
extern uint8_t DP_Status2;
extern uint8_t DP_Status3;
extern uint8_t MineDet_Num;
extern uint8_t Charger;
extern uint8_t BUZ_Status;

extern Portable_Status_t Portable_Status;

void Read_Temp_Value(void);
void Read_FAN_Status(void);
void Read_PSU_Status(void);
void Read_DP_Status(void);
void Read_MineDet_Number(void);
void Read_Charger_Status(void);
void Read_BAT_Status(void);
void Store_Portable_Status(void);
void Print_Portable_Status(void);
uint8_t GetTempStatus(void);
void Read_BUZ_Status(void);

#endif /* COLLECT_H_ */

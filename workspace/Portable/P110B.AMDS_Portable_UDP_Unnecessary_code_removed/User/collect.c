/*
 * input.c
 *
 *  Created on: Jul 3, 2024
 *      Author: machi
 */


#include <stdio.h>
#include "main.h"
#include "collect.h"
#include "hih8131.h"
#include "fan_control.h"
#include "bq34z100.h"
#include "display.h"
#include "udp_server.h"
#include "uart_comm.h"



float Temp_Val1;
float Temp_Val2;
uint8_t FAN_Sense1;
uint8_t FAN_Sense2;
uint8_t FAN_Sense3;
uint8_t FAN_Sense4;
uint8_t FAN_Sense5;
uint8_t FAN_Sense6;
uint8_t PSU_Status1;
uint8_t PSU_Status2;
uint8_t DP_Status1;
uint8_t DP_Status2;
uint8_t DP_Status3;
uint8_t MineDet_Num;
uint8_t Charger;
uint8_t BUZ_Status;

//-------------------------

Portable_Status_t Portable_Status;





void Read_Temp_Value(void)
{
  HMTP_Read_Temp_Value();

  Temp_Val1 = (float)HMTP_Data[0].fTemp;
  Temp_Val2 = (float)HMTP_Data[1].fTemp;
}

//
void Read_FAN_Status(void)
{
  FAN_Read_FansStatus();

	FAN_Sense1 = Fan[0].err;
	FAN_Sense2 = Fan[1].err;
}

//AMDS_BOARD
void Read_DP_Status(void)
{
  DP_Status1 = HAL_GPIO_ReadPin(INPUT_DP_LED1_GPIO_Port, INPUT_DP_LED1_Pin);
  DP_Status2 = HAL_GPIO_ReadPin(INPUT_DP_LED2_GPIO_Port, INPUT_DP_LED2_Pin);
  DP_Status3 = HAL_GPIO_ReadPin(INPUT_DP_LED3_GPIO_Port, INPUT_DP_LED3_Pin);
}

////NUCLEO_BOARD
////void Read_DP_Status(void)
//{
//  DP_Status1 = HAL_GPIO_ReadPin(INPUT_DP1_GPIO_Port, INPUT_DP1_Pin);
//  DP_Status2 = HAL_GPIO_ReadPin(INPUT_DP2_GPIO_Port, INPUT_DP2_Pin);
//  DP_Status3 = HAL_GPIO_ReadPin(INPUT_DP3_GPIO_Port, INPUT_DP3_Pin);
//}


void Read_MineDet_Number(void)
{
  MineDet_Num = UDP_Get_MineDetNum();
}

void Read_Charger_Status(void)
{
  Charger = HAL_GPIO_ReadPin(INPUT_CHG_GPIO_Port, INPUT_CHG_Pin);
}

void Read_BAT_Status(void)
{
  ReadBq34z100();

  Bat.SOC_Val     = BatData16[0];
  Bat.Voltage     = BatData16[1];
  Bat.AvgCurrent  = (int16_t)(BatData16[2]&0xFFFF);
  Bat.CycleCount  = BatData16[3];
  Bat.InternalTemp= (float)((float)BatData16[4]/10.0f - KELVIN);

}

void Read_BUZ_Status(void)
{
  // 0 : Buz ON, 1: Buz Off
  BUZ_Status = (uint8_t)HAL_GPIO_ReadPin(BUZ_GPIO_Port, BUZ_Pin);
}

static uint8_t GetTempStatus1(void){

  uint8_t Temp_Status1 = 0;

  //if No i2c error
  if(HMTP_Data[0].error == 0)
  {
    if(0<=Temp_Val1 && Temp_Val1<43.0f)
    {
      Temp_Status1 = 0;   //Normal
    }
    else if(43.0f<=Temp_Val1 && Temp_Val1<55.0f)
    {
      Temp_Status1 = 2;   //Warning
    }
    else if(Temp_Val1<0 || Temp_Val1>=55.0f)
    {
      Temp_Status1 = 1;   //Danger
    }
  }
  //if i2c error
  else
  {
    Temp_Status1 = 3;
  }

  //clear i2c error
  HMTP_Data[0].error = 0;

  return Temp_Status1;
}

static uint8_t GetTempStatus2(void)
{
  uint8_t Temp_Status2 = 0;

  //if No i2c error
  if(HMTP_Data[1].error == 0)
  {
    if(0<=Temp_Val2 && Temp_Val2<43.0f)
    {
      Temp_Status2 = 0;   //Normal
    }
    else if(43.0f<=Temp_Val2 && Temp_Val2<55.0f)
    {
      Temp_Status2 = 2;   //Warning
    }
    else if(Temp_Val2<0 || Temp_Val2>=55.0f)
    {
      Temp_Status2 = 1;   //Danger
    }
  }
  //if i2c error
  else
  {
    Temp_Status2 = 3;
  }

  //clear i2c error
  HMTP_Data[1].error = 0;

  return Temp_Status2;
}

uint8_t GetTempStatus(void)
{
  uint8_t Temp_Status = 0;
  uint8_t Temp_Status1 = 0;
  uint8_t Temp_Status2 = 0;

  Temp_Status1 = GetTempStatus1();
  Temp_Status2 = GetTempStatus2();

  //if i2c error
  if(Temp_Status1 == 3 || Temp_Status2 == 3)
  {
    Temp_Status = 3;
   }
  //Normal temp range
  else if(Temp_Status1 == 0 && Temp_Status2 == 0)
  {
    Temp_Status = 0;
   }
  //Danger temp range
  else if(Temp_Status1 == 1 || Temp_Status2 == 1)
  {
    Temp_Status = 1;
   }
  //Warning temp range
  else if(Temp_Status1 == 2 || Temp_Status2 == 2)
  {
    Temp_Status = 2;
  }

  return Temp_Status;
}

static uint8_t GetFanStatus1(void)
{
  uint8_t Fan_AddStatus = 0;
  uint8_t Fan_Status1 = 0;

 Fan_AddStatus = FAN_Sense1;	//FAN_Sense1 + FAN_Sense2 + FAN_Sense3;
 if(Fan_AddStatus == 0)
 {
   Fan_Status1 = 0;    //Good
 }
 else if(Fan_AddStatus == 3)
 {
   Fan_Status1 = 1;    //3 Fans abnormal
 }
 else
 {
   Fan_Status1 = 2;    //1 or 2 Fans Warning
 }

  return Fan_Status1;
}

static uint8_t GetFanStatus2(void)
{
  uint8_t Fan_AddStatus = 0;
  uint8_t Fan_Status2 = 0;

  Fan_AddStatus = FAN_Sense2;	//FAN_Sense4 + FAN_Sense5 + FAN_Sense6;
 if(Fan_AddStatus == 0)
 {
   Fan_Status2 = 0;    //Good
 }
 else if(Fan_AddStatus == 3)
 {
   Fan_Status2 = 1;    //3 Fans abnormal
 }
 else
 {
   Fan_Status2 = 2;    //1 or 2 Fans Warning
 }

  return Fan_Status2;
}

//Portable LED Status
void Store_Portable_Status(void)
{
  Portable_Status.Temp1 = Temp_Val1;
  Portable_Status.Temp2 = Temp_Val2;
  Portable_Status.Temp_Range = GetTempStatus();
  Portable_Status.FAN1  = GetFanStatus1();
  Portable_Status.FAN2  = GetFanStatus2();

  Portable_Status.DP1   = DP_Status1;
  Portable_Status.DP2   = DP_Status2;
  Portable_Status.DP3   = DP_Status3;
  Portable_Status.MineDet_Num = MineDet_Num;
  Portable_Status.Charger = Charger;
}

void Print_Display_Status(void)
{
  printf("TVal[%.1f %.1f] -> Temp[%d], FAN[%d %d], P[%d %d %d], MD[%d], CHG[%d]\n",
      Portable_Status.Temp1,
      Portable_Status.Temp2,
      Portable_Status.Temp_Range,
      Portable_Status.FAN1,
      Portable_Status.FAN2,

      Portable_Status.DP1,
      Portable_Status.DP2,
      Portable_Status.DP3,
      Portable_Status.MineDet_Num,
      Portable_Status.Charger );
}

void Print_Portable_Status(void)
{
  Print_FanStatus();
  Print_Read_Status();
  Print_Display_Status();
  printf("\n");

}


/*
 * display.c
 *
 *  Created on: Jun 18, 2024
 *      Author: machi
 */

#include <stdio.h>
#include <stdint.h>
#include "gpio.h"
#include "display.h"
#include "max7219.h"
#include "hih8131.h"
#include "fan_control.h"
#include "collect.h"
#include "bq34z100.h"
#include "buzzer.h"


void LED_Init(void)
{
  uint8_t shift = 0;
  uint16_t led_port = 0;

   for(int i=0; i<14; i++)
  {
    led_port = 0x0001 << shift;

    HAL_GPIO_WritePin(GPIOF, (uint16_t)led_port, GPIO_PIN_SET);
    shift++;
  }
}


void Display_Temp_LED(void)
{

  if(Portable_Status.Temp_Range == 3)  //i2c_error
  {
    HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, RESET);
    HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, SET);
  }
  else if(Portable_Status.Temp_Range == 0)  //Normal -> GRN
  {
    HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, SET);
    HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, RESET);
  }
  else if(Portable_Status.Temp_Range == 1) //Danger -> RED
  {
    HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, RESET);
    HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, SET);
  }
  else if(Portable_Status.Temp_Range == 2) //Warning -> YEL
  {
    HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, RESET);
    HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, RESET);
  }

}

void Display_FAN_LED(void)
{
   if(Portable_Status.Temp_Range == 0)  //Normal -> GRN
   {
     HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, SET);
     HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, RESET);
   }
   else if(Portable_Status.Temp_Range == 1) //Danger -> RED
   {
     HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, RESET);
     HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, SET);
   }
   else if(Portable_Status.Temp_Range == 2) //Warning -> YEL
   {
     HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, RESET);
     HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, RESET);
   }

}


void Display_DP_LED(void)
{
  //DP1 LED
  if(Portable_Status.DP1 == 0)       //DP1 Pwr On -> ON
  {
    HAL_GPIO_WritePin(LED_DP1_G_GPIO_Port, LED_DP1_G_Pin, RESET);
  }
  else if(Portable_Status.DP1 == 1)  //DP1 Pwr Off -> OFF
  {
    HAL_GPIO_WritePin(LED_DP1_G_GPIO_Port, LED_DP1_G_Pin, SET);
  }

  //DP2 LED
  if(Portable_Status.DP2 == 0)       //DP2 Pwr On -> ON
  {
    HAL_GPIO_WritePin(LED_DP2_G_GPIO_Port, LED_DP2_G_Pin, RESET);
  }
  else if(Portable_Status.DP2 == 1)  //DP2 Pwr Off -> OFF
  {
    HAL_GPIO_WritePin(LED_DP2_G_GPIO_Port, LED_DP2_G_Pin, SET);
  }

  //DP3 LED
  if(Portable_Status.DP3 == 0)       //DP3 Pwr On -> ON
  {
    HAL_GPIO_WritePin(LED_DP3_G_GPIO_Port, LED_DP3_G_Pin, RESET);
  }
  else if(Portable_Status.DP3 == 1)  //DP3 Pwr Off -> OFF
  {
    HAL_GPIO_WritePin(LED_DP3_G_GPIO_Port, LED_DP3_G_Pin, SET);
  }
}
//AMDS board
void Alarm_MineDet_BUZ(void)
{
   if(MineDet_Num == 0) {
     //Buzzer_Off();
     HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, RESET);
   }
   else {
     //Buzzer_On();
     HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, SET);
   }
}

void Display_Charger_LED(void)
{
  //Charger LED
  if(Portable_Status.Charger == 0)       //Charger Normal -> GRN
  {
    HAL_GPIO_WritePin(LED_CHG_R_GPIO_Port, LED_CHG_R_Pin, SET);
    HAL_GPIO_WritePin(LED_CHG_G_GPIO_Port, LED_CHG_G_Pin, RESET);
  }
  else if(Portable_Status.Charger == 1)  //Charger Abnormal -> RED
  {
    HAL_GPIO_WritePin(LED_CHG_R_GPIO_Port, LED_CHG_R_Pin, RESET);
    HAL_GPIO_WritePin(LED_CHG_G_GPIO_Port, LED_CHG_G_Pin, SET);
  }
}

void Display_SOC_7SEG(void)
{
  uint16_t num;

  num = (uint16_t)Bat.SOC_Val;

   if(num > 100) {
    Display_3Digit("Err");
  }
  else {
    Display_Number(num);
  }
}

void Print_Read_Status(void)
{
//  printf("PSU(%d %d) : ", PSU_Status1, PSU_Status2);
  printf("DP(%d %d %d) : ", DP_Status1, DP_Status2, DP_Status3);
  printf("Buz(%d) : ", MineDet_Num);
  printf("CHG(%d) ", Charger);

  printf("bat: SOC=%d%% V=%dmV AI=%dmA  CC=%dcount IT=%.1fC\n", \
         (uint8_t)Bat.SOC_Val, Bat.Voltage, Bat.AvgCurrent, Bat.CycleCount, Bat.InternalTemp);

  printf("MineDet(%d) : ", MineDet_Num);

  printf("\n");

}

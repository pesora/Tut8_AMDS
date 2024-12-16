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


#define	LED_NUMs	9

void LED_Init(void)
{
  uint8_t shift = 0;
  uint16_t led_port = 0;

   for(int i=0; i<LED_NUMs; i++)
  {
    led_port = 0x0001 << shift;

    HAL_GPIO_WritePin(GPIOF, (uint16_t)led_port, GPIO_PIN_SET);
    shift++;
  }
}


void LED_SelfTest(void)
{
  uint8_t shift = 0;
  uint16_t led_port = 0;

  while(1)
  {
    shift = 0;
    for(int i=0; i<LED_NUMs; i++)
    {
      led_port = 0x0001 << shift;
      HAL_GPIO_WritePin(GPIOF, (uint16_t)led_port, GPIO_PIN_RESET);
      HAL_Delay(500);
      HAL_GPIO_WritePin(GPIOF, (uint16_t)led_port, GPIO_PIN_SET);
      shift++;
    }
  }

}


void Display_Temp_LED(void)
{

  if(Console_Status.Temp_Range == 3)  //i2c_error
  {
    HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, RESET);
    HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, SET);
  }
  else if(Console_Status.Temp_Range == 0)  //Normal -> GRN
  {
    HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, SET);
    HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, RESET);
  }
  else if(Console_Status.Temp_Range == 1) //Danger -> RED
  {
    HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, RESET);
    HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, SET);
  }
  else if(Console_Status.Temp_Range == 2) //Warning -> YEL
  {
    HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, RESET);
    HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, RESET);
  }

}

//void Display_FAN_LED(void)
//{
//   if(Console_Status.Temp_Range == 0)  //Normal -> GRN
//   {
//     HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, SET);
//     HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, RESET);
//   }
//   else if(Console_Status.Temp_Range == 1) //Danger -> RED
//   {
//     HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, RESET);
//     HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, SET);
//   }
//   else if(Console_Status.Temp_Range == 2) //Warning -> YEL
//   {
//     HAL_GPIO_WritePin(LED_TEMP_R_GPIO_Port, LED_TEMP_R_Pin, RESET);
//     HAL_GPIO_WritePin(LED_TEMP_G_GPIO_Port, LED_TEMP_G_Pin, RESET);
//   }
//
//}

void Display_FAN1_LED(void)
{

  if(Console_Status.FAN1 == 0)       //Normal -> GRN
   {
     HAL_GPIO_WritePin(LED_FAN1_R_GPIO_Port, LED_FAN1_R_Pin, SET);
     HAL_GPIO_WritePin(LED_FAN1_G_GPIO_Port, LED_FAN1_G_Pin, RESET);
   }
   else if(Console_Status.FAN1 == 1) //Danger -> RED
   {
     HAL_GPIO_WritePin(LED_FAN1_R_GPIO_Port, LED_FAN1_R_Pin, RESET);
     HAL_GPIO_WritePin(LED_FAN1_G_GPIO_Port, LED_FAN1_G_Pin, SET);
   }
   else if(Console_Status.FAN1 == 2) //Warning -> YEL
   {
     HAL_GPIO_WritePin(LED_FAN1_R_GPIO_Port, LED_FAN1_R_Pin, RESET);
     HAL_GPIO_WritePin(LED_FAN1_G_GPIO_Port, LED_FAN1_G_Pin, RESET);
   }

}

void Display_FAN2_LED(void)
{
   if(Console_Status.FAN2 == 0)       //Normal -> GRN
   {
     HAL_GPIO_WritePin(LED_FAN2_R_GPIO_Port, LED_FAN2_R_Pin, SET);
     HAL_GPIO_WritePin(LED_FAN2_G_GPIO_Port, LED_FAN2_G_Pin, RESET);
   }
   else if(Console_Status.FAN2 == 1) //Danger -> RED
   {
     HAL_GPIO_WritePin(LED_FAN2_R_GPIO_Port, LED_FAN2_R_Pin, RESET);
     HAL_GPIO_WritePin(LED_FAN2_G_GPIO_Port, LED_FAN2_G_Pin, SET);
   }
   else if(Console_Status.FAN2 == 2) //Warning -> YEL
   {
     HAL_GPIO_WritePin(LED_FAN2_R_GPIO_Port, LED_FAN2_R_Pin, RESET);
     HAL_GPIO_WritePin(LED_FAN2_G_GPIO_Port, LED_FAN2_G_Pin, RESET);
   }

}


void Display_PSU_LED(void)
{
  if(Console_Status.PSU == 0)       //Normal -> GRN
  {
    HAL_GPIO_WritePin(LED_PSU_R_GPIO_Port, LED_PSU_R_Pin, SET);
    HAL_GPIO_WritePin(LED_PSU_G_GPIO_Port, LED_PSU_G_Pin, RESET);
  }
  else if(Console_Status.PSU == 1)  //Danger -> RED
  {
    HAL_GPIO_WritePin(LED_PSU_R_GPIO_Port, LED_PSU_R_Pin, RESET);
    HAL_GPIO_WritePin(LED_PSU_G_GPIO_Port, LED_PSU_G_Pin, SET);
  }
  else if(Console_Status.PSU == 2)  //Warning -> YEL
  {
    HAL_GPIO_WritePin(LED_PSU_R_GPIO_Port, LED_PSU_R_Pin, RESET);
    HAL_GPIO_WritePin(LED_PSU_G_GPIO_Port, LED_PSU_G_Pin, RESET);
  }
}

void Display_DP_LED(void)
{
  //DP1 LED
  if(Console_Status.DP1 == 0)       //DP1 Pwr On -> ON
  {
    HAL_GPIO_WritePin(LED_DP1_G_GPIO_Port, LED_DP1_G_Pin, RESET);
  }
  else if(Console_Status.DP1 == 1)  //DP1 Pwr Off -> OFF
  {
    HAL_GPIO_WritePin(LED_DP1_G_GPIO_Port, LED_DP1_G_Pin, SET);
  }

  //DP2 LED
  if(Console_Status.DP2 == 0)       //DP2 Pwr On -> ON
  {
    HAL_GPIO_WritePin(LED_DP2_G_GPIO_Port, LED_DP2_G_Pin, RESET);
  }
  else if(Console_Status.DP2 == 1)  //DP2 Pwr Off -> OFF
  {
    HAL_GPIO_WritePin(LED_DP2_G_GPIO_Port, LED_DP2_G_Pin, SET);
  }

}

void Alarm_MineDet_BUZ(void)
{
   if(MineDet_Num == 0) {
     Buzzer_Off();
     HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, SET);
   }
   else {
     Buzzer_On();
     HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, RESET);
   }
}


void Print_Read_Status(void)
{
  printf("PSU(%d %d) : ", PSU_Status1, PSU_Status2);
  printf("DP(%d %d)  : ", DP_Status1, DP_Status2);
  printf("Buz(%d)    : ", MineDet_Num);
  printf("MineDet(%d): ", MineDet_Num);

  printf("\n");

}

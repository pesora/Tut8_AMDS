/*
 * buzzer.c
 *
 *  Created on: Aug 21, 2024
 *      Author: machi
 */

#include "tim.h"
#include "buzzer.h"

#define BUZ_FREQ  2700  //2.7KHz

extern TIM_HandleTypeDef htim5;
double timer5_cnt_freq=0;

void Buzzer_Init(void)
{
  Buzzer_Off();
  Set_Buzzer_Frequency(BUZ_FREQ);
}

void Buzzer_On(void)
{
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
}

void Buzzer_Off(void)
{
    HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_4);
}

void Set_Buzzer_Frequency(uint32_t frequency)
{
  //Timer5 belongs to APB1 timer clock
  double APB1Freq = 0;

  APB1Freq = HAL_RCC_GetPCLK1Freq()*2;

  uint32_t period = (APB1Freq / (htim5.Init.Prescaler + 1)) / frequency - 1;

  //uint32_t period = (APB1Freq / (htim5.Init.Prescaler + 1)) / frequency - 1;
  __HAL_TIM_SET_AUTORELOAD(&htim5, period);
  __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, period / 2);
}

/*
 * fan_control.c
 *
 *  Created on: May 25, 2024
 *      Author: orion
 */


#include <stdio.h>
#include "fan_control.h"
#include "tim.h"
#include "user_timer.h"
#include "collect.h"
#include "debug_uart.h"


static uint8_t pwm_ch = 0;
static uint32_t IC_Val1[MAX_FAN_QTY] = {0, };
static uint32_t IC_Val2[MAX_FAN_QTY] = {0, };
static int Is_First_Captured[MAX_FAN_QTY] = {0, };
static float frequency[MAX_FAN_QTY] = {0, };
static uint32_t Difference = 0;
static uint8_t capture_done[MAX_FAN_QTY] = {0, };

static uint16_t ccr=0;
static uint16_t set_rpm = 1000;

static uint8_t ch = 0;

static uint8_t step = 0;
uint8_t fan_step = 2;
uint8_t fan_done = 0;

FanData_t Fan[MAX_FAN_QTY];
FanData_t DbgFan[MAX_FAN_QTY];  // for Debug

static uint8_t FAN_IsRPMOverRange(uint8_t ch, uint16_t rpm);

void FAN_Init(void)
{

  TIM1->CCR1 = 0;
  TIM1->CCR2 = 0;
  TIM1->CCR3 = 0;
  TIM3->CCR1 = 0;
  TIM3->CCR2 = 0;
  TIM3->CCR3 = 0;


  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);

  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);
  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);
}


void FAN_Set_RPM(uint8_t fan_step)
{
  if(fan_step == 0) {
    set_rpm = 0;
    ccr = (set_rpm*(TIM1->ARR))/MAX_RPM;
  }
  else if(fan_step == 1) {
    set_rpm = 1000;
    ccr = (set_rpm*(TIM1->ARR))/MAX_RPM;
  }
  else if(fan_step == 2) {
    set_rpm = 1500;
    ccr = (set_rpm*(TIM1->ARR))/MAX_RPM;
  }
  else if(fan_step == 3) {
    set_rpm = 2000;
    ccr = (set_rpm*(TIM1->ARR))/MAX_RPM;
 }
  else if(fan_step == 4) {
    set_rpm = MAX_RPM;
    ccr = (set_rpm*(TIM1->ARR))/MAX_RPM;
  }
  else {
   ;
  }
  TIM1->CCR1 = ccr;
  TIM1->CCR2 = ccr;
  TIM1->CCR3 = ccr;
  TIM3->CCR1 = ccr;
  TIM3->CCR2 = ccr;
  TIM3->CCR3 = ccr;

}

void FAN_Read_FansStatus(void)
{
  FAN_Set_RPM(fan_step);

  if(fan_done == 0) {
    fan_done = FAN_Read_RPM();
  }

}

uint8_t FAN_Read_RPM(void)
{
	uint8_t ret = 0;

	 switch(step)
	 {
	 case 0:
		Stop_InputCapute();
		Start_InputCapute(ch);
		if(fan_step==2) {
			uTimer_Regist(((uint8_t)uTimerFanCheck), FAN_TIMERCNT1);
		}
		else {
			uTimer_Regist(((uint8_t)uTimerFanCheck), FAN_TIMERCNT2);
		}
		step = 1;
		break;

	 case 1:
		  if(uTimer_CheckTimeOut((uint8_t)uTimerFanCheck) == TRUE)
		  {
        Fan[ch].err = 1;
        step = 2;
        break;
		  }
		  if(capture_done[ch] == 1 )
		  {
		    Fan[ch].err = 0;
        step = 2;
        break;
		  }

      step = 1;
      break;

	 case 2:
		Stop_InputCapute();
		Fan[ch].rpm = (int16_t) (frequency[ch]*60/2);
		Fan[ch].err = FAN_IsRPMOverRange(ch, Fan[ch].rpm);

		capture_done[ch] = 0;

		step = 3;
		break;

	 case 3:
		ch++;
		if(ch>(MAX_FAN_QTY-1))
		{
			//copy the result for debugging
			for(int i=0; i<MAX_FAN_QTY; i++) {
				DbgFan[i].rpm = Fan[i].rpm;
				DbgFan[i].err = Fan[i].err;
			}
			//clear frequency
			for(int i=0; i<MAX_FAN_QTY; i++) {
				frequency[i] = 0;
			}
			ch = 0;
			ret = 1;
		}
		//HAL_Delay(10);
		step = 0;
		break;

	 default:
		 step = 0;
		 break;
	 }//switch

	return ret;
}

static uint8_t FAN_IsRPMOverRange(uint8_t ch, uint16_t rpm)
{
  uint8_t error = 0;

  if(rpm<MIN_RPM || rpm>OVER_MAX_RPM)
    error = 1;
  else
    error = 0;

  return error;
}


FanData_t * FAN_GetFanData(void)
{
  FanData_t * pFan;

  pFan = &Fan[0];


  return pFan;
}

void Print_FanStatus(void)
{
	printf("\nFanStep[%d] ", fan_step);
	printf("%d %d %d : %d %d %d \n", DbgFan[0].err, DbgFan[1].err, DbgFan[2].err, DbgFan[3].err, DbgFan[4].err, DbgFan[5].err );
	printf("%d %d %d : %d %d %d \n", DbgFan[0].rpm, DbgFan[1].rpm, DbgFan[2].rpm, DbgFan[3].rpm, DbgFan[4].rpm, DbgFan[5].rpm );
}


void Stop_InputCapute(void)
{
  HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_1);
  HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_3);
  HAL_TIM_IC_Stop_IT(&htim2, TIM_CHANNEL_4);

  HAL_TIM_IC_Stop_IT(&htim4, TIM_CHANNEL_1);
  HAL_TIM_IC_Stop_IT(&htim4, TIM_CHANNEL_2);
  HAL_TIM_IC_Stop_IT(&htim4, TIM_CHANNEL_3);

}

void Start_InputCapute(uint8_t channel)
{

  if(channel == 0)
  {
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
  }
  else if(channel == 1)
  {
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);
  }
  else if(channel == 2)
  {
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);
  }
  else if(channel == 3)
  {
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
  }
  else if(channel == 4)
  {
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_2);
  }
  else if(channel == 5)
  {
    HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_3);
  }
  pwm_ch = channel;
}

/* Measure Frequency */
void TIM_IC_Capture(TIM_HandleTypeDef *htim, uint8_t ch, uint32_t tim_channel)
{
  if (Is_First_Captured[ch]==0) // if the first rising edge is not captured
  {
    IC_Val1[ch] = HAL_TIM_ReadCapturedValue(htim, tim_channel); // read the first value
    Is_First_Captured[ch] = 1;  // set the first captured as true
  }

  else   // If the first rising edge is captured, now we will capture the second edge
  {
    IC_Val2[ch] = HAL_TIM_ReadCapturedValue(htim, tim_channel);  // read second value

    if (IC_Val2[ch] > IC_Val1[ch])
    {
      Difference = IC_Val2[ch]-IC_Val1[ch];
    }

    else if (IC_Val1[ch] > IC_Val2[ch])
    {
      Difference = (0xffffffff - IC_Val1[ch]) + IC_Val2[ch];
    }

    float refClock = TIMCLOCK/(PRESCALAR);

    frequency[ch] = refClock/Difference;

    __HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter
    Is_First_Captured[ch] = 0; // set it back to false
    capture_done[ch] = 1;
  }
}

//Input Capture time a channel  = 30ms
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

  if ((htim->Instance == TIM2) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) && (pwm_ch == 0))
  {
    TIM_IC_Capture(htim, 0, TIM_CHANNEL_1);
    return;
  }

  if ((htim->Instance == TIM2) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) && (pwm_ch == 1))
  {
    TIM_IC_Capture(htim, 1, TIM_CHANNEL_2);
    return;
  }

  if ((htim->Instance == TIM2) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4) && (pwm_ch == 2))
  {
    TIM_IC_Capture(htim, 2, TIM_CHANNEL_3);
    return;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  if ((htim->Instance == TIM4) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) && (pwm_ch == 3))
  {
    TIM_IC_Capture(htim, 3, TIM_CHANNEL_1);
    return;
  }

  if ((htim->Instance == TIM4) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) && (pwm_ch == 4))
  {
    TIM_IC_Capture(htim, 4, TIM_CHANNEL_2);
    return;
  }

  if ((htim->Instance == TIM4) && (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3) && (pwm_ch == 5))
  {
    TIM_IC_Capture(htim, 5, TIM_CHANNEL_3);
    return;
  }
}



void Control_Fan(Console_Status_t *Status)
{

  uint8_t temp_status = GetTempStatus();

  // Temp is within Normal range
  if( temp_status == 0 )
  {
    fan_step = 2;
  }
  //Temp is within Warning range
  else if( temp_status == 2 )
  {
    fan_step = 3;
  }
  // Temp is within Danger range
  else if( temp_status == 1 )
  {
    fan_step = 4;
  }

  //I2C Error
  else if( temp_status == 3 )
  {
    fan_step = 0;
  }

}


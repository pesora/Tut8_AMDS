//==================================================================
//        Sensor Tech Inc
// -----------------------------------------------------------------
//  PROJECT			: Wearable Sensor
//	PRODUCT NAME	: WeSen(Werable Sensor)
//	FILE NAME		: MovingAverage.c
//  PROCESSOR		: efm32GG990F1024
//  COMPILER		: IAR 6.3
//  AUTHOR			: Hwang Seongjin
//  DATE			: 2016.11.17
//
//  DESCRIPTION		: �̵������ ���ϴ� �Լ�
//  NOTES			: CDC�� ���� �о�帰 �������� �̵������
//					  ���Ѵ�
//===================================================================
#include "ema.h"

////////////////////////////////////////////////////////////////
//
//	Exponential Moving Average
//
/////////////////////////////////////////////////////////////////

float	K;						//K=Smoothing Constant
ENVDATA_t currEmaData[MAX_FAN_CH];	//current ema data
ENVDATA_t prevEmaData[MAX_FAN_CH];	//previous ema data
////////////////////////////////////////////////////////////////
// n1, n2 : Window Size / Smoothing Constant
void EMA_Init(uint8_t n) {
	K = 2.0/(float)(n+1);	//n: Smoothing Constant for K[0]
}

////////////////////////////////////////////////////////////////
// Calculate Exponential Moving Average
// ch   : fan channel
// data	: for ema data
ENVDATA_t GetEma(uint8_t ch, ENVDATA_t data)
{
	//calculate ema
  currEmaData[ch].fan_rpm = K*(data.fan_rpm -prevEmaData[ch].fan_rpm) + prevEmaData[ch].fan_rpm;

	//Save current ema data to previous ema data buff
	prevEmaData[ch].fan_rpm = currEmaData[ch].fan_rpm;

	return currEmaData[ch];
}


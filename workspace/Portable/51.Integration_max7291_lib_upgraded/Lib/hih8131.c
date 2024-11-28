/*
 * hmtp.c
 *
 *  Created on: Jun 1, 2024
 *      Author: orion
 */

#include <stdio.h>
#include "hih8131.h"
#include "main.h"
#include "user_timer.h"


#include "i2c.h"

HMTP_Data_t HMTP_Data[MAX_HMTP_CH];
uint8_t data_buf[2][4] = {0,};
uint16_t devAddr = ((uint16_t)0x0027U << 1);
uint8_t i2c_error[2] = {0,};

static void HMTP_Reset(void);

void HMTP_Read_Temp_Value(void)
{
  Read_HIH8131Data();
  HMTP_CnvData(data_buf);
}

void HMTP_Init(void) {

    HMTP_Reset();

    Delay_clock(1U);/*범용 지연함수*/
}

static void HMTP_Reset(void) {

	HAL_GPIO_WritePin(TEMP_I2C1_nRESET_GPIO_Port, TEMP_I2C1_nRESET_Pin,GPIO_PIN_SET);
	Delay_clock(10U);
	HAL_GPIO_WritePin(TEMP_I2C1_nRESET_GPIO_Port, TEMP_I2C1_nRESET_Pin,GPIO_PIN_RESET);
	Delay_clock(200U);
	HAL_GPIO_WritePin(TEMP_I2C1_nRESET_GPIO_Port, TEMP_I2C1_nRESET_Pin,GPIO_PIN_SET);
	Delay_clock(10U);
}

void Read_HIH8131Data(void)
{
  for(int ch=0; ch<MAX_HMTP_CH; ch++)
  {
    uint8_t ch_data = 0x01U << ch;

    HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR_TCA9546, &ch_data, 1U, I2C_TIMEOUT);
    Delay_clock(100U);

    HAL_I2C_Master_Transmit(&hi2c1, devAddr, &ch_data, 0U, I2C_TIMEOUT);
    HAL_Delay(100U);

    HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR_TCA9546, &ch_data, 1, I2C_TIMEOUT);
    Delay_clock(200U);
    if(HAL_I2C_Master_Receive(&hi2c1, devAddr, (uint8_t *)&data_buf[ch], 4, I2C_TIMEOUT) != HAL_OK)
    {
      i2c_error[ch] = 1;
    }
    else
    {
      i2c_error[ch] = 0;
    }

  }
}

void HMTP_CnvData(uint8_t data_buf[][4]) {

	for(int ch=0; ch<MAX_HMTP_CH; ch++)
	{
		uint16_t  Humidity, Humidity_H, Humidity_L;
		uint16_t  Temperature, Temperature_H, Temperature_L;

		if(i2c_error[ch] == 0)
		{
		  uint8_t temp_data_buf = data_buf[ch][0U];
		  Humidity_H = ((uint16_t)temp_data_buf);
		  Humidity_H = Humidity_H << 8U;
		  temp_data_buf = data_buf[ch][1U];
		  Humidity_L = ((uint16_t)temp_data_buf);
		  Humidity = (Humidity_H | Humidity_L) & 0x3FFFU;

		  temp_data_buf = data_buf[ch][2U];
		  Temperature_H = ((uint16_t)temp_data_buf);
		  Temperature_H = Temperature_H << 8U;
		  temp_data_buf = data_buf[ch][3U];
		  Temperature_L = ((uint16_t)temp_data_buf);
		  Temperature = (((Temperature_H | Temperature_L) >> 2U) + 1U) & 0x3FFFU;

		  HMTP_Data[ch].fHum = ((float)Humidity * 100.0F)/(16383.0F);
		  HMTP_Data[ch].fTemp = (((float)Temperature * 165.0F)/(16383.0F)) - 40.0F;

      HMTP_Data[ch].error = 0;
		}
		else
		{
      HMTP_Data[ch].error = 1;

		}
	}
}

void Print_HMTP_Data(void)
{
	for(int ch=0; ch<MAX_HMTP_CH; ch++)
	{
		if(i2c_error[ch] == 0)
		{
			printf("ch(%d) : H = %.1f %%, T = %.1f C \n", ch, HMTP_Data[ch].fHum, HMTP_Data[ch].fTemp);
		}
		else {
			printf("i2c_error_%d(%d)\n", ch, i2c_error[ch]);
		}
	}
}



/*
 * bq34z100.c
 *
 *  Created on: Jun 4, 2024
 *      Author: machi
 */

#include <stdio.h>
#include <stdint.h>
#include "bq34z100.h"
#include "i2c.h"
#include "utility.h"
#include "usart.h"


BatData_t Bat;

HAL_StatusTypeDef error;
//uint8_t txbuf[3] = {0, 2, 0};
uint8_t rxbuf[2] = {0,};
uint16_t BatData16[6] = {0};
float temp_val;
int16_t ai_val;

uint16_t bq34z100_StdCmd(uint8_t command);
uint16_t bq34z100_ExtCmd(uint8_t command);
uint16_t bq34z100_SubCmd(uint16_t subcommand);

uint8_t i2c3_error = 0;

void ReadBq34z100(void);
void PrintBq34z100Data(void);

void ReadBq34z100(void)
{
      BatData16[0] = bq34z100_StdCmd(SOC);
      BatData16[1] = bq34z100_StdCmd(VOLT);
      BatData16[2] = bq34z100_StdCmd(AI);
      //ai_val = (int16_t)(BatData16[2]&0xFFFF);
      BatData16[3] = bq34z100_ExtCmd(CC);
      BatData16[4] = bq34z100_ExtCmd(INTTEMP);
      //temp_val = (float)( (float)BatData16[4]/10.0f - KELVIN);
      BatData16[5] = bq34z100_SubCmd(FW_VERSION);
}



uint16_t bq34z100_StdCmd(uint8_t command)
{
  uint16_t ret = 0;

  error = HAL_I2C_Mem_Read(&hi2c3, I2C_BQ34Z100_ADDR, command, 1,(uint8_t*)rxbuf, 2, HAL_MAX_DELAY);
  if (error != HAL_OK)
  {
	i2c3_error = 1;
    //printf("i2c rx error: STD_CMD\n");
  }
  else
  {
	i2c3_error = 0;
    ret = make16(&rxbuf[1], &rxbuf[0]);
  }
  
   //print e2c3 error
  if(i2c3_error==1) {
	  printf("i2c3_comm_error1\n");
  }


  return ret;
}

uint16_t bq34z100_ExtCmd(uint8_t command)
{
  uint16_t ret = 0;

  error = HAL_I2C_Mem_Read(&hi2c3, I2C_BQ34Z100_ADDR, command, 1,(uint8_t*)rxbuf, 2, HAL_MAX_DELAY);
  if (error != HAL_OK)
  {
	i2c3_error = 1;
    //printf("i2c rx error: EXT_CMD\n");
  }
  else {
    i2c3_error = 0;
    ret = make16(&rxbuf[1], &rxbuf[0]);
  }

  //print e2c3 error
  if(i2c3_error==1) {
	  printf("i2c3_comm_error2\n");
  }

  return ret;
}

uint16_t bq34z100_SubCmd(uint16_t subcommand)
{
  uint16_t ret = 0;

  uint8_t command[3];
  command[0] = 0x00;
  command[1] = make8(subcommand, 0);
  command[2] = make8(subcommand, 1);

  error = HAL_I2C_Master_Transmit(&hi2c3, I2C_BQ34Z100_ADDR, command, 3, HAL_MAX_DELAY);
  if (error != HAL_OK)
  {
	i2c3_error = 1;
    //printf("i2c tx error: SUB_CMD_TX\n");
  }
  else {
	i2c3_error = 0;
  }
  error = HAL_I2C_Mem_Read(&hi2c3, I2C_BQ34Z100_ADDR, CNTL, 1,(uint8_t*)rxbuf, 2, HAL_MAX_DELAY);
  if (error != HAL_OK)
  {
	i2c3_error = 1;
    //printf("i2c rx error: SUB_CMD_RX\n");
  }
  else
  {
	i2c3_error = 0;
    ret = make16(&rxbuf[1], &rxbuf[0]);
  }

  //print e2c3 error
  if(i2c3_error==1) {
	  printf("i2c_comm_error3\n");
  }

  return ret;
}

void PrintBq34z100Data(void)
{
  printf("SOC    : 0x%04X, [%d %%]\n", BatData16[0], BatData16[0]);
  printf("VOLT   : 0x%04X, [%d mV]\n", BatData16[1], BatData16[1]);
  printf("AI     : 0x%04X, [%d mA]\n", (int16_t)ai_val, (int16_t)BatData16[2]);
  printf("CC     : 0x%04X, [%d times]\n", BatData16[3], BatData16[3]);
  printf("INTTEMP: 0x%04X, [%.1f C]\n", BatData16[4], (float)temp_val);
  printf("FW VER : 0x%04X, [Ver-%d]\n", BatData16[5], BatData16[5]);
}

extern UART_HandleTypeDef huart3;
uint8_t DeviceAddr[25] = {0, };
uint8_t Space[] = " - ";
uint8_t StartMSG[] = "Starting I2C Scanning: \r\n";
uint8_t EndMSG[] = "Done! \r\n\r\n";


uint8_t i2c_scan(void)
{
	uint8_t ret = 0;

	  uint8_t i = 0, status;

    /*-[ I2C Bus Scanning ]-*/
    HAL_UART_Transmit(&huart3, StartMSG, sizeof(StartMSG), 10000);
    for(i=1; i<128; i++)
    {
    	status = HAL_I2C_IsDeviceReady(&hi2c3, (uint16_t)(i<<1), 3, 5);
        if (status != HAL_OK) /* No ACK Received At That Address */
        {
            //HAL_UART_Transmit(&huart3, Space, sizeof(Space), 10000);
        	ret = 0;
        }
        else if(status == HAL_OK)
        {
            sprintf((char*)DeviceAddr, "0x%X", i);
            HAL_UART_Transmit(&huart3, DeviceAddr, sizeof(DeviceAddr), 10000);
        	ret = 1;
        	break;
       }
    }
    HAL_UART_Transmit(&huart3, EndMSG, sizeof(EndMSG), 10000);
    /*--[ Scanning Done ]--*/
    return ret;
}

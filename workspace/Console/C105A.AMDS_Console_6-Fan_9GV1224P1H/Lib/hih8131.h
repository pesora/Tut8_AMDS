/*
 * hmtp.h
 *
 *  Created on: Jun 1, 2024
 *      Author: orion
 */

#ifndef HIH8131_H_
#define HIH8131_H_

#include <stdint.h>


typedef struct tagHMTP_Data_t
{
	float	fTemp;
	float	fHum;
	uint8_t error;
}HMTP_Data_t;

#define MAX_HMTP_CH			2
#define	I2C_ADDR_TCA9546	((uint16_t)0x0070U << 1)
#define I2C_ADDR_HIH8131	((uint16_t)0x2007U << 1);
#define	I2C_TIMEOUT			10U

extern uint8_t data_buf[][4];
extern uint8_t i2c_error[];
extern HMTP_Data_t HMTP_Data[];

void HMTP_Init(void);
void HMTP_Read_Temp_Value(void);
void Read_HIH8131Data(void);
void HMTP_CnvData(uint8_t data_buf[][4]);
void Print_HMTP_Data(void);

#endif /* HIH8131_H_ */

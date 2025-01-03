/*
 * display.h
 *
 *  Created on: Jun 18, 2024
 *      Author: machi
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_


void LED_Init(void);
void LED_SelfTest(void);


void Display_SelfTest(void);
void Display_Temp_LED(void);
void Display_FAN1_LED(void);
void Display_FAN2_LED(void);
void Display_PSU_LED(void);
void Display_DP_LED(void);
void Alarm_MineDet_BUZ(void);

void Print_Read_Status(void);


#endif /* DISPLAY_H_ */


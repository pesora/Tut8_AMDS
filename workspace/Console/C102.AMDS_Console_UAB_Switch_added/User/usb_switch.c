/*
 * usb_switch.c
 *
 *  Created on: Dec 9, 2024
 *      Author: machi
 */

#include "main.h"
#include "usb_switch.h"


uint8_t USB_Switch1;
uint8_t USB_Switch2;

void Read_Usb_Switch(void)
{
	USB_Switch1 = (uint8_t)HAL_GPIO_ReadPin(SEL_DP1_GPIO_Port, SEL_DP1_Pin);
	USB_Switch2 = (uint8_t)HAL_GPIO_ReadPin(SEL_DP2_GPIO_Port, SEL_DP2_Pin);
}

void Output_Usb_Switch(void)
{
    HAL_GPIO_WritePin(USB_SEL_SW1_GPIO_Port, USB_SEL_SW1_Pin, USB_Switch1);
    HAL_GPIO_WritePin(USB_SEL_SW2_GPIO_Port, USB_SEL_SW2_Pin, USB_Switch2);

}


void USB_Selec_Switch(void)
{
	Read_Usb_Switch();
	Output_Usb_Switch();
}

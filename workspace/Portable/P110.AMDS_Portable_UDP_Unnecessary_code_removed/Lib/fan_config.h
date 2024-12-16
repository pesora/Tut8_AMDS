/*
 * fan_config.h
 *
 *  Created on: May 25, 2024
 *      Author: orion
 */

#ifndef FAN_CONFIG_H_
#define FAN_CONFIG_H_

//-------------------------------------------
//Specification of DC Fan
//-------------------------------------------
// Model Name  : 9GA0812P4G001 / 12V
//
// PWM Frequency : 25kHz
// Size : 80x80x25mm
// Max Rotational speed(@100%) : 6800 rpm
// Min Rotational speed(@ 25%) : 1500 rpm
// Input Power(typical)   : 5.76W
// Input Current(typical) : ? A
// Operating Voltage : 12V
//

#define MAX_FAN_QTY		2
#define MAX_RPM       	6800
#define MIN_RPM       	1500
#define OVER_MAX_RPM    7000

#define TIMCLOCK      90000000
#define PRESCALAR     90    //Prescaler used in Input Capture for TIM2 and TIM4


void FAN_Read_FansSensor(void);


#endif /* FAN_CONFIG_H_ */

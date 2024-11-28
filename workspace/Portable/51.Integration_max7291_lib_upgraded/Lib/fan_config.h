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
// Model Name  : NOCTUA NF-A8 5V PWM
//
// Size : 80x80x25mm
// Rotational speed(+/- 10%) : 2200RPM
// Min Rotational speed @ 20%PWM (+/- 20%): 450RPM
// Input Power(typical)   : 0.74W
// Input Current(typical) : 0.15A
// Operating Voltage : 5V
//
#define MAX_FAN_QTY		6
#define MAX_RPM       	2200  //2250
#define MIN_RPM       	900
#define OVER_MAX_RPM    2500

#define TIMCLOCK      90000000
#define PRESCALAR     90    //Prescaler used in Input Capture for TIM2 and TIM4


void FAN_Read_FansSensor(void);


#endif /* FAN_CONFIG_H_ */

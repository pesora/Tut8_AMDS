/*
 * pid.c
 *
 *  Created on: May 2, 2024
 *      Author: orion
 */

#include <stdint.h>
#include "tim.h"
#include "pid.h"


//-----------------------
//PID Control
//-----------------------
int16_t setrpm;
int16_t currpm;
int16_t err;
int16_t i_err;
int16_t d_err;
int16_t err1;
uint16_t kp_term;
uint16_t ki_term;
uint16_t kd_term;
int16_t control[2];

//uint16_t kp = 0.5;
//uint16_t ki = 0.8;
//uint16_t kd = 0.1;

uint16_t kp = 2.0;
uint16_t ki = 1.0;
uint16_t kd = 0.01;

//-----------------------------------------------
int16_t fan_control(uint8_t ch, int setrpm, int currpm)
{
  err=setrpm-currpm;      //오차값(세팅값과 현재값의 차이)
  i_err =(err+err1);      //i오차값
  d_err=(err-err1);       //d 오차값

  kp_term=(uint16_t)kp*err;     //kp_term=kp*err;
  ki_term=(uint16_t)ki*i_err;   //i_err+=err*dt;      //ki_term=ki*i_err;
  kd_term=(uint16_t)kd*d_err;   //d_err=(err-duty)/dt;    //kd_term=kd*d_err;


  control[ch]=kp_term+ki_term+kd_term;  //조작량=Kp×편차+Ki×편차의 누적값+Kd×전회 편차와의 차

  err1=err;                     //현재의 오차값을 err1에 저장한다. (오차값 비교목적)

  control[ch] = (TIM1->CCR1) + control[ch]; //조작된 ccr값

  if(control[ch]>400)
  {
    control[ch]=400;            //max ccr
  }
  else if(control[ch]<0)
  {
    control[ch]=0;              //min ccr
  }
  else
  {
  }

  return control[ch];
}

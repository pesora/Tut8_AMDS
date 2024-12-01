/*
 * UserTimer.c
 *
 *  Created on: May 25, 2024
 *      Author: orion
 */


#include "tim.h"
#include "user_timer.h"

int32_t LongTimer[uTimerMax];
uint32_t ResetCounter;
uint8_t ResetTxState = 0U;
volatile uint32_t msTicks; /* counts 1ms timeTicks */

void uTimer_Init(void) {

  uint32_t ii;

  /* uTimer 변수 초기화 */
  for (ii = 0U; ii < ((uint32_t)uTimerMax); ii++ ){
    LongTimer[ii] = -1;
  }

}

void uTimer_Regist(const uint8_t uTimeId, const int32_t uTimeCnt) {
  /**
  1. uTimer ID 등록
  **/

  /* uTimer ID 등록 */
  if (uTimeId < (uint8_t)uTimerMax)
  {
    LongTimer[uTimeId] = uTimeCnt;
  }
}/* End of uTimer_Regist func. */

uint8_t uTimer_CheckTimeOut(const uint8_t uTimeId) {
  /**
  1. uTimer ID 타임아웃 체크
  **/

  uint8_t result = FALSE;

  /* uTimer ID 타임아웃 체크 */
  if (uTimeId < (uint8_t)uTimerMax)
  {
    if (LongTimer[uTimeId] == 0){
      LongTimer[uTimeId] = -1;
      result = TRUE;
    }
    else{
      result = FALSE;
    }
  }

  return (result);
}/* End of uTimer_CheckTimeOut func. */

void HAL_SYSTICK_Callback(void)
{
  uint8_t ii;

  msTicks++;	//1ms Tick

  /* 등록된 uTimer ID 타이머카운터 값 감소 */
  for (ii = 0U ; ii < ((uint8_t)uTimerMax); ii++){
    if (LongTimer[ii] > 0) {
      LongTimer[ii]--;
    }
  }

}/* End of HAL_SYSTICK_Callback func. */


void HAL_IncTick(void)
{
  uwTick += uwTickFreq;
}

uint32_t HAL_GetTick(void)
{
  return uwTick;
}


void Delay_clock(const uint32_t iCount) {
  uint32_t  delay_clk;

  for(delay_clk = 0U; delay_clk < iCount; delay_clk++){}

}


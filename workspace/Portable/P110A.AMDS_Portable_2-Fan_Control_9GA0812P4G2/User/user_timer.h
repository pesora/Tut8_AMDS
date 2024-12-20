/*
 * UserTimer.h
 *
 *  Created on: May 25, 2024
 *      Author: orion
 */

#ifndef USER_TIMER_H_
#define USER_TIMER_H_

#include <stdint.h>

#define   mills()   HAL_GetTick()


#define   FALSE   0
#define   TRUE    1
#define   FAN_TIMERCNT      100
#define   FAN_TIMERCNT1     150
#define   FAN_TIMERCNT2     150
#define	  KEY_TIMERCNT		  200

typedef enum{
  uTimerRsvID0 = 0U,
  uTimerFanCheck,   /* 1  */
  uTimerDebounce,
  uTimerMax          /* 6 */
} TIMERID_ENUM;

extern volatile uint32_t msTicks;
extern int32_t LongTimer[uTimerMax];
extern uint32_t ResetCounter;
extern uint8_t ResetTxState;


void uTimer_Init(void);                /* uTimer 초기화.  */
void uTimer_Regist(const uint8_t uTimeId, const int32_t uTimeCnt); /* 타이머 ID 등록.  */
uint8_t uTimer_CheckTimeOut(const uint8_t uTimeId);             /* 타임아웃 체크.   */

uint32_t HAL_GetTick(void);
void Delay_clock(const uint32_t iCount);
#endif /* USER_TIMER_H_ */

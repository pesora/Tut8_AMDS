/*
 * udp_protocol.h
 *
 *  Created on: Aug 6, 2024
 *      Author: machi
 */

#ifndef UDP_PROTOCOL_H_
#define UDP_PROTOCOL_H_

#include <stdint.h>


#define ID_REQUEST  (uint16_t)0x0001
#define ID_REPLY    (uint16_t)0x0101
#define ID_STATUS   (uint16_t)0x0102

//10 + 1 = 11
typedef struct {
  //Header
  uint8_t Sender;
  uint8_t Receiver;
  uint16_t Command;
  uint16_t Size;
  uint32_t Count;

  //Body
  uint8_t MineDet_Num;
} RequsetPacket_t;

//10 + 5 = 15
typedef struct {
  //Header
  uint8_t Sender;
  uint8_t Receiver;
  uint16_t Command;
  uint16_t Size;
  uint32_t Count;

  //Body
  uint32_t SeqNo;
  uint8_t Result;

} ReplyPacket_t;

//10 + 23 = 33
typedef struct {
  //Header
  uint8_t Sender;
  uint8_t Receiver;
  uint16_t Command;
  uint16_t Size;
  uint32_t Count;

  //Body
  float Temp1;		//Temp1 value
  float Temp2;		//Temp2 value
  uint8_t FAN1;		//Fan Ass'y1
  uint8_t FAN2;		//Fan Ass'y2
  uint8_t PSU;		//
  uint8_t DP;
  uint8_t Charger;
  uint16_t Bat_SOC;
  uint16_t Bat_Volt;
  uint16_t Bat_AvgCurrent;
  uint16_t Bat_CycleCnt;
  uint16_t Bat_IntTemp;
} StatusPacket_t;

//---------------------------------------------
typedef struct {

  //개별 항목
  float Temp1;			//Temp1 value
  float Temp2;			//Temp2 value
  uint8_t FAN1;			//Fan Ass'y1 bit-wise
  uint8_t FAN2;			//Fan Ass'y2 bit-wise
  uint8_t PSU1;			//PSU1
  uint8_t PSU2;			//PSU2

  //개별항목, LED항목
  uint8_t DP1;			//DP1 (LED항목 겸용)
  uint8_t DP2;			//DP2 (LED항목 겸용)

  //LED 항목
  uint8_t LED_PSU;		//PSU1 + PSU2
  uint8_t LED_Temp;		//Temp1+ Temp2
  uint8_t LED_FAN1;		//fan1 + fan2 + fan3
  uint8_t LED_FAN2;		//fan4 + fan5 + fan6

} ConsoleStatusPacket_t;

typedef struct {

   //개별 항목
  float Temp1;			//Temp1 value
  float Temp2;			//Temp2 value
  uint8_t FANAssy1;		//Fan Ass'y1 bit-wise
  uint8_t FANAssy2;		//Fan Ass'y2 bit-wise
  uint8_t PSU1;			//PSU1
  uint8_t PSU2;			//PSU2

  //개별항목, LED항목
  uint8_t DP1;			//DP1 (LED항목 겸용)
  uint8_t DP2;			//DP2 (LED항목 겸용)
  uint8_t DP3;			//DP3 (LED항목 겸용)

  //LED 항목
  uint8_t LED_PSU;		//PSU1 + PSU2 + PSU3
  uint8_t LED_Temp;		//Temp1+ Temp2
  uint8_t LED_FAN1;		//fan1
  uint8_t LED_FAN2;		//fan2

 //개별항목, LED항목
  uint8_t Charger;		//Charger
  uint16_t Bat_SOC;		//Bat SOC / 3-digit FND Display

  //개별항목(Non-Display)
  uint16_t Bat_Volt;
  uint16_t Bat_Current;
  uint16_t Bat_CycleCnt;
  uint16_t Bat_Temp;

} PortableStatusPacket_t;

//---------------------------------------------

extern RequsetPacket_t request;
extern ReplyPacket_t reply;
extern StatusPacket_t status;

extern uint32_t StatusCount;

void UDP_Protocol_Init(void);
void UDP_Make_PortableStatusPacket(void);
void UDP_Make_ReplyPacket(RequsetPacket_t *reqPacket);
void print_status_packet(const StatusPacket_t *status);


#endif /* UDP_PROTOCOL_H_ */

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
  float Temp1;
  float Temp2;
  uint8_t FAN1;
  uint8_t FAN2;
  uint8_t PSU;
  uint8_t DP;

 } StatusPacket_t;

extern RequsetPacket_t request;
extern ReplyPacket_t reply;
extern StatusPacket_t status;

extern uint32_t StatusCount;

void UDP_Protocol_Init(void);
void UDP_Make_StatusPacket(void);
void UDP_Make_ReplyPacket(RequsetPacket_t *reqPacket);
void print_status_packet(const StatusPacket_t *status);

#endif /* UDP_PROTOCOL_H_ */

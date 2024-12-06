/*
 * udp_protocol.c
 *
 *  Created on: Aug 6, 2024
 *      Author: machi
 */

#include <stdio.h>
#include "udp_protocol.h"
#include "collect.h"
#include "bq34z100.h"

#define HEAD_SIZE 10

RequsetPacket_t request = {0};;
ReplyPacket_t reply = {0};;
StatusPacket_t status = {0};

uint32_t StatusCount = 0;
uint32_t ReplyCount = 0;

void UDP_RequestPacket_Init(void)
{
  //Header
  request.Sender = 0;
  request.Receiver = 0;
  request.Command = ID_REQUEST;
  request.Size  = 0;
  request.Count = 0;

  //Body
  request.MineDet_Num = 0;
}


void UDP_ReplyPacket_Init(void)
{
  //Header
  reply.Sender   = 0;;
  reply.Receiver = 0;
  reply.Command  = 0;
  reply.Size     = 0;
  reply.Count    = 0;

  //Body
  reply.SeqNo = 0;
  reply.Result = 0;
};


void UDP_StatusPacket_Init(void)
{
  //Header
  status.Sender   = 0;
  status.Receiver = 0;
  status.Command  = 0;
  status.Size     = 0;
  status.Count    = 0;

  //Header;
  status.Temp1 = 0.0;
  status.Temp2 = 0.0;
  status.FAN1  = 0;
  status.FAN2  = 0;
  status.PSU   = 0;
  status.DP    = 0;
  status.Charger  = 0;
  status.Bat_SOC  = 0;
  status.Bat_Volt = 0;
  status.Bat_AvgCurrent = 0;
  status.Bat_CycleCnt   = 0;
  status.Bat_IntTemp    = 0;
}


void UDP_Protocol_Init(void)
{
//  UDP_ReplyPacket_Init();
//  UDP_RequestPacket_Init();
//  UDP_StatusPacket_Init();
	StatusCount = 0;
	ReplyCount = 0;
}

//Fan3, Fan2, Fan1
static uint8_t UDP_GetFanStatus1(void)
{
  uint8_t Fan_Status = 0;

  Fan_Status  =  FAN_Sense1 & 0x01;
  Fan_Status |= (FAN_Sense2 & 0x01) << 1;

  return Fan_Status;
}

////Fan3, Fan2, Fan1
//static uint8_t UDP_GetFanStatus1(void)
//{
//  uint8_t Fan_Status1 = 0;
//
//  Fan_Status1  =  FAN_Sense1 & 0x01;
//  Fan_Status1 |= (FAN_Sense2 & 0x01) << 1;
//  Fan_Status1 |= (FAN_Sense3 & 0x01) << 2;
//
//  return Fan_Status1;
//}
//
////Fan6, Fan5, Fan4
//static uint8_t UDP_GetFanStatus2(void)
//{
//  uint8_t Fan_Status2 = 0;
//
//  Fan_Status2  =  FAN_Sense4 & 0x01;
//  Fan_Status2 |= (FAN_Sense5 & 0x01) << 1;
//  Fan_Status2 |= (FAN_Sense6 & 0x01) << 2;
//
//  return Fan_Status2;
//}

//static uint8_t UDP_GetPSUStatus(void)
//{
//  uint8_t PSUStatus;
//
//  PSUStatus  =  PSU_Status1 & 0x01;
//  PSUStatus |= (PSU_Status2 & 0x01) << 1;
//
//  return PSUStatus;
//}

static uint8_t UDP_GetDPStatus(void)
{
  uint8_t DPStatus;

  DPStatus  =  DP_Status1 & 0x01;
  DPStatus |= (DP_Status2 & 0x01) << 1;
  DPStatus |= (DP_Status3 & 0x01) << 2;

  return DPStatus;
}

void UDP_Make_StatusPacket(void)
{
  //Header
  status.Sender   = 0x01;
  status.Receiver = 0x02;
  status.Command  = ID_STATUS;
  status.Size     = sizeof(StatusPacket_t) - HEAD_SIZE;
  status.Count    = StatusCount;

  //Body
  status.Temp1 = Temp_Val1;
  status.Temp2 = Temp_Val2;
  status.FAN1  = UDP_GetFanStatus1();
  //status.FAN2  = UDP_GetFanStatus2();
  status.PSU   = 0;	//UDP_GetPSUStatus();	//Console과 포맷을 맞추기 위해 그대로 둠
  status.DP    = UDP_GetDPStatus();
  status.Charger        = Charger;
  status.Bat_SOC        = Bat.SOC_Val;
  status.Bat_Volt       = Bat.Voltage;
  status.Bat_AvgCurrent = Bat.AvgCurrent;
  status.Bat_CycleCnt   = Bat.CycleCount;
  status.Bat_IntTemp    = BatData16[4];

}

void UDP_Make_ReplyPacket(RequsetPacket_t *reqPacket)
{
  //Header
  reply.Sender   = 0x01;
  reply.Receiver = 0x02;
  reply.Command  = ID_REPLY;
  reply.Size     = sizeof(ReplyPacket_t) - HEAD_SIZE;
  reply.Count    = ReplyCount;

  //Body
  reply.SeqNo    = reqPacket->Count;
  reply.Result   = BUZ_Status;
}


void printBinary8Bit(int num, uint8_t count) {
    for (int i = 7; i >= 0; i--) {
        if (i < count) {
            printf("%d", (num >> i) & 1);
        }
    }
    printf("\n");
}

void print_status_packet(const StatusPacket_t *status)
{
//	float fBat_IntTemp;
//    printf("==[ Received STATUS Packet ]==\n");
//    printf("Sender: %d\n", status->Sender);
//    printf("Receiver: %d\n", status->Receiver);
//    printf("Command: 0x%X\n", status->Command);
//    printf("Size: %d\n", status->Size);
    printf("Count: %lu\n", status->Count);

//    printf("Temp1: %.2f C\n", status->Temp1);
//    printf("Temp2: %.2f C\n", status->Temp2);
//    printf("FAN1(3,2,1): %d = ", status->FAN1);
//    printBinary8Bit(status->FAN1, 3);
//    printf("FAN2(6,5,4): %d = ", status->FAN2);
//    printBinary8Bit(status->FAN2, 3);
//    printf("PSU(2,1): %d = ", status->PSU);
//    printBinary8Bit(status->PSU, 2);
//    printf("DP(3,2,1): %d = ", status->DP);
//    printBinary8Bit(status->DP, 3);
//    printf("Charger: %d\n", status->Charger);
//    printf("Bat_SOC: %d %%\n", status->Bat_SOC);
//    printf("Bat_Volt: %d mV\n", status->Bat_Volt);
//    printf("Bat_AvgCurrent: %d mA\n", status->Bat_AvgCurrent);
//    printf("Bat_CycleCnt: %d count\n", status->Bat_CycleCnt);
//    fBat_IntTemp = (float)((float)status->Bat_IntTemp / 10.0f - (float)273.15f);
//    printf("Bat_IntTemp: %.1f C\n", fBat_IntTemp);
//    printf("\n");
}


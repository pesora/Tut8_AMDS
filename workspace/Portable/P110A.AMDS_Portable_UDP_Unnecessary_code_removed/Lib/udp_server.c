/*
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************

  File:		  udpServerRAW.c
  Author:     ControllersTech.com
  Updated:    Jul 23, 2021

  ***************************************************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ***************************************************************************************************************
*/


#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"

#include <stdio.h>
#include <string.h>
#include <udp_server.h>
#include "lwip.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_eth.h"
#include "lwipopts.h"
#include "lwip/igmp.h"
#include "lwip/ip_addr.h"


// 전역 변수로 udp_pcb 선언
struct udp_pcb *upcb;
static uint8_t mine_det_num;

void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
void udp_send_to_client(struct udp_pcb *upcbx, const ip_addr_t *addr, u16_t port, const char *data);
void print_request_packet(const char *remoteIP, const RequsetPacket_t *request);
void print_reply_packet(const char *remoteIP, const ReplyPacket_t *reply);

/* IMPLEMENTATION FOR UDP Server :   source:https://www.geeksforgeeks.org/udp-server-client-implementation-c/

1. Create UDP socket.
2. Bind the socket to server address.
3. Wait until datagram status arrives from client.
4. Process the datagram status and send a reply to client.
5. Go back to Step 3.
*/
void configure_mac_filter(void) {
    ETH_MACFilterConfigTypeDef MACFilterConfig;

    // 현재 MAC 필터 설정을 가져옵니다.
    HAL_ETH_GetMACFilterConfig(&heth, &MACFilterConfig);

    // 멀티캐스트 프레임 필터 설정
    MACFilterConfig.PassAllMulticast = ENABLE;

    // MAC 필터 설정을 적용합니다.
    HAL_ETH_SetMACFilterConfig(&heth, &MACFilterConfig);
}

void udpServer_init(void)
{
	// UDP Control Block structure
   //struct udp_pcb *upcb;
   err_t err;

   /* 1. Create a new UDP control block  */
   upcb = udp_new();

   /* 2. Bind the upcb to the local port */
   ip_addr_t myIPADDR;
   IP_ADDR4(&myIPADDR, 192, 168, 50, 100);

   err = udp_bind(upcb, &myIPADDR, 9000);  // 7 is the server UDP port


   /* 3. Set a receive callback for the upcb */
   if(err == ERR_OK)
   {
	   udp_recv(upcb, udp_receive_callback, NULL);
   }
   else
   {
	   udp_remove(upcb);
   }
}

// udp_receive_callback will be called, when the client sends some data to the server
/* 4. Process the datagram status and send a reply to client. */
//void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
void udp_receive_callback(void *arg, struct udp_pcb *upcbx, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
    char *remoteIP = ipaddr_ntoa(addr);
    uint16_t port_no = 9000;
    RequsetPacket_t *requestPacket = (RequsetPacket_t *)p->payload;

    //Set MineDet_Num
    mine_det_num = requestPacket->MineDet_Num;

    // print requestPacket
    print_request_packet(remoteIP, requestPacket);

    // create ReplyPacket for client
    uint8_t buffer[sizeof(ReplyPacket_t)];
    UDP_Make_ReplyPacket(requestPacket);
    memcpy(buffer, &reply, sizeof(ReplyPacket_t));
    print_reply_packet(remoteIP, (ReplyPacket_t *)&buffer);

    // reply to the received remote client
     udp_send_to_client(upcb, addr, port_no, (char *)buffer);

    pbuf_free(p);
}

uint8_t UDP_Get_MineDetNum(void)
{
  return mine_det_num;
}

void print_request_packet(const char *remoteIP, const RequsetPacket_t *request)
{
    printf("[ REQUEST ] from %s\n", remoteIP);
    printf(" - Sender  : 0x%02X\n", request->Sender);
    printf(" - Receiver: 0x%02X\n", request->Receiver);
    printf(" - Command : 0x%04X\n", request->Command);
    printf(" - Size    : %d\n", request->Size);
    printf(" - Count   : %lu\n", request->Count);

    printf(" - MineDet : %d\n", request->MineDet_Num);
    printf("\n");
}

void print_reply_packet(const char *remoteIP, const ReplyPacket_t *reply)
{
    printf("[ REPLY ] from %s\n", remoteIP);
    printf(" - Sender  : 0x%02X\n", reply->Sender);
    printf(" - Receiver: 0x%02X\n", reply->Receiver);
    printf(" - Command : 0x%04X\n", reply->Command);
    printf(" - Pkt Size: %d\n", reply->Size);
    printf(" - Count   : %lu\n", reply->Count);

    printf(" - SeqNo : %lu\n", reply->SeqNo);
    printf(" - Result : %d\n", reply->Result);
    printf("\n");
}


void udp_send_to_client(struct udp_pcb *upcbx, const ip_addr_t *addr, u16_t port, const char *data)
{
    struct pbuf *txBuf;
    int len = sizeof(ReplyPacket_t);

    txBuf = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);
    if (txBuf == NULL) {
        printf("Error: pbuf allocation failed\n");
        return;
    }

    pbuf_take(txBuf, data, len);

    err_t err = udp_connect(upcb, addr, port);
    if (err != ERR_OK) {
        printf("Error: udp_connect failed with code %d\n", err);
        pbuf_free(txBuf);
        return;
    }

    err = udp_send(upcb, txBuf);
    if (err != ERR_OK) {
        printf("Error: udp_send failed with code %d\n", err);
    } else {
        printf("Message sent to %s:%d\n", ipaddr_ntoa(addr), port);
    }

    udp_disconnect(upcb);
    pbuf_free(txBuf);
}


void join_multicast_group(void) {
    ip4_addr_t local_ip;
    ip4_addr_t multicast_ip;

    IP4_ADDR(&local_ip, 192, 168, 50, 100); // 로컬 IP 주소
    IP4_ADDR(&multicast_ip, 224, 0, 1, 129); // 멀티캐스트 IP 주소

    igmp_joingroup(&local_ip, &multicast_ip);
}

void udp_send_multicast_msg(const char *msg)
{
    struct udp_pcb *pcb;
    struct pbuf *p;
    err_t err;

    //char msg[] = "Multicasting Message from UDP Server\n";

    pcb = udp_new();
    if (pcb == NULL) {
        return;
    }

    err = udp_bind(pcb, IP_ADDR_ANY, 9000);
    if (err != ERR_OK) {
        // Handle error
    }

    p = pbuf_alloc(PBUF_TRANSPORT, strlen(msg)+1, PBUF_RAM);
    if (p != NULL) {
        memcpy(p->payload, msg, strlen(msg)+1);

        ip_addr_t multicast_ip;
        IP_ADDR4(&multicast_ip, 224, 0, 1, 129); // Multicast IP address

#if LWIP_IGMP
        igmp_joingroup(IP_ADDR_ANY, &multicast_ip);
#endif

        err = udp_sendto(pcb, p, &multicast_ip, 9000);
        if (err != ERR_OK) {
            // Handle error
        }

        pbuf_free(p);
    }

    udp_remove(pcb);
}


void udp_send_multicast(const StatusPacket_t *status)
{
    struct udp_pcb *pcb;
    struct pbuf *p;
    err_t err;

    pcb = udp_new();
    if (pcb == NULL) {
      printf("error: usp creation fail !!\n");
      return;
    }

    // 변경된 포트 번호 사용
    err = udp_bind(pcb, IP_ADDR_ANY, 9001); // 포트를 9001로 변경
    if (err != ERR_OK) {
        // Handle error
        printf("error: binding fail !!\n");
        return;
    }

    p = pbuf_alloc(PBUF_TRANSPORT, sizeof(StatusPacket_t), PBUF_RAM);
    if (p != NULL) {
        memcpy(p->payload, status, sizeof(StatusPacket_t));

        ip_addr_t multicast_ip;
        IP_ADDR4(&multicast_ip, 224, 0, 1, 129); // Multicast IP address

#if LWIP_IGMP
        igmp_joingroup(IP_ADDR_ANY, &multicast_ip);
#endif

        err = udp_sendto(pcb, p, &multicast_ip, 9000);
        if (err != ERR_OK) {
            // Handle error
            printf("error: pbuf memory allocation fail !!\n");
        }

        pbuf_free(p);
    }

    udp_remove(pcb);
}


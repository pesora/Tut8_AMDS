/*
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************

  File:		  udpServerRAW.h
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


#ifndef INC_UDPSERVERRAW_H_
#define INC_UDPSERVERRAW_H_

#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "udp_protocol.h"

extern struct udp_pcb *upcb;


void udpServer_init(void);
void udp_send_to_client(struct udp_pcb *upcb, const ip_addr_t *addr, u16_t port, const char *data);
void udp_send_multicast(const StatusPacket_t *status);
void udp_send_multicast_msg(const char *msg);
void configure_mac_filter(void);
uint8_t UDP_Get_MineDetNum(void);

#endif /* INC_UDPSERVERRAW_H_ */

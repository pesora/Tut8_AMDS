/*
 * send.c
 *
 *  Created on: Aug 6, 2024
 *      Author: machi
 */


#include "send.h"
#include "udp_protocol.h"
#include "udp_server.h"

void Send_Portable_Status(void)
{
	StatusCount++;
	UDP_Make_StatusPacket();
	udp_send_multicast(&status);
	print_status_packet(&status);
}

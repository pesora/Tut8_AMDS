/*
 * process.c
 *
 *  Created on: Jun 12, 2024
 *      Author: machi
 */

#include <stdio.h>
#include <udp_server.h>
#include "main.h"
#include "process.h"
#include "hih8131.h"
#include "bq34z100.h"
#include "fan_control.h"
#include "display.h"
#include "user_timer.h"
#include "collect.h"
#include "send.h"

#include "lwip/udp.h"
#include "ethernetif.h"
#include "timeouts.h"
#include "udp_protocol.h"

//UDP Server
extern struct netif gnetif;
extern ip4_addr_t ipaddr;

extern Portable_Status_t Portable_Status;

static uint32_t collect_stamp_100ms = 0;
static uint32_t collect_stamp_500ms = 0;
static uint32_t collect_stamp_1sec = 0;
static uint32_t display_stamp_1sec = 0;
static uint32_t send_stamp_1sec = 0;

static void Collect_Portable_Status(void);
static void Display_Portable_LED(void);

void Process_Init(void)
{
  collect_stamp_100ms = 0;
  collect_stamp_500ms = 0;
  collect_stamp_1sec = 0;
  display_stamp_1sec = 0;
  send_stamp_1sec = 0;
}

void Process_Portable_Status(void)
{
  //Ethernet UDP Server
  ethernetif_input(&gnetif);
  sys_check_timeouts();

  Read_FAN_Status();

  if (fan_done == 1 && (mills() - collect_stamp_1sec >= 1000))
  {
    Collect_Portable_Status();
    Display_Portable_LED();
    Send_Portable_Status();

    fan_done = 0;
    collect_stamp_1sec = mills();
  }

  Control_Fan(&Console_Status);
}


static void Collect_Portable_Status(void)
{
  Read_Temp_Value();
//  Read_PSU_Status();
  Read_DP_Status();
  Read_MineDet_Number();
  Read_Charger_Status();
  Read_BAT_Status();
  Read_BUZ_Status();

  Store_Portable_Status();
  UDP_Make_PortableStatusPacket();


  //----------------------------------------------------
  HAL_GPIO_TogglePin(LD3_RED_GPIO_Port, LD3_RED_Pin);

}


static void Display_Portable_LED(void)
{
  Display_Temp_LED();
  Display_FAN_LED();
//  Display_FAN1_LED();
//  Display_FAN2_LED();
//  Display_PSU_LED();
  Display_DP_LED();
  Display_Charger_LED();
  Alarm_MineDet_BUZ();
  Display_SOC_7SEG();

  Print_Portable_Status();

   //----------------------------------------------------

  HAL_GPIO_TogglePin(LD2_BLU_GPIO_Port, LD2_BLU_Pin);
}



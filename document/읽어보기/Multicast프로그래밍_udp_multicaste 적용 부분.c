1. Middlewares\Third_Party\LwIP\src\include\lwip ( LWIP\Target\lwipopts.h ) 파일을 열어 다음을 추가, 
  
  #define   LWIP_IGMP 1

2. LWIP\Target\ethernetif.c 파일을 열어 low_level_init() 함수에 다음을 추가

/* USER CODE BEGIN LOW_LEVEL_INIT */
 netif->flags |= NETIF_FLAG_IGMP;
/* USER CODE END LOW_LEVEL_INIT */

3. udpServerRAW.c
  1) 다음 헤더파일을 추가
	#include <stdio.h>
	#include <string.h>
	#include "lwip.h"
	#include "stm32f4xx_hal.h"
	#include "stm32f4xx_hal_eth.h"
	#include "lwipopts.h"
	#include "lwip/igmp.h"
	
  2)다음을 변경
	// 전역 변수로 udp_pcb 선언
	struct udp_pcb *upcb;
  
  3) multicast 루틴을 추가한다
  
4. main.c

 1) configure_mac_filter();
 2) send multicast message
   while (1)
  {
    ethernetif_input(&gnetif);
    sys_check_timeouts();

    if(key_pressed == 1)
    {
      // send multicast message
      udp_server_multicasting();

      key_pressed = 0;
    }


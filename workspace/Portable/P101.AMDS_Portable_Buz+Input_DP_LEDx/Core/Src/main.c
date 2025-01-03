/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "lwip.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <udp_server.h>
#include "ring_buffer.h"
#include "pid.h"
#include "ema.h"
#include "user_timer.h"
#include "fan_control.h"
#include "debug_uart.h"
#include "hih8131.h"
#include "bq34z100.h"
#include "process.h"
#include "max7219.h"
#include "display.h"
#include "udp_protocol.h"
#include "send.h"
#include "debug_uart.h"
#include "buzzer.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t timer_interrupt_100ms_done = 0;
uint8_t timer_interrupt_1sec_done = 0;
uint8_t key_pressed = 0;
uint8_t keyno = 0;

//----------------------
//RingBuffer rxBuffer;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
int _write(int file, char* p, int len)
{
	HAL_UART_Transmit(&huart3, (const uint8_t *)p, len, 10);
	return len;
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t stamp_100ms = 0;
uint32_t stamp_1sec = 0;
int8_t cmd_received = 1;
//uint8_t command[50] = {0, };


//UDP Server
extern struct netif gnetif;
extern ip4_addr_t ipaddr;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_LWIP_Init();
  MX_TIM6_Init();
  MX_I2C3_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
  uTimer_Init();
  LED_Init();
  MAX7219_Init();
  Buzzer_Init();

  DBG_Uart_Init();
  HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxBuffer.buffer[rxBuffer.head], 1);

  FAN_Init();
  HMTP_Init();
  UDP_Protocol_Init();

  configure_mac_filter();
  udpServer_init();
  Process_Init();

  HAL_TIM_Base_Start_IT(&htim6);

 printf("\nP101.AMDS_Portable_Buz+Input_DP_LEDx\n");

 //Send_Portable_Status()
 setbuf(stdout,NULL);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


 uint8_t toggle = 0;
  while (1)
  {
//	  Buzzer_On();
//	  HAL_Delay(1000);
//	  Buzzer_Off();
//	  HAL_Delay(1000);

    ethernetif_input(&gnetif);
    sys_check_timeouts();

    Process_Portable_Status();

    if(key_pressed == 1)
    {
      toggle = !toggle;

        if(toggle==1) {
        	status.Charger  = 1;
        	Buzzer_On();
        }
        else {
        	status.Charger  = 0;
        	Buzzer_Off();
        }

        //Send_Portable_Status();

        key_pressed = 0;
     }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint32_t last_blink_tick = 0;

  if(htim->Instance == TIM6)
  {
    if (HAL_GetTick() - last_blink_tick >= 500) {
      last_blink_tick = HAL_GetTick();

      HAL_GPIO_TogglePin(RUN_LED_GPIO_Port, RUN_LED_Pin);
      //HAL_GPIO_TogglePin(LED_DP2_G_GPIO_Port, LED_DP2_G_Pin);
    }
  }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == USER_BTN_Pin)
  {
    HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    //---------------------------------------------------------
    if(key_pressed == 0)
    {
      printf("key_pressed !\n");
      key_pressed = 1;
    }

    //---------------------------------------------------------
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  }//USER_BTN_Pin

  if(GPIO_Pin == TEST_BTN_Pin)
  {
    HAL_NVIC_DisableIRQ(EXTI0_IRQn);
    //---------------------------------------------------------
    if(key_pressed == 0)
    {
      uTimer_Regist(((uint8_t)uTimerDebounce), KEY_TIMERCNT);
      keyno = fan_step;

      if(keyno <5 ) {
        keyno++;
      }
      if (keyno > 4) {
        keyno = 0;
      }
      fan_step = keyno;

      key_pressed = 1;

      printf("STEP : %d \n", keyno);
    }
    //---------------------------------------------------------
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  }//TEST_BTN_Pin
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

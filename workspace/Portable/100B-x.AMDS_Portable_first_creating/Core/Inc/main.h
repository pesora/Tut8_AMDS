/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FAN_MUX_S2_Pin GPIO_PIN_2
#define FAN_MUX_S2_GPIO_Port GPIOE
#define FAN_MUX_S3_Pin GPIO_PIN_3
#define FAN_MUX_S3_GPIO_Port GPIOE
#define USER_BTN_Pin GPIO_PIN_13
#define USER_BTN_GPIO_Port GPIOC
#define USER_BTN_EXTI_IRQn EXTI15_10_IRQn
#define LED_TEMP_R_Pin GPIO_PIN_0
#define LED_TEMP_R_GPIO_Port GPIOF
#define LED_TEMP_G_Pin GPIO_PIN_1
#define LED_TEMP_G_GPIO_Port GPIOF
#define LED_FAN1_R_Pin GPIO_PIN_2
#define LED_FAN1_R_GPIO_Port GPIOF
#define LED_FAN1_G_Pin GPIO_PIN_3
#define LED_FAN1_G_GPIO_Port GPIOF
#define LED_FAN2_R_Pin GPIO_PIN_4
#define LED_FAN2_R_GPIO_Port GPIOF
#define LED_FAN2_G_Pin GPIO_PIN_5
#define LED_FAN2_G_GPIO_Port GPIOF
#define LED_PSU_R_Pin GPIO_PIN_6
#define LED_PSU_R_GPIO_Port GPIOF
#define LED_PSU_G_Pin GPIO_PIN_7
#define LED_PSU_G_GPIO_Port GPIOF
#define LED_DP1_G_Pin GPIO_PIN_8
#define LED_DP1_G_GPIO_Port GPIOF
#define LED_DP2_G_Pin GPIO_PIN_9
#define LED_DP2_G_GPIO_Port GPIOF
#define LED_DP3_G_Pin GPIO_PIN_10
#define LED_DP3_G_GPIO_Port GPIOF
#define TEST_BTN_Pin GPIO_PIN_0
#define TEST_BTN_GPIO_Port GPIOC
#define TEST_BTN_EXTI_IRQn EXTI0_IRQn
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define TIM2_CH1_IC1_Pin GPIO_PIN_0
#define TIM2_CH1_IC1_GPIO_Port GPIOA
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define TIM5_CH4_BUZ_Pin GPIO_PIN_3
#define TIM5_CH4_BUZ_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define LD1_GRN_Pin GPIO_PIN_0
#define LD1_GRN_GPIO_Port GPIOB
#define PB2_BOOT1_Pin GPIO_PIN_2
#define PB2_BOOT1_GPIO_Port GPIOB
#define LED_CHG_R_Pin GPIO_PIN_11
#define LED_CHG_R_GPIO_Port GPIOF
#define LED_CHG_G_Pin GPIO_PIN_12
#define LED_CHG_G_GPIO_Port GPIOF
#define BUZ_Pin GPIO_PIN_13
#define BUZ_GPIO_Port GPIOF
#define RUN_LED_Pin GPIO_PIN_15
#define RUN_LED_GPIO_Port GPIOF
#define TIM1_CH1_PWM1_Pin GPIO_PIN_9
#define TIM1_CH1_PWM1_GPIO_Port GPIOE
#define TIM1_CH2_PWM2_Pin GPIO_PIN_11
#define TIM1_CH2_PWM2_GPIO_Port GPIOE
#define TIM1_CH3_PWM3_Pin GPIO_PIN_13
#define TIM1_CH3_PWM3_GPIO_Port GPIOE
#define TIM2_CH3_IC2_Pin GPIO_PIN_10
#define TIM2_CH3_IC2_GPIO_Port GPIOB
#define TIM2_CH4_IC3_Pin GPIO_PIN_11
#define TIM2_CH4_IC3_GPIO_Port GPIOB
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define LD3_RED_Pin GPIO_PIN_14
#define LD3_RED_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define TIM4_CH1_IC4_Pin GPIO_PIN_12
#define TIM4_CH1_IC4_GPIO_Port GPIOD
#define TIM4_CH2_IC5_Pin GPIO_PIN_13
#define TIM4_CH2_IC5_GPIO_Port GPIOD
#define TIM4_CH3_IC6_Pin GPIO_PIN_14
#define TIM4_CH3_IC6_GPIO_Port GPIOD
#define INPUT_DP_LED1_Pin GPIO_PIN_4
#define INPUT_DP_LED1_GPIO_Port GPIOG
#define INPUT_DP_LED2_Pin GPIO_PIN_5
#define INPUT_DP_LED2_GPIO_Port GPIOG
#define INPUT_DP_LED3_Pin GPIO_PIN_6
#define INPUT_DP_LED3_GPIO_Port GPIOG
#define TIM3_CH1_PWM4_Pin GPIO_PIN_6
#define TIM3_CH1_PWM4_GPIO_Port GPIOC
#define TIM3_CH2_PWM5_Pin GPIO_PIN_7
#define TIM3_CH2_PWM5_GPIO_Port GPIOC
#define TIM3_CH3_PWM6_Pin GPIO_PIN_8
#define TIM3_CH3_PWM6_GPIO_Port GPIOC
#define BAT_I2C3_SDA_Pin GPIO_PIN_9
#define BAT_I2C3_SDA_GPIO_Port GPIOC
#define BAT_I2C3_SCL_Pin GPIO_PIN_8
#define BAT_I2C3_SCL_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SEG_LOAD_Pin GPIO_PIN_15
#define SEG_LOAD_GPIO_Port GPIOA
#define SEG_SPI3_SCK_Pin GPIO_PIN_10
#define SEG_SPI3_SCK_GPIO_Port GPIOC
#define SEG_SPI3_MISO_Pin GPIO_PIN_11
#define SEG_SPI3_MISO_GPIO_Port GPIOC
#define SEG_SPI3_MOSI_Pin GPIO_PIN_12
#define SEG_SPI3_MOSI_GPIO_Port GPIOC
#define INPUT_PSU1_Pin GPIO_PIN_0
#define INPUT_PSU1_GPIO_Port GPIOD
#define INPUT_PSU2_Pin GPIO_PIN_1
#define INPUT_PSU2_GPIO_Port GPIOD
#define INPUT_DP1_Pin GPIO_PIN_2
#define INPUT_DP1_GPIO_Port GPIOD
#define INPUT_DP2_Pin GPIO_PIN_3
#define INPUT_DP2_GPIO_Port GPIOD
#define INPUT_DP3_Pin GPIO_PIN_4
#define INPUT_DP3_GPIO_Port GPIOD
#define INPUT_CHG_Pin GPIO_PIN_5
#define INPUT_CHG_GPIO_Port GPIOD
#define INPUT_CHG_ERR_Pin GPIO_PIN_6
#define INPUT_CHG_ERR_GPIO_Port GPIOD
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define SEG_SPI1_MISO_Pin GPIO_PIN_4
#define SEG_SPI1_MISO_GPIO_Port GPIOB
#define TEMP_I2C1_nRESET_Pin GPIO_PIN_6
#define TEMP_I2C1_nRESET_GPIO_Port GPIOB
#define LD2_BLU_Pin GPIO_PIN_7
#define LD2_BLU_GPIO_Port GPIOB
#define TEMP_I2C1_SCL_Pin GPIO_PIN_8
#define TEMP_I2C1_SCL_GPIO_Port GPIOB
#define TEMP_I2C1_SDA_Pin GPIO_PIN_9
#define TEMP_I2C1_SDA_GPIO_Port GPIOB
#define FAN_MUX_S0_Pin GPIO_PIN_0
#define FAN_MUX_S0_GPIO_Port GPIOE
#define FAN_MUX_S1_Pin GPIO_PIN_1
#define FAN_MUX_S1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

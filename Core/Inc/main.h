/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define VIOUT_2_Pin GPIO_PIN_0
#define VIOUT_2_GPIO_Port GPIOC
#define Batt_Pin GPIO_PIN_1
#define Batt_GPIO_Port GPIOC
#define LED_FR_Pin GPIO_PIN_2
#define LED_FR_GPIO_Port GPIOC
#define LED_R_Pin GPIO_PIN_3
#define LED_R_GPIO_Port GPIOC
#define Sensor_FR_Pin GPIO_PIN_0
#define Sensor_FR_GPIO_Port GPIOA
#define Sensor_R_Pin GPIO_PIN_1
#define Sensor_R_GPIO_Port GPIOA
#define Sensor_FL_Pin GPIO_PIN_2
#define Sensor_FL_GPIO_Port GPIOA
#define Sensor_L_Pin GPIO_PIN_3
#define Sensor_L_GPIO_Port GPIOA
#define SPI3_CS_Pin GPIO_PIN_4
#define SPI3_CS_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_5
#define Buzzer_GPIO_Port GPIOA
#define LED_L_Pin GPIO_PIN_6
#define LED_L_GPIO_Port GPIOA
#define LED_FL_Pin GPIO_PIN_7
#define LED_FL_GPIO_Port GPIOA
#define VIOUT_1_Pin GPIO_PIN_4
#define VIOUT_1_GPIO_Port GPIOC
#define ModeChange_Button_Pin GPIO_PIN_5
#define ModeChange_Button_GPIO_Port GPIOC
#define Mode_LED2_Pin GPIO_PIN_0
#define Mode_LED2_GPIO_Port GPIOB
#define Mode_LED3_Pin GPIO_PIN_1
#define Mode_LED3_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_14
#define AIN2_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_15
#define AIN1_GPIO_Port GPIOB
#define M2_ChB_Pin GPIO_PIN_6
#define M2_ChB_GPIO_Port GPIOC
#define M2_ChA_Pin GPIO_PIN_7
#define M2_ChA_GPIO_Port GPIOC
#define SensorLED_L_Pin GPIO_PIN_8
#define SensorLED_L_GPIO_Port GPIOC
#define PWMA_Pin GPIO_PIN_8
#define PWMA_GPIO_Port GPIOA
#define SensorLED_R_Pin GPIO_PIN_10
#define SensorLED_R_GPIO_Port GPIOA
#define SensorLED_FR_Pin GPIO_PIN_11
#define SensorLED_FR_GPIO_Port GPIOA
#define SensorLED_FL_Pin GPIO_PIN_12
#define SensorLED_FL_GPIO_Port GPIOA
#define Mode_LED1_Pin GPIO_PIN_15
#define Mode_LED1_GPIO_Port GPIOA
#define BIN2_Pin GPIO_PIN_4
#define BIN2_GPIO_Port GPIOB
#define BIN1_Pin GPIO_PIN_5
#define BIN1_GPIO_Port GPIOB
#define M1_ChB_Pin GPIO_PIN_6
#define M1_ChB_GPIO_Port GPIOB
#define M1_ChA_Pin GPIO_PIN_7
#define M1_ChA_GPIO_Port GPIOB
#define Suction_Motor_Pin GPIO_PIN_8
#define Suction_Motor_GPIO_Port GPIOB
#define PWMB_Pin GPIO_PIN_9
#define PWMB_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

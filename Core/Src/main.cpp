/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "gpio.hpp"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../HALinterface/Inc/AdcSTM32F4.hpp"
#include "../HALinterface/Inc/PwmSTM32F4.hpp"
#include "../HALinterface/Inc/TimerSTM32F4.hpp"
#include "../HALinterface/Inc/GpioSTM32F4.hpp"
#include "../HALinterface/Inc/EncoderSTM32F4.hpp"

#include "../Driver/Inc/Button.hpp"
#include "../Driver/Inc/MotorDriver.hpp"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_SPI3_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
  // HAL実装インスタンス
  // GPIO
  static GpioSTM32F4 AIN1(GPIOB, GPIO_PIN_15);
  static GpioSTM32F4 AIN2(GPIOB, GPIO_PIN_14);
  static GpioSTM32F4 BIN1(GPIOB, GPIO_PIN_5);
  static GpioSTM32F4 BIN2(GPIOB, GPIO_PIN_4);
  static GpioSTM32F4 SensorLED_FL(GPIOA, GPIO_PIN_12);
  static GpioSTM32F4 SensorLED_FR(GPIOA, GPIO_PIN_11);
  static GpioSTM32F4 SensorLED_R(GPIOA, GPIO_PIN_10);
  static GpioSTM32F4 SensorLED_L(GPIOC, GPIO_PIN_8);
  static GpioSTM32F4 LED_FL(GPIOA, GPIO_PIN_7);
  static GpioSTM32F4 LED_FR(GPIOC, GPIO_PIN_2);
  static GpioSTM32F4 LED_R(GPIOC, GPIO_PIN_3);
  static GpioSTM32F4 LED_L(GPIOA, GPIO_PIN_8);
  static GpioSTM32F4 ModeLED1(GPIOA, GPIO_PIN_15);
  static GpioSTM32F4 ModeLED2(GPIOB, GPIO_PIN_0);
  static GpioSTM32F4 ModeLED3(GPIOB, GPIO_PIN_1);
  static GpioSTM32F4 gpioButton(GPIOC, GPIO_PIN_5);

  // ADC
  static AdcSTM32F4 Adc1(&hadc1);
  static AdcSTM32F4 Adc2(&hadc2);
  static AdcSTM32F4 Adc3(&hadc3);

  // PWM
  static PwmSTM32F4 pwmRight(&htim1, TIM_CHANNEL_1);
  static PwmSTM32F4 pwmLeft(&htim11, TIM_CHANNEL_1);
  static PwmSTM32F4 SuctionMotor(&htim10, TIM_CHANNEL_1);
  static PwmSTM32F4 Buzzer(&htim2, TIM_CHANNEL_1);

  // TIMER
  static TimerSTM32F4 CalcDynamics(&htim5);
  static EncoderSTM32F4 EncoderRight(&htim3);
  static EncoderSTM32F4 EncoderLeft(&htim4);

  //ドライバクラス 
  static Button ModeChangeButton(&gpioButton, 1000);  // longPress=1000ms

  // 右モータ
  static MotorDriver RightMotor(
      &pwmRight,
      &AIN1,
      &AIN2,
      840.0f   // ARR値
  );

  // 左モータ
  static MotorDriver LeftMotor(
      &pwmLeft,
      &BIN1,
      &BIN2,
      840.0f   // ARR値
  );
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    uint8_t state = ModeChangeButton.checkState();

        if (state == 0) {
          ModeLED1.setHigh();
            // 短い押下
            // 例えば モードを1つ進めるとか
        }
        else if (state == 1) {
          ModeLED2.setHigh();
            // 長押し
            // 例えば "決定" や "抜ける" 動作
        }
        else {
          ModeLED3.setHigh();
            // Off
            // 押されていない状態
        }

        // 他の処理...
        HAL_Delay(50); // 適当なウェイト
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
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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

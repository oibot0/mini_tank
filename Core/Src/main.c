/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "wifi.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_it.h"
#include "stm32l0xx_hal_tim.h"
#include "sys.h"
#include "sht30.h"
#include "stdio.h"
//#include "SHT30.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define tuya

#ifdef USER_MAIN_DEBUG

#define log(format, ...) printf( format "\r\n",##__VA_ARGS__)

#else
#define log(format, ...)

#endif

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
    I2C_HandleTypeDef hi2c1;
    SHT30_T SHT3ODATA;
    UART_HandleTypeDef hlpuart1;
    TIM_HandleTypeDef htim2;
    TIM_HandleTypeDef htim21;

//uint16_t adcbuf[10]; //锟斤拷锟絘dc
//uint8_t hall_flag=1;    //锟斤拷锟斤拷锟酵碉拷平锟斤拷志
//uint8_t CONTROL=0x01;  //锟斤拷锟斤拷状态
//uint16_t time=0,time1,time2,now=0,min=0,max=600;
//uint32_t temp = 0;//锟斤拷锟节斤拷锟秸猴拷锟斤拷锟斤拷锟斤拷
//uint16_t rx_temp[1]; //锟斤拷锟节斤拷锟斤拷
//UART_HandleTypeDef hlpuart1;
#ifdef tuya
//uint8_t PERCENT_CONTROL=0,AUTO_POWER=1,BATTERY_PERCENTAGE;
//uint8_t PERCENT_STATE=0;
//uint16_t now_control=0xffff;
#endif
/* USER CODE END PTD */

/* USER CODE BEGIN PFP */

/*
int fputc(int ch, FILE *f)	  //fputc重写
{
	 uint8_t temp[1]={ch};
  HAL_UART_Transmit(&hlpuart1,temp,1,2);
	return ch;
}
*/

/* USER CODE END PFP */

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
void MX_GPIO_Init(void);
void MX_LPUART1_UART_Init(void);
static void MX_I2C1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM21_Init(void);

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
  MX_LPUART1_UART_Init();
  MX_I2C1_Init();

//  MX_TIM2_Init();
//  MX_TIM21_Init();
  /* USER CODE BEGIN 2 */

//  HAL_TIM_Base_Start_IT(&htim21);
//  HAL_TIM_Base_Stop(&htim21);


#ifdef tuya
	wifi_protocol_init();
//    HAL_UART_Receive_IT(&hlpuart1,(uint8_t *)rx_temp, 1);
#endif
  /* USER CODE END 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  while (1)
  {

#ifdef tuya
	    wifi_uart_service();  //SDK锟斤拷锟斤拷
	   // mcu_reset_wifi();
		if(HAL_GPIO_ReadPin(sw2_GPIO_Port, sw2_Pin)==0)                //检测按键按下2000ms进入配网模式
		{
			HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);

			if(HAL_GPIO_ReadPin(sw2_GPIO_Port, sw2_Pin)==0)
		  {
			HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
			HAL_Delay(100);
			mcu_set_wifi_mode(SMART_CONFIG);
			HAL_Delay(100);
		  }

			switch(mcu_get_wifi_work_state())                   //查询配网状态
						{
							case SMART_CONFIG_STATE: //Smart 配置状态 LED 快闪 �
							  while(mcu_get_wifi_work_state() == SMART_CONFIG_STATE )
								{
									HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
									HAL_Delay(500);
									HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
									HAL_Delay(500);
			          }
								break;
							case AP_STATE: //AP 配置状态 LED 慢闪
							  while(mcu_get_wifi_work_state() == AP_STATE )
								{
									HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
									HAL_Delay(2000);
									HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
									HAL_Delay(2000);
								}
								break;
							case WIFI_NOT_CONNECTED: //WIFI 配置完成，正在连接路由器
							{
								HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
								HAL_Delay(250);
								HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
								HAL_Delay(250);
							}
								break;
							case WIFI_CONN_CLOUD: //wifi 已连上云端 LED 慢闪硕后关闭
							{
								HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
							    HAL_Delay(4000);
								HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
								HAL_Delay(4000);
								HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_SET);
								HAL_Delay(4000);
								HAL_GPIO_WritePin(led_GPIO_Port, led_Pin, GPIO_PIN_RESET);
								HAL_Delay(4000);
							}
								break;
							default:break;
						}
		}

		 SHT30_ReadData();
		 mcu_dp_value_update(1,SHT3ODATA.temp); //VALUE型数据上报;
		 mcu_dp_value_update(2,SHT3ODATA.humidity); //VALUE型数据上报;

#endif

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPUART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_HSI;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00303D5B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}


/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
//static void MX_LPUART1_UART_Init(void)
void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 9600;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
//static void MX_GPIO_Init(void)
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


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


SHT30_T SHT30_ReadData()
{
 //   MX_I2C1_Init();

    uint8_t IIC_TXbuf[2] = {SHT30_Read_CMD, SHT30_Read_High};
    uint8_t IIC_RXbuf[6];

    HAL_StatusTypeDef status = HAL_OK;
    SHT30_T data;

    status = HAL_I2C_Master_Transmit(&hi2c1, SHT30_ADDR << 1, IIC_TXbuf, 2, 0xff);
    if (status != HAL_OK)
    {
        HAL_I2C_DeInit(&hi2c1);
        MX_I2C1_Init();
    }
    status = HAL_I2C_Master_Receive(&hi2c1, SHT30_ADDR << 1, IIC_RXbuf, 6, 0xff);
    if (status != HAL_OK)
    {
        HAL_I2C_DeInit(&hi2c1);
        MX_I2C1_Init();
    }
    data.state = status;
    data.temp = (float)(((IIC_RXbuf[0] << 8) + IIC_RXbuf[1]) * 175) / 65535 - 45;
    data.humidity = (float)(((IIC_RXbuf[3] << 8) + IIC_RXbuf[4]) * 100) / 65535;
    HAL_I2C_DeInit(&hi2c1);
    return data;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

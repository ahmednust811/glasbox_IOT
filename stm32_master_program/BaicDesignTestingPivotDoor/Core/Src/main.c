/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
 TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void initial_system_state(void);
void normal_state(uint8_t);
uint8_t manager_auth(void);
void direction(uint8_t); //O-to open;C- to close
void brake(uint8_t); //1- to brake;0- to release brake
void move_actuator(uint8_t); // L- to lock; U-to unlock;S-to stop
uint8_t actuator_state(void); // returns high when locked
uint8_t door_state(void); // returns high when closed
uint8_t select_system(void); //returns 1-normal operation;return 2-wind sensor master
uint8_t person_present(uint8_t); //input-F-to check front sensor;B-to check back sensor --> returns 1-person present;0-no person
uint8_t wind_sensor_state(void); //returns 1-wind speed high;returns 2-wind speed low
void emergency_close(void);
void remained_open(void);
uint8_t countstates(uint8_t[]);
void move_motor(uint8_t, uint8_t);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define TOTAL_PULSES 2015
/* USER CODE END 0 */

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  	initial_system_state();
  	/* USER CODE END 2 */

  	/* Infinite loop */
  	/* USER CODE BEGIN WHILE */
  	while (1) {
  		if (HAL_GPIO_ReadPin(GPIOD, remained_open_Pin)) {
  			remained_open();
  		}
  		/* USER CODE END WHILE */

  		/* USER CODE BEGIN 3 */
  		uint8_t select_switch = select_system(); // Selection between motion sensor and wind sensor

  		switch (select_switch) {
  		case 1:

  			normal_state(0);
  			break;

  		case 2:
  			if (wind_sensor_state()) {
  				if (!manager_auth()) {
  					emergency_close();
  					while (!manager_auth())
  						;
  				}
  			}
  			normal_state(1);

  			break;
  		}
  	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 63000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, BC_Pin|buzzer_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|act_clock_Pin|act_aclock_Pin|LS1_Pin
                          |LS2_Pin|FR_Pin|alignment_sensor_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, led3_Pin|led2_Pin|led1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : BC_Pin buzzer_Pin */
  GPIO_InitStruct.Pin = BC_Pin|buzzer_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 act_clock_Pin act_aclock_Pin LS1_Pin
                           LS2_Pin FR_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|act_clock_Pin|act_aclock_Pin|LS1_Pin
                          |LS2_Pin|FR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : motion_in_Pin button_motion_in_Pin button_motion_out_Pin motion_out_Pin */
  GPIO_InitStruct.Pin = motion_in_Pin|button_motion_in_Pin|button_motion_out_Pin|motion_out_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : actuator_sensor_Pin */
  GPIO_InitStruct.Pin = actuator_sensor_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(actuator_sensor_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : wind_Pin */
  GPIO_InitStruct.Pin = wind_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(wind_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : function_switch_Pin door_sensor_Pin */
  GPIO_InitStruct.Pin = function_switch_Pin|door_sensor_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : master_button_Pin */
  GPIO_InitStruct.Pin = master_button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(master_button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : led3_Pin led2_Pin led1_Pin */
  GPIO_InitStruct.Pin = led3_Pin|led2_Pin|led1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : alignment_sensor_Pin */
  GPIO_InitStruct.Pin = alignment_sensor_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(alignment_sensor_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

uint8_t person_present(uint8_t side) {

	HAL_Delay(20);
	if (side == 'F')
		return HAL_GPIO_ReadPin(GPIOB, motion_sensor_Pin);
	else if (side == 'B')
		return !HAL_GPIO_ReadPin(GPIOD, closing_motion_sensor_Pin);
}

void move_actuator(uint8_t state) {
	if (state == 'L') {
		HAL_GPIO_WritePin(GPIOC, linear_actuator1_Pin, GPIO_PIN_RESET);
		HAL_Delay(20);
		HAL_GPIO_WritePin(GPIOC, linear_actuator2_Pin, GPIO_PIN_SET);
		HAL_Delay(50);
	} else if (state == 'U') {
		HAL_GPIO_WritePin(GPIOC, linear_actuator2_Pin, GPIO_PIN_RESET);
		HAL_Delay(20);
		HAL_GPIO_WritePin(GPIOC, linear_actuator1_Pin, GPIO_PIN_SET);
		HAL_Delay(50);

	} else if (state == 'S') {
		HAL_GPIO_WritePin(GPIOC, linear_actuator2_Pin, GPIO_PIN_RESET);
		HAL_Delay(20);
		HAL_GPIO_WritePin(GPIOC, linear_actuator1_Pin, GPIO_PIN_RESET);
		HAL_Delay(50);
	}

}
uint8_t actuator_state(void) {

	HAL_Delay(20);
	return HAL_GPIO_ReadPin(GPIOB, proximity_sensor_Pin);

}
uint8_t door_state(void) {

	HAL_Delay(20);
	return HAL_GPIO_ReadPin(GPIOB, limit_switch_Pin);

}
void direction(uint8_t dir) {
	if (dir == 'C')
		HAL_GPIO_WritePin(FR_GPIO_Port, FR_Pin, GPIO_PIN_RESET);
	else if (dir == 'O')
		HAL_GPIO_WritePin(FR_GPIO_Port, FR_Pin, GPIO_PIN_SET);

}

void brake(uint8_t state) {

	if (state)
		HAL_GPIO_WritePin(BC_GPIO_Port, BC_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(BC_GPIO_Port, BC_Pin, GPIO_PIN_RESET);

}
uint8_t wind_sensor_state(void) {

	HAL_Delay(10);
	return HAL_GPIO_ReadPin(wind_GPIO_Port, wind_Pin);

}

void initial_system_state(void) {
	brake(1);  // Break while door opening
	HAL_Delay(50);

	direction('C');
	HAL_Delay(20);
	brake(0);
	HAL_Delay(20);

	while (!door_state()) {
		HAL_Delay(10);
	}
	brake(1);
	HAL_Delay(20);
	move_actuator('L');
	while (!actuator_state()) {
		HAL_Delay(10);
	}
	move_actuator('S');

}

uint8_t select_system(void) {
	HAL_Delay(10);
	uint8_t system_state = HAL_GPIO_ReadPin(function_switch_GPIO_Port, function_switch_Pin);

	if (system_state)
		return 2;
	else
		return 1;

}

void normal_state(uint8_t override) {
	uint32_t rising_flag = 0;
	char uart_buf[50];
	int uart_buf_len;
	while (!HAL_GPIO_ReadPin(door_sensor_GPIO_Port, door_sensor_Pin)) {

		if (person_present('F') && (!HAL_GPIO_ReadPin(button_motion_out_GPIO_Port, button_motion_out_Pin))) {
			if (actuator_state()) {
				move_actuator('U');
				while (actuator_state()) {
					HAL_Delay(20);
				}
				move_actuator('S');
			}
			/* direction('O');
			 brake(0);
			 HAL_Delay(17000);
			 brake(1);*/
			move_motor('O', 90);
			HAL_Delay(5000);
			direction('C');
			brake(0);
			while (!door_state()) {
				if (!rising_flag) {

					if (HAL_GPIO_ReadPin(wind_GPIO_Port, wind_Pin)) {

						count++;
						rising_flag = 1;
					}
				} else {
					if (!HAL_GPIO_ReadPin(wind_GPIO_Port, wind_Pin)) {

						rising_flag = 0;
					}

				}
				uart_buf_len = sprintf(uart_buf, "%lu count\r\n", count);
				HAL_UART_Transmit(&huart1, &uart_buf, uart_buf_len + 1, 100);

				while (person_present('B') && (count < 503)) {
					direction('O');
					brake(0);
					if (!rising_flag) {

						if (HAL_GPIO_ReadPin(wind_GPIO_Port, wind_Pin)) {

							count++;
							rising_flag = 1;
						}
					} else {
						if (!HAL_GPIO_ReadPin(wind_GPIO_Port, wind_Pin)) {

							rising_flag = 0;
						}

					}
					uart_buf_len = sprintf(uart_buf, "%lu count\r\n", count);
					HAL_UART_Transmit(&huart1, &uart_buf, uart_buf_len + 1,
							100);
					//HAL_Delay(2000);
					// if(!person_present('B'))
					//{

					// }
					//HAL_Delay(200);

					HAL_Delay(200);
				}

				//direction('C');
			}
			brake(1);
			if (door_state() && (!override)) {

				move_actuator('L');
				while (!actuator_state()) {
					HAL_Delay(20);
				}
				move_actuator('S');

			}
		} else {
			if (HAL_GPIO_ReadPin(button_motion_out_GPIO_Port, button_motion_Pin)) {
				if (person_present('B')) {
					if (actuator_state()) {
						move_actuator('U');
						while (actuator_state()) {
							HAL_Delay(20);
						}
						move_actuator('S');
					}
					direction('O');
					brake(0);
					HAL_Delay(15000);
					brake(1);
					HAL_Delay(5000);
					direction('C');
					brake(0);
					while (!door_state()) {
						HAL_Delay(50);
					}
					brake(1);
					if (door_state() && (!override)) {

						move_actuator('L');
						while (!actuator_state()) {
							HAL_Delay(20);
						}
						move_actuator('S');

					}
				}

			}
		}

	}
}
void emergency_close(void) {
	if (!door_state()) {

		if (actuator_state()) {
			move_actuator('U');
			while (actuator_state()) {
				HAL_Delay(20);
			}
			move_actuator('S');

		}
		direction('C');
		brake(0);
		while (!door_state()) {
			HAL_Delay(20);
		}
		brake(1);
		move_actuator('L');
		while (!actuator_state()) {
			HAL_Delay(20);
		}
		move_actuator('S');

	}

}
void remained_open(void) {
	if (HAL_GPIO_ReadPin(door_sensor_GPIO_Port, door_sensor_Pin)) {
		if (actuator_state()) {
			move_actuator('U');
			while (actuator_state()) {
				HAL_Delay(20);
			}
			move_actuator('S');
		}
		brake(0);
		direction('O');
		HAL_Delay(17000);
		brake(1);
		while (HAL_GPIO_ReadPin(door_sensor_GPIO_Port, door_sensor_Pin)) {
			HAL_Delay(50);
		}
		direction('C');
		brake(0);
		while (!door_state()) {
			HAL_Delay(50);
		}
		brake(1);
		move_actuator('L');
		while (!actuator_state()) {
			HAL_Delay(20);
		}
		move_actuator('S');
	}
}
uint8_t manager_auth(void) {

	HAL_Delay(10);
	return HAL_GPIO_ReadPin(GPIOA, manager_button_Pin);
}
uint8_t countstates(uint8_t states[]) {
	uint8_t countpos = 0;
	for (int i = 0; i < (sizeof(states) / sizeof(states[0])); i++) {
		if (states[i] < 1) {
			countpos = 0;
			break;
		} else
			countpos = 1;
	}
	return countpos;

}
void move_motor(uint8_t dir, uint8_t degree) {
	char uart_buf[50];
	int uart_buf_len;
	uint32_t rising_flag = 0;
	//uint32_t count= 0;
	uint32_t pulses = 0;
	pulses = (degree * TOTAL_PULSES) / 360;
	direction(dir);
	brake(0);

	while (count < pulses) {
		if (!rising_flag) {

			if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5)) {

				count++;
				rising_flag = 1;
			}
		} else {
			if (!HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5)) {

				rising_flag = 0;
			}

		}

		//for(uint32_t i=0;i<10000;i++);
		uart_buf_len = sprintf(uart_buf, "%lu count\r\n", count);
		HAL_UART_Transmit(&huart1, &uart_buf, uart_buf_len + 1, 100);

	}

	brake(1);
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

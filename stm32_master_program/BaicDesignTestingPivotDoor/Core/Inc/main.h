/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BC_Pin GPIO_PIN_0
#define BC_GPIO_Port GPIOA
#define buzzer_Pin GPIO_PIN_2
#define buzzer_GPIO_Port GPIOA
#define act_clock_Pin GPIO_PIN_1
#define act_clock_GPIO_Port GPIOB
#define motion_in_Pin GPIO_PIN_10
#define motion_in_GPIO_Port GPIOB
#define actuator_sensor_Pin GPIO_PIN_11
#define actuator_sensor_GPIO_Port GPIOB
#define button_motion_in_Pin GPIO_PIN_13
#define button_motion_in_GPIO_Port GPIOB
#define button_motion_out_Pin GPIO_PIN_14
#define button_motion_out_GPIO_Port GPIOB
#define wind_Pin GPIO_PIN_15
#define wind_GPIO_Port GPIOB
#define function_switch_Pin GPIO_PIN_8
#define function_switch_GPIO_Port GPIOA
#define door_sensor_Pin GPIO_PIN_9
#define door_sensor_GPIO_Port GPIOA
#define master_button_Pin GPIO_PIN_10
#define master_button_GPIO_Port GPIOA
#define led3_Pin GPIO_PIN_11
#define led3_GPIO_Port GPIOA
#define led2_Pin GPIO_PIN_12
#define led2_GPIO_Port GPIOA
#define led1_Pin GPIO_PIN_15
#define led1_GPIO_Port GPIOA
#define act_aclock_Pin GPIO_PIN_3
#define act_aclock_GPIO_Port GPIOB
#define LS1_Pin GPIO_PIN_5
#define LS1_GPIO_Port GPIOB
#define LS2_Pin GPIO_PIN_6
#define LS2_GPIO_Port GPIOB
#define FR_Pin GPIO_PIN_7
#define FR_GPIO_Port GPIOB
#define alignment_sensor_Pin GPIO_PIN_8
#define alignment_sensor_GPIO_Port GPIOB
#define motion_out_Pin GPIO_PIN_9
#define motion_out_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

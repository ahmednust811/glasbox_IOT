/*
 * HAL_MX.h
 *
 *  Created on: Jun 23, 2022
 *      Author: Ahmed
 */
#include "HAL.h"
#ifndef MAIN_HAL_MX_H_
#define MAIN_HAL_MX_H_

#define BC_Pin GPIO_PIN_0
#define BC_GPIO_Port GPIOA
#define buzzer_Pin GPIO_PIN_2
#define buzzer_GPIO_Port GPIOA
#define motion_in_Pin GPIO_PIN_10
#define motion_in_GPIO_Port GPIOB
#define actuator_sensor_Pin GPIO_PIN_11
#define actuator_sensor_GPIO_Port GPIOB
#define wind_Pin GPIO_PIN_17
#define wind_GPIO_Port GPIOB
#define button_motion_in_Pin GPIO_PIN_13
#define button_motion_in_GPIO_Port GPIOB
#define button_motion_out_Pin GPIO_PIN_14
#define button_motion_out_GPIO_Port GPIOB
#define wind_button_Pin GPIO_PIN_15
#define wind_button_GPIO_Port GPIOB
#define function_switch_Pin GPIO_PIN_4
#define function_switch_GPIO_Port GPIOA
#define door_sensor_Pin GPIO_PIN_5
#define door_sensor_GPIO_Port GPIOA
#define master_button_Pin GPIO_PIN_32
#define master_button_GPIO_Port GPIOA
#define led3_Pin GPIO_PIN_34
#define led3_GPIO_Port GPIOA
#define led2_Pin GPIO_PIN_35
#define led2_GPIO_Port GPIOA
#define act_clock_Pin GPIO_PIN_5
#define act_clock_GPIO_Port GPIOB
#define act_aclock_Pin GPIO_PIN_6
#define act_aclock_GPIO_Port GPIOB
#define FR_Pin GPIO_PIN_7
#define FR_GPIO_Port GPIOB
#define alignment_sensor_Pin GPIO_PIN_8
#define alignment_sensor_GPIO_Port GPIOB
#define motion_out_Pin GPIO_PIN_9
#define motion_out_GPIO_Port GPIOB
#define INPUT_PULLUP 0
#define INPUT_PULLDOWN 1
#define GPIO_PIN_RESET 0
#define GPIO_PIN_SET 1
#define INPUT 0
#define OUTPUT 1
#define PWM_PIN 26
//void MX_GPIO_set_type(int port,int pin,int io);
void MX_GPIO_set_type(int port,int pin,int io,int type);
int HAL_GPIO_ReadPin(int port,int pin);
void HAL_GPIO_WritePin(int port,int pin,int level);
void HAL_Delay(long ms);
void HAL_TIM_PWM_Start(void);
void HAL_TIM_UPDATE_PWM(uint32_t duty_cycle);


#endif /* MAIN_HAL_MX_H_ */

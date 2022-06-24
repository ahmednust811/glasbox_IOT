/*
 * pivot_program.c
 *
 *  Created on: Jun 24, 2022
 *      Author: Ahmed
 */

/* USER CODE BEGIN 4 */
#include "HAL_MX.h"
uint8_t person_present(uint8_t side) {

	HAL_Delay(20);
	if (side == 'F')
		return HAL_GPIO_ReadPin(motion_out_GPIO_Port, motion_out_Pin);
	else if (side == 'B')
		return !HAL_GPIO_ReadPin(motion_in_GPIO_Port, motion_in_Pin);
}

void move_actuator(uint8_t state) {
	if (state == 'L') {
		HAL_GPIO_WritePin(act_clock_GPIO_Port, act_clock_Pin, GPIO_PIN_RESET);
		HAL_Delay(20);
		HAL_GPIO_WritePin(act_aclock_GPIO_Port, act_aclock_Pin, GPIO_PIN_SET);
		HAL_Delay(50);
	} else if (state == 'U') {
		HAL_GPIO_WritePin(act_aclock_GPIO_Port, act_aclock_Pin, GPIO_PIN_RESET);
		HAL_Delay(20);
		HAL_GPIO_WritePin(act_clock_GPIO_Port, act_clock_Pin, GPIO_PIN_SET);
		HAL_Delay(50);

	} else if (state == 'S') {
		HAL_GPIO_WritePin(act_aclock_GPIO_Port, act_aclock_Pin, GPIO_PIN_RESET);
		HAL_Delay(20);
		HAL_GPIO_WritePin(act_clock_GPIO_Port, act_clock_Pin, GPIO_PIN_RESET);
		HAL_Delay(50);
	}

}
uint8_t actuator_state(void) {

	HAL_Delay(20);
	return !(HAL_GPIO_ReadPin(actuator_sensor_GPIO_Port, actuator_sensor_Pin));

}
uint8_t door_state(void) {

	HAL_Delay(20);
	return !(HAL_GPIO_ReadPin(alignment_sensor_GPIO_Port, alignment_sensor_Pin));

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
	return HAL_GPIO_ReadPin(wind_button_GPIO_Port, wind_button_Pin);

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
 		TIM2->CCR2 = 900;
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
			HAL_Delay(1500);
			TIM2->CCR2 =400;
			HAL_Delay(500);
			while (!door_state()) {HAL_Delay(5);}/*{
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
				//uart_buf_len = sprintf(uart_buf, "%lu count\r\n", count);
				//HAL_UART_Transmit(&huart1, &uart_buf, uart_buf_len + 1, 100);

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
					//uart_buf_len = sprintf(uart_buf, "%lu count\r\n", count);
					//HAL_UART_Transmit(&huart1, &uart_buf, uart_buf_len + 1,
						//	100);
					//HAL_Delay(2000);
					// if(!person_present('B'))
					//{

					// }
					//HAL_Delay(200);

					HAL_Delay(200);
				}

				//direction('C');
			}*/
			brake(1);
			if (door_state() && (!override)) {

				move_actuator('L');
				while (!actuator_state()) {
					HAL_Delay(20);
				}
				move_actuator('S');

			}
		} else {
			if (HAL_GPIO_ReadPin(button_motion_out_GPIO_Port, button_motion_out_Pin)) {
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
					move_motor('O', 90);
					HAL_Delay(5000);
					direction('C');
					brake(0);
					HAL_Delay(2000);
					TIM2->CCR2 =200 ;
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
		HAL_Delay(2000);
		TIM2->CCR2 =200 ;
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
		move_motor('O', 90);
		//brake(1);
		while (HAL_GPIO_ReadPin(door_sensor_GPIO_Port, door_sensor_Pin)) {
			HAL_Delay(50);
		}
		//direction('C');
		//brake(0);
		//HAL_Delay(2000);
		move_motor('C',100);
		brake(0);
		TIM2->CCR2 =200 ;
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
	return HAL_GPIO_ReadPin(master_button_GPIO_Port, master_button_Pin);
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
	uint32_t count= 0;
	uint32_t pulses = 0;
	pulses = (degree * TOTAL_PULSES) / 360;
	direction(dir);
	brake(0);
	while (count < pulses) {
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

		//for(uint32_t i=0;i<10000;i++);
		//uart_buf_len = sprintf(uart_buf, "%lu count\r\n", count);
		//HAL_UART_Transmit(&huart1, &uart_buf, uart_buf_len + 1, 100);

	}

	brake(1);
}
/* USER CODE END 4 */


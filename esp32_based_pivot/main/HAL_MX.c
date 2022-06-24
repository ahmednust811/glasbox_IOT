/*
 * HAL_MX.c
 *
 *  Created on: Jun 23, 2022
 *      Author: Ahmed
 */

#include "HAL_MX.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void MX_GPIO_set_type(int port,int pin,int io,int type){
gpio_pull_mode_t gpio_type = GPIO_FLOATING;
if(type == INPUT_PULLUP)gpio_type = GPIO_PULLUP_ONLY;
else{
	gpio_type = GPIO_PULLDOWN_ONLY;
}
int pin_i  = port + pin;
gpio_set_pull_mode(pin_i,gpio_type);
gpio_mode_t pin_mode;
if(io == INPUT)pin_mode = GPIO_MODE_INPUT;
else {
	pin_mode = GPIO_MODE_OUTPUT;
}
gpio_set_direction(pin_i,pin_mode);
}

int HAL_GPIO_ReadPin(int port,int pin){
int pin_i = port+pin;
return gpio_get_level(pin_i);
}

void HAL_GPIO_WritePin(int port,int pin,int level){

	int pin_i = port+pin;
	gpio_set_level(pin_i,level);
}

void HAL_Delay(long ms){

	vTaskDelay(ms/portTICK_PERIOD_MS);

}
void HAL_TIM_PWM_Start(void){


	ledc_timer_config_t tim_conf ={.speed_mode =LEDC_HIGH_SPEED_MODE,
		.duty_resolution=LEDC_TIMER_10_BIT,
		.freq_hz=1000,
		.clk_cfg = LEDC_USE_APB_CLK,
		.timer_num=LEDC_TIMER_1,
		};
		ledc_timer_config(&tim_conf);
		ledc_channel_config_t chanel ={
				.channel=LEDC_CHANNEL_0,
				.duty=0,
				.gpio_num=PWM_PIN,
				.intr_type=LEDC_INTR_DISABLE,
				.timer_sel=LEDC_TIMER_1,
				.speed_mode=LEDC_HIGH_SPEED_MODE,

		};
		ledc_channel_config(&chanel);


}


void HAL_TIM_UPDATE_PWM(uint32_t duty_cycle){
	ledc_set_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_0, duty_cycle);
			ledc_update_duty(LEDC_HIGH_SPEED_MODE,LEDC_CHANNEL_0);

}

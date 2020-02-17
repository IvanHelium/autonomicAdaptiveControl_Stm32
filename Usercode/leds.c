/*
 * leds.c
 *
 *  Created on: Feb 10, 2020
 *      Author: Ivan Mishustin
 *      mishustinivan777@gmail.com
 */

#include "leds.h"

//tim 4 generate pulse for blue led
extern TIM_HandleTypeDef htim4;

void blinkBlueLedOneTime(void)
{
 //start one pulse timer
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

}


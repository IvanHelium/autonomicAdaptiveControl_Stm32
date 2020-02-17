/*
 * leds.h
 *
 *  Created on: Feb 10, 2020
 *      Author: Ivan Mishustin
 *      mishustinivan777@gmail.com
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "main.h"
#include "gpio.h"
#include "tim.h"

#define LED_R_ON()			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET)
#define LED_R_OFF()			HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET)
#define LED_G_ON()			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET)
#define LED_G_OFF()			HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET)

void blinkBlueLedOneTime(void);


#endif /* LEDS_H_ */

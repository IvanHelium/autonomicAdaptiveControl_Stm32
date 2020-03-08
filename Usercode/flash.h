/*
 * flash.h
 *
 *  Created on: Feb 25, 2020
 *      Author: Ivan Mishustin
 *      mishustinivan777@gmail.com
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "stdint.h"
#include "stm32f7xx_hal.h"

#define USER_DATA_ADDRESS 	 ((uint32_t)0x08018000)





int eraseSectors(int sizeInBytes);
void writeFlash(void* data, int size);



#endif /* FLASH_H_ */

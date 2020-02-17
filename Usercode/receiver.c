/*
 * receiver.c
 *
 *  Created on: Feb 10, 2020
 *      Author: Ivan Mishustin
 *      mishustinivan777@gmail.com
 */


#include "receiver.h"
#include "usart.h"

#define RX_SINGLE_TRANSFER_SIZE 		2

extern UART_HandleTypeDef huart6;

static uint8_t _dmaReceiveBuffer[RX_SINGLE_TRANSFER_SIZE];

uint8_t test_data;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart == &huart6) {
		acceptAndParseInputByte(_dmaReceiveBuffer[0]);
	}
}

//config dma receiver for 1 byte
void receiverInitialize(void)
{
	HAL_UART_Receive_DMA(&huart6, _dmaReceiveBuffer, 1);
}

//define callback for received byte




//use cbuf here

/*
 * transmitter.c
 *
 *  Created on: Mar 5, 2020
 *      Author: Ivan Mishustin
 *      mishustinivan777@gmail.com
 */

#include "transmitter.h"

#include "parser.h"
#include "usart.h"

#define TX_SINGLE_TRANSFER_SIZE 		4

extern UART_HandleTypeDef huart6;

uint8_t _dmaTransmitBuffer[TX_SINGLE_TRANSFER_SIZE];

void blankSendPacket(uint8_t action)
{
	_dmaTransmitBuffer[0] = 0xBA; //header
	_dmaTransmitBuffer[1] = 0x3A;
	_dmaTransmitBuffer[2] = action;
	_dmaTransmitBuffer[3] = calculateCrc(&_dmaTransmitBuffer, TX_SINGLE_TRANSFER_SIZE);
}

void sendAction(uint8_t action)
{
	blankSendPacket(action);
	HAL_UART_Transmit_DMA(&huart6, _dmaTransmitBuffer, TX_SINGLE_TRANSFER_SIZE);
}


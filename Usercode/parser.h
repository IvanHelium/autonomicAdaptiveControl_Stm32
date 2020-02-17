/*
 * parser.h
 *
 *  Created on: Feb 10, 2020
 *      Author: Lincoln
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdint.h>


typedef struct ReceivedFrame
{
	uint8_t header;
	uint8_t type;
	uint8_t data_0;
	uint8_t data_1;
	uint8_t isHandleCommandNecessary;
}ReceivedFrame;


void acceptAndParseInputByte(uint8_t inputByte);
uint8_t checkCrc(uint8_t* buffer, uint8_t bufferSize, uint8_t receivedCrc);
uint8_t getIsHandleCommandNecessaryFlag();
void clearIsHandleCommandNecessaryFlag();

#endif /* PARSER_H_ */

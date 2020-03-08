/*
 * parser.c
 *
 *  Created on: Feb 10, 2020
 *      Author: Ivan Mishustin
 *      mishustinivan777@gmail.com
 */


#include "parser.h"

#define TEMPORARY_BUFFER_SIZE 			5


enum PARSER_STATE {
    PARSER_STATE_HEADER = 0x00,
	PARSER_STATE_TYPE = 0x01,
	PARSER_STATE_DATA_0 = 0x02,
	PARSER_STATE_DATA_1 = 0x03,
	PARSER_STATE_CRC = 0x04
};


static const uint8_t HEADER = 0xBA;

static uint8_t _parserState = PARSER_STATE_HEADER;
static uint8_t _temporaryBuffer[TEMPORARY_BUFFER_SIZE];
static uint8_t _temporaryBufferIndex = 0;


//state machine here for parser and crc summ checker




ReceivedFrame receivedFrame = {0x00, 0x00, 0x00, 0x00, 0x00};

void acceptAndParseInputByte(uint8_t inputByte)
{
	switch(_parserState)
	{
		case PARSER_STATE_HEADER:
			if(inputByte == HEADER)
			{
				_temporaryBuffer[_temporaryBufferIndex] = inputByte;
				_temporaryBufferIndex++;
				_parserState = PARSER_STATE_TYPE;
			}
			break;
		case PARSER_STATE_TYPE:
			_temporaryBuffer[_temporaryBufferIndex] = inputByte;
			_temporaryBufferIndex++;
			_parserState = PARSER_STATE_DATA_0;
			break;
		case PARSER_STATE_DATA_0:
			_temporaryBuffer[_temporaryBufferIndex] = inputByte;
			_temporaryBufferIndex++;
			_parserState = PARSER_STATE_DATA_1;
			break;
		case PARSER_STATE_DATA_1:
			_temporaryBuffer[_temporaryBufferIndex] = inputByte;
			_temporaryBufferIndex++;
			_parserState = PARSER_STATE_CRC;
			break;
		case PARSER_STATE_CRC:
			_temporaryBuffer[_temporaryBufferIndex] = inputByte;
			_temporaryBufferIndex = 0;
			_parserState = PARSER_STATE_HEADER;

			if(checkCrc(_temporaryBuffer, TEMPORARY_BUFFER_SIZE, _temporaryBuffer[4])){
				//call here if crc ok?
				receivedFrame.isHandleCommandNecessary = 1;
				receivedFrame.header = _temporaryBuffer[0];
				receivedFrame.type = _temporaryBuffer[1];
				receivedFrame.data_0 = _temporaryBuffer[2];
				receivedFrame.data_1 = _temporaryBuffer[3];

			}

			break;
		default:
			_temporaryBufferIndex = 0;
			_parserState = PARSER_STATE_HEADER;
			break;

	}
}
uint8_t calculateCrc(uint8_t* buffer, uint8_t bufferSize)
{
	int i;
	uint8_t calculatedcrc = 0x00;
	for(i = 0; i < bufferSize - 1; i++)
	{
		calculatedcrc += buffer[i];
	}
	return calculatedcrc;
}

uint8_t checkCrc(uint8_t* buffer, uint8_t bufferSize, uint8_t receivedCrc)
{
	uint8_t calculated_Crc = 0x00;

	calculated_Crc = calculateCrc(buffer, bufferSize);
	if(calculated_Crc == receivedCrc){
		return 1;
	}
	return 0;
}


uint8_t getIsHandleCommandNecessaryFlag()
{
	return receivedFrame.isHandleCommandNecessary;
}

void clearIsHandleCommandNecessaryFlag()
{
	receivedFrame.isHandleCommandNecessary = 0;
}




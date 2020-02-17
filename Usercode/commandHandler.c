/*
 * commandHandler.c
 *
 *  Created on: Feb 10, 2020
 *      Author: Lincoln
 */


#include "commandHandler.h"
#include "parser.h"
#include "leds.h"

#define SENSOR_DATA_TYPE  			0x1A
#define SAVE_KNOWLEDGEBASE_TYPE		0x2B
#define	LOAD_KNOWLEDGEBASE_TYPE		0x2C

extern ReceivedFrame receivedFrame;

uint16_t test;

void handleCommand(void)
{
	if(getIsHandleCommandNecessaryFlag()){
		switch(receivedFrame.type)
		{
			case SENSOR_DATA_TYPE:
				blinkBlueLedOneTime();
				test = transformSensorData(receivedFrame.data_0, receivedFrame.data_1);
				break;
			case SAVE_KNOWLEDGEBASE_TYPE:

				break;
			case LOAD_KNOWLEDGEBASE_TYPE:

				break;
		}

		clearIsHandleCommandNecessaryFlag();
	}
}


uint16_t transformSensorData(uint8_t lsb, uint8_t msb) //lsb - least significant byte, msb - most significant byte
{
	return (uint16_t)lsb | ((uint16_t)(msb) << 8);
}


/*
 * commandHandler.c
 *
 *  Created on: Feb 10, 2020
 *      Author: Ivan Mishustin
 *      mishustinivan777@gmail.com
 */


#include "commandHandler.h"
#include "parser.h"
#include "leds.h"
#include "logger.h"

#define SENSOR_DATA_TYPE  			0x1A
#define SAVE_KNOWLEDGEBASE_TYPE		0x2B
#define	LOAD_KNOWLEDGEBASE_TYPE		0x2C

extern ReceivedFrame receivedFrame;

static uint16_t receivedSensorData;
static uint8_t currentAction;

void handleCommand(void)
{
	if(getIsHandleCommandNecessaryFlag()){
		switch(receivedFrame.type)
		{
			case SENSOR_DATA_TYPE:
				blinkBlueLedOneTime();
				receivedSensorData = transformSensorData(receivedFrame.data_0, receivedFrame.data_1);
				//algorithm next step
				currentAction = autonomicAdaptiveControlNextStep(receivedSensorData);
				//transmitter send action
				sendAction(currentAction);
				break;
			case SAVE_KNOWLEDGEBASE_TYPE:
				eraseDataFromSectors();
				saveDatabase();
				break;
			case LOAD_KNOWLEDGEBASE_TYPE:
				loadDatabase();
				break;
		}

		clearIsHandleCommandNecessaryFlag();
	}
}


uint16_t transformSensorData(uint8_t lsb, uint8_t msb) //lsb - least significant byte, msb - most significant byte
{
	return (uint16_t)lsb | ((uint16_t)(msb) << 8);
}


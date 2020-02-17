/*
 * commandHandler.h
 *
 *  Created on: Feb 10, 2020
 *      Author: Lincoln
 */

#ifndef COMMANDHANDLER_H_
#define COMMANDHANDLER_H_

#include "stdint.h"

void handleCommand(void);
uint16_t transformSensorData(uint8_t lsb, uint8_t msb);

#endif /* COMMANDHANDLER_H_ */

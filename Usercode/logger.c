/*
 * logger.c
 *
 *  Created on: 3 мар. 2020 г.
 *      Author: Ivan Mishustin
 *      mishustinivan777@gmail.com
 */

#include "logger.h"

#include "stdint.h"
#include "flash.h"
#include "globalTypes.h"

extern Database database;

void eraseDataFromSectors()
{
	eraseSectors(sizeof(database));
}



void saveDatabase()
{
	writeFlash(&database, sizeof(Database));
}

void loadDatabase()
{
	int i;
	int j;
	for(i = 0; i < NUMBER_OF_PATTERNS; i++){
		database.databasePatternFullness[i] = *(float *)(USER_DATA_ADDRESS + i * sizeof(float));
	}

	for(i = 0; i < NUMBER_OF_PATTERNS; i++){
		for(j = 0; j < NUMBER_OF_ACTIONS; j++) {
			database.databaseSells[i][j] = *(uint16_t *)(USER_DATA_ADDRESS + NUMBER_OF_PATTERNS * sizeof(float) + i * sizeof(uint16_t) + j * sizeof(uint16_t));
		}

	}
}




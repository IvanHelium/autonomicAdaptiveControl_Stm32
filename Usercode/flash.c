/*
 * flash.c
 *
 *  Created on: Feb 25, 2020
 *      Author: Ivan Mishustin
 *      mishustinivan777@gmail.com
 */

#include "flash.h"

#define NUMBER_OF_AVAILABLE_SECTORS			9

static FLASH_EraseInitTypeDef pEraseInitInstance;
static uint32_t SectorErrorInstance;
static int sectorSizes[NUMBER_OF_AVAILABLE_SECTORS] = {32768, 131072, 262144, 262144, 262144, 262144, 262144, 262144, 262144};


static int isFlashMemoryEnough(int sizeInBytes)
{
	int i = 0;
	int summ = 0;
	for(i = 0; i < NUMBER_OF_AVAILABLE_SECTORS; i++){
		summ += sectorSizes[i];
	}
	if(sizeInBytes < summ){
		return 1;
	}
	return 0;
}

static int defineNumberOfSectors(int sizeInBytes)
{
	int i;
	int numberOfSectors = 1;
	int summ = sectorSizes[0];
	for(i = 1; i < NUMBER_OF_AVAILABLE_SECTORS; i++){
		if(summ > sizeInBytes){
			break;
		}
		summ += sectorSizes[i];
		numberOfSectors++;
	}
	return numberOfSectors;
}


int eraseSectors(int sizeInBytes)
{
	HAL_StatusTypeDef HAL_status = HAL_ERROR;
	uint8_t numberOfSectors = 1;

	if(isFlashMemoryEnough(sizeInBytes)){
		numberOfSectors = defineNumberOfSectors(sizeInBytes);
	}

	pEraseInitInstance.TypeErase = FLASH_TYPEERASE_SECTORS;
	pEraseInitInstance.Sector = (uint32_t)3U; // always start with 3 sector becouse i want so
	pEraseInitInstance.NbSectors = numberOfSectors;
	pEraseInitInstance.VoltageRange = FLASH_VOLTAGE_RANGE_3;

	if(numberOfSectors != 0){
		HAL_FLASH_Unlock();
		HAL_status = HAL_FLASHEx_Erase(&pEraseInitInstance, &SectorErrorInstance);
		HAL_FLASH_Lock();
	}

	if(HAL_status != HAL_OK)
	{
		return 1;
	}
	return 0;
}

void writeFlash(void* data, int sizeInBytes)
{
	int i;
	HAL_FLASH_Unlock();
	for(i = 0; i < sizeInBytes / sizeof(uint16_t); i++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, USER_DATA_ADDRESS + i * sizeof(uint16_t), *(uint16_t *)(data + i * sizeof(uint16_t)));
	}
	HAL_FLASH_Lock();
}






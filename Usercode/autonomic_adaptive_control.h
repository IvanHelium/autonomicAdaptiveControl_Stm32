#pragma once

#include <stdint.h>
#include "globalTypes.h"

#define PERSENTAGE_OF_RANDOM_ACTION_THROSHOLD       (0.4f)
#define PERSENTAGE_OF_50P_RANDOM_ACTION_THROSHOLD   (0.95f)


void initializeDatabase(void);

uint8_t autonomicAdaptiveControlNextStep(uint16_t currentPattern);

//grade subsystem
int gradePattern(uint16_t pattern);
//desisionMaking subsystem
static uint8_t decisionMaking(Database *databasePtr, uint16_t currentPattern);
static uint8_t chooseActionWithUnknownResultAndLogToDatabaseFullness(Database *databasePtr, uint16_t currentPattern);
static uint8_t chooseActionWithBestResult(Database *databasePtr, uint16_t currentPattern);
static uint8_t chooseActionBestOrUnknownResult(Database *databasePtr, uint16_t currentPattern);

//utility
static uint32_t getRandomValue(uint32_t maxValue);
static uint32_t getRandomValuePlatformDependent(uint32_t maxValue);
static void savePreviousState(uint16_t pattern, uint8_t action);
static void acceptDataBaseKnowledge(Database *databasePtr, uint16_t nextPattern);






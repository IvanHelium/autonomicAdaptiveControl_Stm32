#include "autonomic_adaptive_control.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "rng.h"


extern RNG_HandleTypeDef hrng;

static uint8_t prevAction = 0;
static uint16_t prevPattern = 0;

static float EMPTY_FLOAT = 0.0f;
static uint16_t EMPTY_UINT16T = 0x0000;

Database database;



void initializeDatabase()
{
	int i;
	int j;
	for(i = 0; i < NUMBER_OF_PATTERNS; i++){
		database.databasePatternFullness[i] = EMPTY_FLOAT;
	}
	for(i = 0; i < NUMBER_OF_PATTERNS; i++){
		for(j = 0; j < NUMBER_OF_ACTIONS; j++){
			database.databaseSells[i][j] = EMPTY_UINT16T;
		}
	}
}

uint8_t autonomicAdaptiveControlNextStep(uint16_t currentPattern)
{
    uint8_t currentAction = 0;
    acceptDataBaseKnowledge(&database, currentPattern);
    currentAction = decisionMaking(&database, currentPattern);
    savePreviousState(currentPattern, currentAction);
    return currentAction;
}


//-------------------------------------------
//implement your realisation of random
//-------------------------------------------

static uint32_t getRandomValue(uint32_t maxValue)
{
    uint32_t rand_value = 0;
    rand_value = ((uint32_t)rand() % maxValue);
    return rand_value;
}

static uint32_t getRandomValuePlatformDependent(uint32_t maxValue)
{
	uint32_t rand_value = 0;
	HAL_RNG_GenerateRandomNumber(&hrng, &rand_value);
	rand_value = rand_value % maxValue;
	return rand_value;
}

int gradePattern(uint16_t pattern)
{
    int gradeObstaclesBits = 0;
    int gradeDirectionsBits = 0;
    int gradeDistanceBits = 0;

    gradeObstaclesBits = (~(pattern) & 0x01) * 8000 + ((~(pattern) & 0x02)>>1) * 40000 + ((~(pattern) & 0x04)>>3) * 8000;
    gradeDirectionsBits = (((pattern & 0x78) >> 3) * -4000)/16  + 8000;
    gradeDistanceBits = (((pattern & 0x780) >> 7) * -4000)/16;

    return gradeObstaclesBits + gradeDirectionsBits + gradeDistanceBits;
}


static uint8_t chooseActionWithUnknownResultAndLogToDatabaseFullness(Database *databasePtr, uint16_t currentPattern)
{
    uint8_t action = 0;
    for(uint8_t i = 0; i < NUMBER_OF_ACTIONS; i++) {
        if(databasePtr->databaseSells[currentPattern][i] == EMPTY_SELL_VALUE){ //choose first zero knowladge
            action = i;
            //fill fullfilness
            databasePtr->databasePatternFullness[currentPattern] += 1.0f / (float)(NUMBER_OF_ACTIONS);
            break;
        }
    }
    return action;
}

static uint8_t chooseActionWithBestResult(Database *databasePtr, uint16_t currentPattern)
{
    int maxValue = -1;
    int currentGrade = 0;
    uint8_t action = 0;
    for(uint8_t i = 0; i < NUMBER_OF_ACTIONS; i++) {   //choose best knowladge
        currentGrade = gradePattern(databasePtr->databaseSells[currentPattern][i]);
        if(currentGrade >= maxValue && (databasePtr->databaseSells[currentPattern][i] != EMPTY_SELL_VALUE)){
            action = i;
            maxValue = currentGrade;
        }
    }
    return action;
}

static uint8_t chooseActionBestOrUnknownResult(Database *databasePtr, uint16_t currentPattern)
{
    uint8_t action = 0;
    uint32_t probability = 0;
    probability = getRandomValuePlatformDependent(100);
    if(probability < 50){
        action = chooseActionWithUnknownResultAndLogToDatabaseFullness(databasePtr, currentPattern);
    }
    else {
         action = chooseActionWithBestResult(databasePtr, currentPattern);
    }
    return action;
}


static uint8_t decisionMaking(Database *databasePtr, uint16_t currentPattern)
{
    uint8_t action = 0;
    float currentPatternFullness = 0.0f;
    currentPatternFullness = databasePtr->databasePatternFullness[currentPattern];
    if( currentPatternFullness <= PERSENTAGE_OF_RANDOM_ACTION_THROSHOLD ) {
        //choose random action (first empty action)
        action = chooseActionWithUnknownResultAndLogToDatabaseFullness(databasePtr, currentPattern);
    }
    else if(currentPatternFullness <= PERSENTAGE_OF_50P_RANDOM_ACTION_THROSHOLD){
         //choose random action (first empty action) with 50% probability ( you will choose best action or random)
        action = chooseActionBestOrUnknownResult(databasePtr, currentPattern);
    }
    else {
        //choose best action here
         action = chooseActionWithBestResult(databasePtr, currentPattern);
    }
    return action;
}

static void savePreviousState(uint16_t pattern, uint8_t action)
{
    prevPattern = pattern;
    prevAction = action;
}


static void acceptDataBaseKnowledge(Database *databasePtr, uint16_t nextPattern)
{
    databasePtr->databaseSells[prevPattern][prevAction] = nextPattern;
}



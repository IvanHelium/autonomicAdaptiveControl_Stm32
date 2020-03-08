/*
 * globalTypes.h
 *
 *  Created on: 5 мар. 2020 г.
 *      Author: Lincoln
 */

#ifndef GLOBALTYPES_H_
#define GLOBALTYPES_H_


#define NUMBER_OF_ACTIONS                           (7)
#define NUMBER_OF_PATTERNS                          (4096)
#define EMPTY_FULLNESS_VALUE                        (0.0f)
#define EMPTY_SELL_VALUE                            (65535u)


#pragma pack(push, 2)

typedef struct Database
{
    float databasePatternFullness[NUMBER_OF_PATTERNS];
    uint16_t databaseSells[NUMBER_OF_PATTERNS][NUMBER_OF_ACTIONS];
} Database;

#pragma pack(pop)






#endif /* GLOBALTYPES_H_ */

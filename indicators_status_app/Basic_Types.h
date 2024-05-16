#pragma once

//  Main commands:
//  Get indicators count
#define COMMAND_GET_INDICATORS_COUNT 0xA1A20000
//  Get current(selected) indicator data
#define COMMAND_GET_STAT 0xA1A20001
//  Turn the current(selected) indicator on
#define COMMAND_INDIC_ACTION_ON 0xA1A20002
//  Turn the current(selected) indicator off
#define COMMAND_INDIC_ACTION_OFF 0xA1A20003

//  The structure of the device management package
typedef struct
{
    uint32_t Command;

    //  Number of selected indicator (only with commands: COMMAND_GET_STAT
    // COMMAND_INDIC_ACTION_ON COMMAND_INDIC_ACTION_OFF)
    uint32_t IndicatorIndex;

    uint32_t crc32;
}sIndicatorCommand;

//  Package structure with the number of connected indicators
//  This is answer on
typedef struct
{
    //  COMMAND_GET_INDICATORS_COUNT
    uint32_t Command;
    uint32_t IndicatorsCount;
    uint32_t crc32;
}sIndicatorsCountPack;

//  The structure of statistics data for a single indicator
typedef struct
{
    uint64_t SerialNum;         //  Serial number of the indicator
    uint32_t Type : 4;          //  0 - lamp, 1 - LED
    uint32_t Power : 1;         //  0 - ON, 1 - OFF
    uint32_t Color : 2;         //  0 - yellow, 1 - green, 2 - red, 3 - reserve
    uint32_t Current_mA : 25;   //  I mA
    uint32_t : 32;              //  Reserve
    uint64_t ErrorCode;         //  Error code
}sOneIndicatorStats;


//  The structure of the statistics packet sent by the device in response
//  to the statistics request packet of the selected indicator
typedef struct
{
    //  COMMAND_GET_STAT
    uint32_t Command;
    uint32_t IndicatorIndex;

    //  Data of choisen indicator
    sOneIndicatorStats IndicatorData;
    uint32_t crc32;
}sIndicatorStatisticsPack;

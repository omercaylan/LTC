/**
 * @file LTC2943_i2c.c
 * @author ömer ÇAYLAN (omerceylan38@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "LTC2943_i2c.h"

bool LTC2943_Initialise(void){
#ifdef TEST
    return true;
#endif
}

bool LTC2943_Read(uint8_t address, uint8_t* dest, uint8_t dataSize){
#ifdef TEST

    uint8_t a = address;
    for (int i = 0; i < dataSize; i++)
    {
        dest[i] = 0x08;
    }
    return true;
#endif
}

bool LTC2943_Write(uint8_t address, uint8_t* src, uint8_t dataSize){
#ifdef TEST
    uint8_t a = address;
    uint8_t ar[3]={0};
    for (int i = 0; i < dataSize; i++)
    {
        ar[i] = src[i];
    }
    return true; 
#endif
}
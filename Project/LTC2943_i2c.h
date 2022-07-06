/**
 * @file LTC2943_i2c.h
 * @author ömer ÇAYLAN (omerceylan38@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef __LTC2943_I2C_H
#define __LTC2943_I2C_H

#include "common.h"

/**
 * @brief Initialise the driver
 * 
 * @return true success
 * @return false fail
 */
bool LTC2943_Initialise(void);

/**
 * @brief Read data from the chip @address to dest
 * 
 * @param address Hardcoded chip address
 * @param dest include destination  register address and and data
 * @param dataSize addres and writing data size
 * @return true 
 * @return false 
 */
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize);

/**
 * @brief Write data from src to the chip @address
 * 
 * @param address 
 * @param src include source register address and read data
 * @param dataSize addres and reading data size
 * @return true 
 * @return false 
 */
bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize);

#endif /* __LTC2943_I2C_H */
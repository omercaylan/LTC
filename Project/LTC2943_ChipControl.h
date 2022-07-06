/**
 * @file LTC2943_ChipControl.h
 * @author ömer ÇAYLAN (omerceylan38@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef __LTC2943_ChipControl_H
#define __LTC2943_ChipControl_H


#include "common.h"
#include "LTC2943_i2c.h"

//Read only
#define one  1
#define zero 0


#define LTC2943_ADDRESS         0x64 /* Static Chip address */
#define LTC2943_ALERT_RESPONSE  0x0C /* Static Alert Response address */

//Chip default value for resiger
#define DAFAULT_ALERT_VALUE    0
#define DEFAULT_THRESHOLD_HIGH 0xFF
#define DEFAULT_THRESHOLD_LOW  0x00

//Register size type
typedef uint16_t Voltage_t;
typedef uint16_t Temperature_t;
typedef uint16_t Current_t;

typedef enum {
    bit_0 = 1, // bit zero effected
    bit_1 = 2,
    bit_2 = 4,
    bit_3 = 8,
    bit_4 = 16,
    bit_5 = 32,
    bit_6 = 64,
    bit_7 = 128
}bits;

/**
 * @brief LTC2943 All Register List
 * 
 */
typedef enum {
    Register_Status                      = 0x00, //A Status
    Register_Control                     = 0x01, //B Control
    Register_Accumulated_Charge_MSB      = 0x02, //C Accumulated Charge MSB
    Register_Accumulated_Charge_LSB      = 0x03, //D Accumulated Charge LSB
    Register_Charge_Threshold_High_MSB   = 0x04, //E Charge Threshold High MSB
    Register_Charge_Threshold_High_LSB   = 0x05, //F Charge Threshold High LSB
    Register_Charge_Threshold_Low_MSB    = 0x06, //G Charge Threshold Low MSB
    Register_Charge_Threshold_Low_LSB    = 0x07, //H Charge Threshold Low LSB
    Register_Voltage_MSB                 = 0x08, //I Voltage MSB
    Register_Voltage_LSB                 = 0x09, //J Voltage LSB
    Register_Voltage_Threshold_High_MSB  = 0x0A, //K Voltage Threshold High MSB
    Register_Voltage_Threshold_High_LSB  = 0x0B, //L Voltage Threshold High LSB
    Register_Voltage_Threshold_Low_MSB   = 0x0C, //M Voltage Threshold Low MSB
    Register_Voltage_Threshold_Low_LSB   = 0x0D, //N Voltage Threshold Low LSB
    Register_Current_MSB                 = 0x0E, //O Current MSB
    Register_Current_LSB                 = 0x0F, //P Current LSB
    Register_Current_Threshold_High_MSB  = 0x10, //Q Current Threshold High MSB
    Register_Current_Threshold_High_LSB  = 0x11, //R Current Threshold High LSB
    Register_Current_Threshold_Low_MSB   = 0x12, //S Current Threshold Low MSB
    Register_Current_Threshold_Low_LSB   = 0x13, //T Current Threshold Low LSB
    Register_Temperature_MSB             = 0x14, //U Temperature MSB
    Register_Temperature_LSB             = 0x15, //V Temperature LSB
    Register_Temperature_Threshold_High  = 0x16, //W Temperature Threshold High
    Register_Temperature_Threshold_Low   = 0x17  //X Temperature Threshold Low
}LTC2943_Registers_Maps;

/* Status Alert bits */
typedef enum {
    ALERT_NONE                   = 0,
    ALERT_UNDERVOLTAGE_LOCKOUT   = 1 << 0,
    ALERT_VOLTAGE                = 1 << 1,
    ALERT_CHARGE_LOW             = 1 << 2,
    ALERT_CHARGE_HIGH            = 1 << 3,
    ALERT_TEMPERATURE            = 1 << 4,
    ALERT_CHARGE_OVER_UNDER_FLOW = 1 << 5,
    ALERT_CURRENT                = 1 << 6
}Alert;

/* Read Write Permission */
enum {
    WRITE_BIT = 0,
    READ_BIT = 1,
}Read_Write_t;

/* Chip Run Mode */
typedef enum {
    Sleep          = 0,
    Mamuel_Mode    = 1,
    Scan_Mode      = 2,
    Automatic_Mode = 3,
    MODE_ERROR     = 4
}ADC_Mode_t;

typedef enum{
    Alert_Mode             = 2,   //[10] Alert Mode. Alert functionality enabled. Pin becomes logic output.
    Charge_Complete_Mode   = 1,   //[01] Charge Complete Mode. Pin becomes logic input and accepts charge complete inverted signal (e.g., from a charger) to set accumulated charge register (C,D) to FFFFh.
    pin_disable            = 0,   //[00] ALCC pin disabled.
    Not_Allowed            = 3
}ALCC_t;

typedef enum {
    Alert_None                              = 0,
    Alert_UnderVoltageLockout               = 1 << 1,
    Alert_Voltage                           = 1 << 2,
    Alert_ChargeHigh                        = 1 << 3,
    Alert_ChargeLow                         = 1 << 4,
    Alert_Temperature                       = 1 << 5,
    AccumukatedCharge_OverFlow_or_UnderFlow = 1 << 6,
    Alert_Current                           = 1 << 7
}Alert_t;

typedef enum {
    Pres_0  = 0,
    Pres_1  = 1,
    Pres_2  = 2,
    Pres_3  = 3,
    Pres_4  = 4,
    Pres_6  = 6,
    Pres_7  = 7
}Prescaler_t;

//getBit(data,Alert_ChargeHigh);
typedef union {
    uint8_t raw;
    struct {
        uint8_t Alert_UnderVoltageLockout  : 1; /* @brief 0.bit Default : 0, Indicates recovery from undervoltage. If set to 1, a UVLO has occurred and the contents of the registers are uncertain. */
        uint8_t Alert_Voltage              : 1; /* @brief 1.bit Default : 0, Indicates one of the voltage limits was exceeded. */
        uint8_t Alert_ChargeHigh           : 1; /* @brief 2.bit Default : 0, Indicates that the ACR value exceeded the charge threshold low limit. */
        uint8_t Alert_ChargeLow            : 1; /* @brief 3.bit Default : 0, Indicates that the ACR value exceeded the charge threshold high limit.*/
        uint8_t Alert_Temperature          : 1; /* @brief 4.bit Default : 0, Indicates one of the temperature limits was exceeded.*/
        uint8_t AccumukatedCharge_OF_or_UF : 1; /* @brief 5.bit Default : 0, Indicates that the value of the ACR hit either top or bottom.*/
        uint8_t Alert_Current              : 1; /* @brief 6.bit Default : 0, Indicates one of the current limits was exceeded.*/
        uint8_t Reserved                   : 1; /* @brief 7.bit !Reseved Not Read.*/
    }bit;
}Status_t;

typedef union{
    uint8_t raw;
    struct
    {
        uint8_t     ShutDown : 1;     // 0.bit Shut down analog section to reduce
        ALCC_t      ALCC : 2;         // 2,1 bit
        Prescaler_t pres : 3;         // 5,4,3 bit 
        ADC_Mode_t  AdcMode : 2;         // 7.bit 6.bit
    }bit;
}Control_t;

typedef union{
    uint16_t TwoByte;
    struct{
        uint8_t LSB;
        uint8_t MSB;
    }Onebyte; 
}TwoByte_t;

typedef struct{
    TwoByte_t high;
    TwoByte_t low;
}ChargeThreshold_t;

typedef struct{
    uint16_t high;
    uint16_t low;
}VoltageThreshold_t;

typedef struct{
    TwoByte_t high;
    TwoByte_t low;
}CurrentThreshold_t;

typedef struct{
    uint8_t high;
    uint8_t low;
}TemperatureThreshold_t;

typedef struct
{
    Status_t                Status;
    Control_t               Control;
    ChargeThreshold_t       ChargeThreshold;
    Voltage_t               Voltage;
    VoltageThreshold_t      VoltageThreshold;
    Current_t               current;
    CurrentThreshold_t      CurrentThreshold;
    Temperature_t           Tempereture;
    TemperatureThreshold_t  TemperatureThreshold;
}LTC2943_t;

/**
 * @brief Get the ADC mode.
 * 
 * @param data 
 * @return ADC_Mode_t 
 */
ADC_Mode_t LTC2943_FindADCMode(uint8_t data);

/**
 * @brief 
 * 
 * @param mode 
 * @return uint8_t 
 */
uint8_t LTC2943_GetModeHex(ADC_Mode_t mode);

/**
 * @brief 
 * 
 * @return ADC_Mode_t 
 */
ADC_Mode_t LTC2943_GetADCMode(void);

/**
 * @brief 
 * 
 * @param mode Change the ADC mode to automatic, scan, manual or sleep.
 * @return true 
 * @return false 
 */
bool LTC2943_SetADCMode(ADC_Mode_t mode);

/**
 * @brief 
 * 
 * @param alert 
 * @return true 
 * @return false 
 */
bool LTC2943_GetStatus_Register(Status_t *alert);

/**
 * @brief Check if there is a temperature alert.
 * 
 * @return Alert_t 
 */
Alert_t LTC2943_CheckTempretureAlert(void);

/**
 * @brief 
 * 
 * @param threshold Set the charge thresholds.
 * @return true 
 * @return false 
 */
bool LTC2943_SetChargeThreshold(ChargeThreshold_t threshold);

/**
 * @brief Check that the charge is within thresholds.
 * 
 * @return Alert_t 
 */
Alert_t LTC2943_CheckChargeThreshold(void);


#endif /* __LTC2943_ChipControl_H */
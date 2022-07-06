/**
 * @file LTC2943_ChipControl.c
 * @author ömer ÇAYLAN (omerceylan38@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "LTC2943_ChipControl.h"

ADC_Mode_t FindADCMode(uint8_t data) {
    uint8_t mode = ((data & bit_7) | (data & bit_6));
    ADC_Mode_t result = MODE_ERROR;
    switch (mode)
    {
    case Sleep:
        result = Sleep;
        break;
    case Mamuel_Mode:
        result = Mamuel_Mode;
        break;
    case Scan_Mode:
        result = Scan_Mode;
        break;
    case Automatic_Mode:
        result = Automatic_Mode;
        break;
    default:
        result = MODE_ERROR;
        break;
    }
    return result;
}

uint8_t LTC2943_GetModeHex(ADC_Mode_t mode) {
    uint8_t result = 0;
    switch (mode)
    {
    case Sleep:
        result = 0x00; 
        break;
    case Mamuel_Mode:
        result = 0x40;
        break;
    case Scan_Mode:
        result = 0x80;
        break;
    case Automatic_Mode:
        result = 0xc0;
        break;
    default:
        result = MODE_ERROR;
        break;
    }
    return result;
}


ADC_Mode_t LTC2943_GetADCMode(void) {
    uint8_t data[2]={0};
    data[0] = (uint8_t)Register_Control;

    if(!LTC2943_Write(LTC2943_ADDRESS << (uint8_t)bit_0 | WRITE_BIT, &(data[0]), (uint8_t)1)) {
        return MODE_ERROR;
    }
    if(!LTC2943_Read(LTC2943_ADDRESS << (uint8_t)bit_0 | READ_BIT, &(data[1]), (uint8_t)1)) {
        return MODE_ERROR;
    }
    return LTC2943_FindADCMode(data[1]);
}

bool LTC2943_SetADCMode(ADC_Mode_t mode) {
    
    uint8_t data[2]={0};
    data[0] = (uint8_t)Register_Control;

    if(!LTC2943_Write(LTC2943_ADDRESS << (uint8_t)bit_0 | WRITE_BIT, &(data[0]), (uint8_t)1)) {
        return false;
    }
    if(!LTC2943_Read(LTC2943_ADDRESS << (uint8_t)bit_0 | READ_BIT, &(data[1]), (uint8_t)1)) {
        return false;
    }
    uint8_t modeHexNumber = LTC2943_GetModeHex(mode);

    if(modeHexNumber == MODE_ERROR)
        return false;

    data[1] |= modeHexNumber;
    
    //check Power bit, power bit not set
    data[1] &= ~0x01; //TODO: maybe transfer function
    if(!LTC2943_Write(LTC2943_ADDRESS << (uint8_t)bit_0 | WRITE_BIT, &(data[0]), (uint8_t)2)) {
        return false;
    }
    return true;
}

bool LTC2943_GetStatus_Register(Status_t *alert){
    uint8_t data[2]={0};
    data[0] = (uint8_t)Register_Status;

    if(!LTC2943_Write(LTC2943_ADDRESS << (uint8_t)bit_0 | WRITE_BIT, &(data[0]), (uint8_t)1)) {
        return false;
    }
    if(!LTC2943_Read(LTC2943_ADDRESS << (uint8_t)bit_0 | READ_BIT, &(data[1]), (uint8_t)1)) {
        return false;
    }
    alert->raw=data[1];
    return true;
}

Alert_t LTC2943_CheckTempretureAlert() {
    Alert_t result = Alert_None;
    Status_t status;
    LTC2943_GetStatus_Register(&status);
    if(status.bit.Alert_Temperature != DAFAULT_ALERT_VALUE){
        result = Alert_Temperature;
    }
    return result;
}

//TODO: Default degerler kontrol edilmeli
bool LTC2943_SetChargeThreshold(ChargeThreshold_t threshold) {
    bool result = false;
    uint8_t data[3] = {0};

    if(threshold.high.Onebyte.MSB != DEFAULT_THRESHOLD_HIGH 
    && threshold.high.Onebyte.LSB != DEFAULT_THRESHOLD_HIGH) {

        data[0]= Register_Charge_Threshold_High_MSB;
        data[1]= threshold.high.Onebyte.MSB;
        data[2]= threshold.high.Onebyte.LSB;
        if(!LTC2943_Write(LTC2943_ADDRESS << (uint8_t)bit_0 | WRITE_BIT,&(data[0]), (uint8_t)3)) {
            return false;
        } 
    }
    
    //memset(data,0,sizeof(data));

    if(threshold.low.Onebyte.MSB != DEFAULT_THRESHOLD_LOW 
    && threshold.low.Onebyte.LSB != DEFAULT_THRESHOLD_LOW) {

        data[0]= Register_Charge_Threshold_Low_MSB;
        data[1]= threshold.low.Onebyte.MSB;
        data[2]= threshold.low.Onebyte.LSB;
        if(!LTC2943_Write(LTC2943_ADDRESS << (uint8_t)bit_0 | WRITE_BIT,&(data[0]), (uint8_t)3)) {
            return false;
        }
    }
    return result;
}

Alert_t LTC2943_CheckChargeThreshold() {
    Alert_t result = Alert_None;
    Status_t status;
    LTC2943_GetStatus_Register(&status);
    if(status.bit.Alert_ChargeHigh != DAFAULT_ALERT_VALUE){
        result = Alert_ChargeHigh;
    }
    if(status.bit.Alert_ChargeLow != DAFAULT_ALERT_VALUE) {
        result = Alert_ChargeLow;
    }
    return result;
}
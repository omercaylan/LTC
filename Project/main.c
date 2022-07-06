/**
 * @file main.c
 * @author ömer ÇAYLAN (omerceylan38@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//TASK list
//[ok] Line 67 : Get the ADC mode.
//[ok] Line 77 - 82 - 86 - 91 : Change the ADC mode to automatic, scan, manual or sleep.
//[ok] Line 96 : Check if there is a temperature alert.
//[ok] Line 108 : Set the charge thresholds.
//[ok] Line 116: Check that the charge is within thresholds.
//[ok] Question: without implementation, how would you handle this IO interface in a RTOS environment?
/*  
      Answer :
1-) I use thread for diffrent mode, the purpose of this is to run the processor in parallel for performance.

Scan Mode: when the chip is put into scanning mode, it measures every 10 seconds, reads current voltage and temperature information every 10 seconds
Automatic Mode: in this mode, the chip continuously reads the current voltage and temperature data,

Thread use for chip Scane mode:  thread for Scan mode 10 second thread i can use.
Thread use for chip Automatic mode: i can use any specific thread for this i can make polling.

2-) I use mutex for critical section.

3-) I use data queue.

4-) I can make different and additional choices according to the rtos features.
*/


#include "common.h"
#include "LTC2943_ChipControl.h"


#ifdef TEST
#include <stdarg.h>
#include <stdio.h>
#endif
void my_printf(const char *fmt, ...) {
#ifdef TEST
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif
}

int main() {
    //Must be write sizeof() assert for struct 
    //Must be write big endian and little indian
    //Must be write i2c scanner for i2c address

    //LTC2943_t LTC2943;
    //memset(&LTC2943,0,sizeof(LTC2943));
    bool result = false;
    Alert_t alert = Alert_None;

    LTC2943_Initialise();
/*__________Get the ADC mode__________*/

    ADC_Mode_t ADCMode = LTC2943_GetADCMode();
    if(ADCMode != MODE_ERROR){
        my_printf("ADC Mode :%d\n",ADCMode);
    } 
    else{
        my_printf("ADC Mode Read Error\n");
    }
/*__________Change the ADC mode to automatic, scan, manual or sleep.__________ */

    ADCMode = Automatic_Mode;
    if(LTC2943_SetADCMode(ADCMode) != true){
        my_printf("I2c Error");
    }

    ADCMode = Scan_Mode;
    if(LTC2943_SetADCMode(ADCMode) != true){
        my_printf("I2c Error");
    }
    ADCMode = Mamuel_Mode;
    if(LTC2943_SetADCMode(ADCMode) != true){
        my_printf("I2c Error");
    }

    ADCMode = Sleep;
    if(LTC2943_SetADCMode(ADCMode) != true){
        my_printf("I2c Error");
    }
/*__________Check if there is a temperature alert.__________ */

    alert = LTC2943_CheckTempretureAlert();
    if(alert != Alert_Temperature) {
        my_printf("Temperature limits was exceeded\n");
    }

/*__________Set the charge thresholds.__________ */

    ChargeThreshold_t threshold;
    threshold.high.Onebyte.MSB = 0x54;
    threshold.high.Onebyte.LSB = 0x12;
    threshold.low.Onebyte.MSB = 0x44;
    threshold.low.Onebyte.LSB = 0x10;
    result = LTC2943_SetChargeThreshold(threshold);
    if(result != true){
        my_printf("Threshold Set ERROR\n");
    }


/*__________Check that the charge is within thresholds.__________ */

    alert = LTC2943_CheckChargeThreshold();
    if(alert != Alert_ChargeHigh) {
        my_printf("ACR value exceeded the charge threshold high limit\n");
    }
    else if(alert != Alert_ChargeLow) {
        my_printf("ACR value exceeded the charge threshold low limit\n");
    }

    return 0;
}
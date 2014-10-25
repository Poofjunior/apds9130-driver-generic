/**
 * \project apds9130-driver
 * \brief   a generic driver providing the most basic functionality 
 *          for the vl6180 proximity sensor. In a nutshell, you 
 *          implement the three functions read(...) and write(...), 
 *          and delayMS(...) on the microcontroller of your choice, 
 *          and the rest is done for you.
 * \author Joshua Vasquez
 * \date October 25, 2014
*/

#include "apds-9130-driver.h"

void initAPDS9130()
{
    // initialize all settings to default values.
    apds9130_Params.proxIntegrationTime = 0xff; // PTIME default value.
    apds9130_Params.waitTime = 0xff;    // 

    apds9130_Params.proxPulseCount = 0x01;
    apds9130_Params.proxDriveCurrent = 0x0; 
    //apds9130_Params.proxDiodeSelect = 0x20;
    apds9130_Params.proxGain = 0x0;


    
    // Set PDRIVE, PDIODE, and PGAIN values in CONTROL_ register.
    uint8_t dataToSend = (apds9130_Params.proxDriveCurrent << PDRIVE_) |
                         (apds9130_Params.proxGain << PGAIN_) | 
                         (apds9130_Params.proxDiodeSelect << PDIODE_);
    writeOne(I2C, apds9130_Params.deviceAddress_, CONTROL_, dataToSend); 
}

void initDataCollection()
{
    apds9130_Params.waitEnable = 1; 
    apds9130_Params.proxEnable = 1;
    apds9130_Params.powerOn    = 1;

    // Set WEN, PEN, and PON values to initialize data collection.
    uint8_t dataToSend = (apds9130_Params.waitEnable << WEN) |
                         (apds9130_Params.proxEnable << PEN) |
                         (apds9130_Params.powerOn    << PON);
    writeOne(I2C, apds9130_Params.deviceAddress_, ENABLE_, dataToSend);
}

uint16_t readProxDataNonBlocking()
{
    uint8_t dataReceived[2];
    read(I2C, apds9130_Params.deviceAddress_, PDATAL_, 2, dataReceived);
    return (uint16_t)dataReceived[0] | ((uint16_t)dataReceived[1] << 8);
}

uint16_t readProxData()
{
    initDataCollection();
    delayMS(12);
    uint16_t val = readProxDataNonBlocking();
    return val;
}


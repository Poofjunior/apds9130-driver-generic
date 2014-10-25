/**
 * \project vl6180-driver
 * \brief   a generic driver providing the most basic functionality 
 *          for the vl6180 proximity sensor. In a nutshell, you 
 *          implement the two functions read(...) and write(...),
 *          on the microcontroller of your choice, and the rest is 
            done for you.
 * \author Joshua Vasquez
 * \date October 8, 2014
*/

#include "apds-9130-driver.h"


void initAPDS9130()
{
    // initialize all settings to default values.
    apds9130-params.proxIntegrationTime = 0xff; // PTIME default value.
    apds9130-params.waitTime = 0xff;    // 

    apds9130-params.proxPulseCount = 0x01;
    apds9130-params.proxDriveCurrent = 0x0; 
    apds9130-params.proxDiodeSelect = 0x20;
    apds9130-params.proxGain = 0x0;


    
    // Set PDRIVE, PDIODE, and PGAIN values in CONTROL_ register.
    uint8_t dataToSend = (apds9130-params.proxDriveCurrent << PDRIVE_) |
                         (apds9130-params.proxGain << PGAIN_) | 
                         (apds9130-params.proxDiodeSelect << PDIODE);
    writeOne(I2C, CONTROL_, dataToSend); 
}

void initDataCollection()
{
    apds9130-params.waitEnable = 1; 
    apds9130-params.proxEnable = 1;
    apds9130-params.powerOn    = 1;

    // Set WEN, PEN, and PON values to initialize data collection.
    uint8_t dataToSend = (apds9130-params.waitEnable << WEN) |
                         (apds9130-params.proxEnable << PEN) |
                         (apds9130-params.powerOn    << PON);
    writeOne(I2C, ENABLE_, dataToSend);
}

uint16_t readProxDataNonBlocking()
{

}

uint16_t readProxData()
{
    initDataCollection();
    delayMS(12);
    uint16_t val = readProxDataNonBlocking();
    return val;
}


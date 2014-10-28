/**
 * \project apds9130-driver
 * \brief   a generic driver providing the most basic functionality 
 *          for the apds-9130 proximity sensor. In a nutshell, you 
 *          implement the three functions read(...) and write(...), 
 *          and delayMS(...) on the microcontroller of your choice, 
 *          and the rest is done for you.
 * \author Joshua Vasquez
 * \date October 25, 2014
*/

#include "apds-9130-driver.h"
struct sensorParams apds9130_Params =
{                                                                               
    0x39,   // device address (cannot be changed)                               
                                                                                
    0xff,   // proxIntegrationTime                                              
    0xff,   // waitTime                                                         
    0x01,   // proxPulseCount                                                   
                                                                                
    0x0,    // proxDriveCurrent                                                 
    0x02,   // proxDiodeSelect (cannot be changed)                              
    0x0,    // proxGain                                                         
                                                                                
    0x0,    // waitEnable                                                       
    0x0,    // proxEnable                                                       
    0x0     // powerOn                                                          
};  


void initAPDS9130()
{
    // initialize all settings to default values.
    apds9130_Params.proxIntegrationTime = 0xff; // PTIME default value.
    apds9130_Params.waitTime = 0xff;    // 

    apds9130_Params.proxPulseCount = 0x01;
    apds9130_Params.proxDriveCurrent = 0x0; 
    apds9130_Params.proxDiodeSelect = 0x02;
    apds9130_Params.proxGain = 0x0;


    
    // Set PDRIVE, PDIODE, and PGAIN values in CONTROL_ register.
    uint8_t dataToSend = (apds9130_Params.proxDriveCurrent << PDRIVE_) |
                         (apds9130_Params.proxGain << PGAIN_) | 
                         (apds9130_Params.proxDiodeSelect << PDIODE_);

    uint8_t cmdByte = (0x01 << 7) | (0x01 << 5) | CONTROL_;

    writeOne(I2C, apds9130_Params.deviceAddress_, cmdByte, dataToSend); 
}

void clearSaturation()
{
    /// Send special 'clear saturation' command.
    uint8_t cmdCode = (0x01 << 7) | (0x03 << 5) | (0x05);
    write(I2C, apds9130_Params.deviceAddress_, cmdCode, 0, 0x00);
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

    uint8_t cmdByte = (0x01 << 7) | (0x01 << 5) | ENABLE_;

    writeOne(I2C, apds9130_Params.deviceAddress_, cmdByte, dataToSend);
}

uint16_t readProxDataNonBlocking()
{
    uint8_t dataReceived[2];
    // Format cmdByte to include starting reg
    uint8_t cmdByte = (0x01 << 7) | (0x01 << 5) | (PDATAL_);
    read(I2C, apds9130_Params.deviceAddress_, cmdByte, 2, dataReceived);
    return (uint16_t)dataReceived[0] | ((uint16_t)dataReceived[1] << 8);
}

uint16_t readProxData()
{
    initDataCollection();
    delayMS(12);
    uint16_t val = readProxDataNonBlocking();
    return val;
}


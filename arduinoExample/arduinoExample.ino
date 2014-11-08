/*
 * Arduino Example of apds9130-driver
 * \author Joshua Vasquez
 * \date October 25, 2014
 */
#include "embeddedCommon.h"
#include <apds-9130-driver.h>
#include <Wire.h>


void setup()
{
    Wire.begin();
    Serial.begin(115200);
    initAPDS9130();
}

void loop()
{
/*
    uint16_t dataCollected = readProxData();
    Serial.println(dataCollected);
*/
    initAPDS9130();
    initDataCollection();
    delay(12);
    uint16_t dataCollected = readProxData();
    Serial.print("Prox Data: ");
    Serial.println(dataCollected);

    uint8_t data[30];
    uint8_t numBytes = 30;

    Serial.println("Memory Dump:");
    Wire.beginTransmission(0x39);                              
    Wire.write((1 << 7) | (1 << 5) );                                               
    Wire.endTransmission();                                             
    Wire.requestFrom(0x39, numBytes);                          
    for (uint8_t i = 0; i < numBytes; ++i)                              
    {                                                                   
        while(!Wire.available());   // wait for next byte               
        data[i] = Wire.read();                                          
    } 

    for (uint8_t j = 0; j < numBytes; ++j)
    {
        Serial.print("0x");
        if (j <= 0x0F)
            Serial.print("0");
        Serial.print(j, HEX);
        Serial.print("  ");
        Serial.println(data[j]);
    }
    Serial.println();

    clearSaturation();
    delay(50);
}

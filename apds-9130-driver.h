#ifndef APDS_9130_DRIVER_H
#define APDS_9130_DRIVER_H 
/**
 * \project apds-9130-driver
 * \brief   a generic driver providing the most basic functionality 
 *          for the apds-9130 proximity sensor. In a nutshell, you 
 *          implement the three functions read(...), write(...),
 *          and delayMs(...) on the microcontroller of your choice, 
 *          and the rest is done for you.
 * \author Joshua Vasquez
 * \date October 23, 2014
*/

#include <stdint.h>
#include "embeddedCommon.h"  /// contains read(...) and write(...) fns.
/// Important VL6180 settings
struct apds9130_Params {
    const uint8_t deviceAddress_; // 7-bit address in struct to prevent
                                         // name clashes for other sensors.
    uint8_t proxIntegrationTime;
    uint8_t waitTime;
    uint8_t proxPulseCount;

    uint8_t proxDriveCurrent;
    const uint8_t proxDiodeSelect;
    uint8_t proxGain;
    
    /// Constants for performing a read.
    uint8_t waitEnable;
    uint8_t proxEnable;
    uint8_t powerOn;
} apds9130_Params = 
{
    0x39,   // device address (cannot be changed)

    0xff,   // proxIntegrationTime
    0xff,   // waitTime
    0x01,   // proxPulseCount

    0x0,    // proxDriveCurrent
    0x20,   // proxDiodeSelect (cannot be changed)
    0x0,    // proxGain

    0x0,    // waitEnable
    0x0,    // proxEnable
    0x0     // powerOn
};

/// Prototypes:
void initAPDS9130();
uint16_t readProxData();

// The following two functions are used in tandem;
void initDataCollection();  
uint16_t readProxDataNonBlocking();


/// Register Addresses: (datasheet page 16)
const uint8_t ENABLE_   = 0x00;
    /// ENABLE_ register bitfield offsets:
    const uint8_t PON    = 0x00; 
    const uint8_t PEN    = 0x02;
    const uint8_t WEN    = 0x03;
const uint8_t PTIME_    = 0x02;
const uint8_t WTIME_    = 0x03;
const uint8_t PILTL_    = 0x08;
const uint8_t PILTH_    = 0x09;
const uint8_t PIHTL_    = 0x0A;
const uint8_t PIHTH_    = 0x0B;
const uint8_t PERS_     = 0x0C;
const uint8_t CONFIG_   = 0x0D;
const uint8_t PPULSE_   = 0x0E;
const uint8_t CONTROL_  = 0x0F;
    /// CONTROL_ register bitfield offsets:
    const uint8_t PGAIN_    = 0x02;
    const uint8_t PDIODE_   = 0x04;
    const uint8_t PDRIVE_   = 0x06;
const uint8_t ID_       = 0x12;
const uint8_t STATUS_   = 0x13;
const uint8_t CH0DATA_  = 0x14;
const uint8_t CH1DATA_  = 0x16;
const uint8_t PDATAL_    = 0x18;
const uint8_t PDATAH_   = 0x19;
const uint8_t POFFSET_  = 0x1E;

#endif // APDS_9130_H


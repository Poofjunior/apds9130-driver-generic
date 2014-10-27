#ifdef __cplusplus
extern "C" {
#endif

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
/// Important VL6180 settings declared in a struct.
struct sensorParams {
    /*const*/ uint8_t deviceAddress_; // 7-bit address in struct to prevent
                                         // name clashes for other sensors.
    uint8_t proxIntegrationTime;
    uint8_t waitTime;
    uint8_t proxPulseCount;

    uint8_t proxDriveCurrent;
    /*const*/ uint8_t proxDiodeSelect;
    uint8_t proxGain;
    
    /// Constants for performing a read.
    uint8_t waitEnable;
    uint8_t proxEnable;
    uint8_t powerOn;
}; 


/// Prototypes:
void initAPDS9130();
uint16_t readProxData();
void clearSaturation();

/// The following two functions are used together one after the other to get
///  sensor data;
void initDataCollection();  
uint16_t readProxDataNonBlocking();


/// Register Addresses: (datasheet page 16)
/// note: declaring these values as static const will create a new set of 
///       these variables in EVERY file that #includes the header file.
/// note: static const alternative would be to #define these values.
/// note: If you are constrained for space on your microcontroller, consider
///       replacing these variables with #defines.  
static const uint8_t ENABLE_   = 0x00;
/// ENABLE_ register bitfield offsets:
    static const uint8_t PON    = 0x00; 
    static const uint8_t PEN    = 0x02;
    static const uint8_t WEN    = 0x03;
static const uint8_t PTIME_    = 0x02;
static const uint8_t WTIME_    = 0x03;
static const uint8_t PILTL_    = 0x08;
static const uint8_t PILTH_    = 0x09;
static const uint8_t PIHTL_    = 0x0A;
static const uint8_t PIHTH_    = 0x0B;
static const uint8_t PERS_     = 0x0C;
static const uint8_t CONFIG_   = 0x0D;
static const uint8_t PPULSE_   = 0x0E;
static const uint8_t CONTROL_  = 0x0F;
    static const uint8_t PGAIN_    = 0x02;
    static const uint8_t PDIODE_   = 0x04;
    static const uint8_t PDRIVE_   = 0x06;
static const uint8_t ID_       = 0x12;
static const uint8_t STATUS_   = 0x13;
    static const uint8_t PVALID_ = 0x01;
    static const uint8_t PINT_ = 0x05;
    static const uint8_t PSAT_ = 0x06;
static const uint8_t CH0DATA_  = 0x14;
static const uint8_t CH1DATA_  = 0x16;
static const uint8_t PDATAL_    = 0x18;
static const uint8_t PDATAH_   = 0x19;
static const uint8_t POFFSET_  = 0x1E;

#endif // APDS_9130_H
#ifdef __cplusplus
}
#endif

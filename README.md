APDS-9130-Driver
=============

a generic driver for the APDS-9130 proximity detector 
[Datasheet](http://www.avagotech.com/docs/AV02-3425EN)

## The Sensor
The APDS-9130 is Avago's proximity sensor for short ranges 
(about 0 to 100 [cm]).

### Basic Sensor Characteristics (summarized from the datasheet)
The APDS-9130 is a proximity detector, however, it performs far better as a 
reflectance sensor.

## The Driver Interface
You, the embedded programmer, implement read(...), write(...), and delayMS(...)
for your application; and the driver handles the rest.

Note: for the examples featured, these functions have already been implemented.


## Quirks
The sensor passes data to the requesting master device over an i2c interface.
While many manufacturers tend to follow the protocol format:
    
    [i2cStartSignal] [R/W bit | 7-bit address] [starting Reg to writeTo/readFrom]
    [byte read/written 0]
    ....
    [byte read/written n]
    [i2c StopSignal]
    
The APDS-9130 changes the [starting Reg to writeTo/readFrom] value to a 
'command byte' value, which includes both the starting reg as well as 
additional information for clearing interrupts.



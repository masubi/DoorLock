# DoorLock

Snack security among other real life intrusion detection scenarios are critical
to maintaining a viable caloric supply.  This simple project detects
a sensor change and then publishes both the sensor result so that 3rd party
services can be alerted(e.g. IFTTT can send an alert or text to smart phone).

As an added bonus it also can detect if the battery runs low and also send a
corresponding alert.  

## Differences from adafruit docs
This project is based heavily on the adafruit docs shown in references section
but with some significant updates:
* updates the MQTT connection
* doesn't use EEPROM, so won't wear this out
* uses updated wifi libraries
* uses updated libraries for adafruit.io feeds
* deep sleep works compared to the source shown in references

# Components

## Hardware
* Adafruit huzzah ESP8266
* Magnetic door sensor
* Lipoly battery

### Wiring
* Pin 16 to RST (this lets us use the low power mode)
* Pin 13 to one side of door sensor
* GND to opposite side of door sensor
* VBat to the battery +
* GND to battery -
* GND to one side of the 220kΩ resistor
* VBat to one side of the 1MΩ resistor
* Pin A to the opposite side of  the 1MΩ resistor and 220kΩ resistor
* wiring example:  ![wiring_diagram](https://github.com/masubi/DoorLock/blob/master/images/wiring_diagram.png)
* [diagram src](https://learn.adafruit.com/using-ifttt-with-adafruit-io/wiring#battery-tracking)

## Service Integration
* adafruit.io
* IFTTT and corresponding smartphone

# References
* https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/power-management
* https://learn.adafruit.com/using-ifttt-with-adafruit-io/arduino-code-1?view=all

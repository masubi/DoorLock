# DoorLock

Snack security among other real life intrusion detection scenarios are critical
to maintaining a viable caloric supply.  This simple project detects
a sensor change and then publishes both the sensor result so that 3rd party
services can be alerted(e.g. IFTTT can send an alert or text to smart phone).

As an added bonus it also can detect if the battery runs low and also send a
corresponding alert.  

## Differences from tutorials
This work is based heavily on the adafruit docs shown in references section
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

## Service Integration
* adafruit.io
* IFTTT and corresponding smartphone

# References
* https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/power-management
* https://learn.adafruit.com/using-ifttt-with-adafruit-io/arduino-code-1?view=all

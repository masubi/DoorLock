/************************* User Configs *********************************/
#define CHARGE true         // true: charge i.e. don't sleep
#define PUB_DOOR true      // true: publish door to adafruitio
#define PUB_BATTERY true    // true: publish batter to adafruitio
#define SLEEP_LENGTH 600    // seconds before sleeping/delaying

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "MY_WIFI_SSID"
#define WLAN_PASS       "MY_PASS"

/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883 // use 8883 for SSL
#define AIO_USERNAME    "io.adafruit_USERNAME"
#define AIO_KEY         "io.adafruit_KEY"

/************************* Hardware Configs *********************************/
#define DOOR 13          // door gpio pin

// blink configs
#define INT_LED 0        // internal led pin
#define RED_LED 15       // red led pin
#define BLINK_DELAY 100  // ms delay before flashing

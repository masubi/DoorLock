#include "config.h"
#include <EEPROM.h>

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/****************************** WIFI and Feeds ***************************************/
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
// Note MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish door = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/door");
Adafruit_MQTT_Publish battery = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/battery");

/****************************** Fn Prototypes ***************************************/
void battery_level();
void door_check();
void door_pub();
void adafruitConnect();
void wifi_connect();
void MQTT_connect();
void onLED(int pin);
void offLED(int pin);
void blink(int pin);

/****************************** Main ***************************************/
void setup() {
  Serial.begin(115200);
  Serial.println("-----------------------------");
  Serial.println("Door Lock Sensor Setup");
  Serial.println("-----------------------------");
  pinMode(DOOR, INPUT_PULLUP);
  pinMode(INT_LED, OUTPUT);

  battery_level();
  door_check();

  if(CHARGE == false){
    // we are done here. go back to sleep.
    Serial.println("sleeeping ...");
    ESP.deepSleep(SLEEP_LENGTH * 1000000, WAKE_RF_DEFAULT);
  }else{
    Serial.println("CHARGE: true, so do not sleep");
  }
}

//
//  MAIN
//
int chargeCounter = 0;
void loop() {
  blink(0);
  blink(0);
  Serial.println("------------------");
  if(CHARGE == true){
    battery_level();
    door_check();
    delay(SLEEP_LENGTH*1000);
  }
}

void door_check(){
  if(digitalRead(DOOR) == LOW) {
    Serial.println("Door check:  closed");
    Serial.println("(It was made by those who are Dead and the Dead keep it)");
  } else {
    Serial.println("Door check:  open!");
    door_pub();
  }
}

void door_pub() {
  if(PUB_DOOR==false){
    Serial.println("PUB_DOOR: false");
    return;
  }

  adafruitConnect();

  Serial.println("door publish attempt");
  if (!door.publish("open")) {
     Serial.println(F("door publish: Failed"));
   } else {
     Serial.println(F("door publish: OK!"));
   }
}

void battery_level() {

  // read the battery level from the ESP8266 analog in pin.
  // analog read level is 10 bit 0-1023 (0V-1V).
  // our 1M & 220K voltage divider takes the max
  // lipo value of 4.2V and drops it to 0.758V max.
  // this means our min analog read value should be 580 (3.14V)
  // and the max analog read value should be 774 (4.2V).
  int level = analogRead(A0);

  // convert battery level to percent
  level = map(level, 580, 774, 0, 100);
  Serial.print("Battery level: "); Serial.print(level); Serial.println("%");

  if(PUB_BATTERY==false){
    Serial.println("PUB_BATTERY: false");
    return;
  }

  // send battery level to AIO
  adafruitConnect();
  Serial.println("Battery publish attempt");
  if (!battery.publish(level)) {
     Serial.println(F("Battery publish: Failed"));
   } else {
     Serial.println(F("Battery publish: OK"));
   }
}

void adafruitConnect(){
  wifi_connect();    // turn on wifi if we aren't connected
  MQTT_connect();  // connect to MQTT servers
}

void wifi_connect(){
  // turn on wifi if we aren't connected
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("wifi not connected");
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    Serial.println("connecting to wifi");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("wifi not connected, MQTT connect fail");
    return;
  }
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

//
//  LED helpers
//
void onLED(int pin){
  digitalWrite(pin, HIGH);
}

void offLED(int pin){
  digitalWrite(pin, LOW);
}

void blink(int pin){
  onLED(pin);
  delay(BLINK_DELAY);
  offLED(pin);
}

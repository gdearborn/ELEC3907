#include <Arduino.h>
#include "light.h"
#include "temp_humid.h"

void setup(){
    Serial.begin(115200);
    while (!Serial);   // wait for serial port to connect. Needed for native USB
    lcd.begin(16, 2);  // set up the LCD's number of columns and rows
    light_setup();
    temp_humid_setup();
}

void loop(){
    light_loop();
    temp_humid_loop();
}

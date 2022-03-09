#include <Arduino.h>
#include "light.h"
#include "temp_humid.h"

void setup(){
    Serial.begin(115200);
    while (!Serial); // wait for serial port to connect. Needed for native USB
    light_setup();
}

void loop(){
    light_loop();
}

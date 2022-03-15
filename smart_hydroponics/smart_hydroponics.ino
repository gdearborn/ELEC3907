#include <Arduino.h>
#include "light.h"
#include "temp_humid.h"
#include "ph_tds.h"
#include "water.h"

void setup(){
    Serial.begin(115200);
    while (!Serial);   // wait for serial port to connect. Needed for native USB
    light_setup();
    temp_humid_setup();
    ph_tds_setup();
    water_setup();
}

void loop(){
    light_loop();
    temp_humid_loop();
    ph_tds_loop();
    water_loop();
}

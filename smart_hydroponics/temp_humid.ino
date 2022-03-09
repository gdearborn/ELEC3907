#include "temp_humid.h"

void temp_humid_setup(){
#ifdef TEMP_DEBUG
    Serial.println("Temperature debug setup message");
#endif
#ifdef HUMID_DEBUG
    Serial.println("Humidity debug setup message");
#endif
}

void temp_humid_loop(){
#ifdef TEMP_DEBUG
    Serial.println("Temperature debug loop message");
#endif
#ifdef HUMID_DEBUG
    Serial.println("Humidity debug loop message");
#endif
}

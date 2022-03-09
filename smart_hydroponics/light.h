#ifndef _LIGHT_H
#define _LIGHT_H

#include <hp_BH1750.h>  // https://github.com/Starmbi/hp_BH1750
#include <RTClib.h>     // https://github.com/adafruit/RTClib

#define LIGHT_DEBUG
#define LIGHT_RESET_PIN 13
#define LIGHT_CONTROL_PIN 12
#define LIGHT_THRESHOLD 100
#define LIGHT_TARGET_DURATION_HOURS 0 //8
#define LIGHT_TARGET_DURATION_MINUTES 1 //0
#define LIGHT_TARGET_DURATION_SECONDS 1 //0
#define LIGHT_TARGET_BUFFER_HOURS 23 //4
#define LIGHT_TARGET_BUFFER_MINUTES 58 //0
#define LIGHT_TARGET_BUFFER_SECONDS 50  //0

void light_setup();
void light_loop();

#endif

#ifndef _TEMP_HUMID_H
#define _TEMP_HUMID_H

#include <LiquidCrystal.h>      // LiquidCrystal (Arduino) https://www.arduino.cc/en/Reference/LiquidCrystal
#include <OneWire.h>            // OneWire (Paul Stoffgren) https://github.com/PaulStoffregen/OneWire
#include <DallasTemperature.h>  // DallasTemperature (Miles Burton) https://github.com/milesburton/Arduino-Temperature-Control-Library
#include <DHT.h>                // DHT sensor library (Adafruit) https://github.com/adafruit/DHT-sensor-library

#define TEMP_DEBUG
#define HUMID_DEBUG

#define PIN_SENSOR_DS 8
#define PIN_SENSOR_DHT 9
#define DHTTYPE DHT11
//#define ONE_WIRE_BUS 2

//(1)
int buttonpin7 = 7;
int buttonState7 = 0;
//buttonpin13 = 13
//buttonState13 = 0, buttonState7 = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

DHT dht(PIN_SENSOR_DHT, DHTTYPE);
// Data wire is plugged into port 2 on the Arduino
OneWire oneWire(PIN_SENSOR_DS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// arrays to hold device address
//DeviceAddress insideThermometer;

void temp_humid_setup();
void temp_humid_loop();

#endif

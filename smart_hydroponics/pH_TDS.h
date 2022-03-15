#ifndef _PH_TDS_H
#define _PH_TDS_H

#include <EEPROM.h>             // 
#include <GravityTDS.h>         // GravityTDS (DFRobot) https://wiki.dfrobot.com/Gravity__Analog_TDS_Sensor___Meter_For_Arduino_SKU__SEN0244
#include <LiquidCrystal_I2C.h>  // LiquidCrystal I2C (Marco Schwartz) https://github.com/johnrickman/LiquidCrystal_I2C

#define PH_DEBUG
#define TDS_DEBUG

#define TdsSensorPin A1

LiquidCrystal_I2C lcd_i2c(0x27, 16, 2);
int phval = 0; // the pH meter Analog output is connected with the Arduino’s A0
unsigned long int avgval; //Store the average value of the sensor feedback
int buffer_arr[10],temp;
GravityTDS gravityTds;
 
float temperature = 25, tdsValue = 0;

void ph_tds_setup();
void ph_tds_loop();

#endif

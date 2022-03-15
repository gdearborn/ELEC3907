#include "temp_humid.h"

void temp_humid_setup(){
    lcd.begin(16, 2);  // set up the LCD's number of columns and rows
    dht.begin();
    sensors.begin();
}

void temp_humid_loop(){
    delay(1000);
    lcd.clear();
//(2)
    buttonState7 = digitalRead( buttonpin7 );
    //buttonState13 = digitalRead(buttonpin13);
//(3)
    if (buttonState7 == LOW) {
        float h = dht.readHumidity();
#ifdef HUMID_DEBUG
        Serial.print("DHT Humidity: ");
        Serial.println(h, 2);
#endif
        lcd.setCursor(0,0);
        lcd.print("Humidity:");
        lcd.print(h,2);
        //read temperature in Fahrenheit
        float f = dht.readTemperature(true);
#ifdef TEMP_DEBUG
        Serial.print("DHT Temperature: ");
        Serial.println(f, 2);
#endif
        lcd.setCursor(0,1);
        lcd.print("Temp:");
        lcd.print(f,2);
        delay(500);
//(4)
    }else{
        lcd.setCursor(0, 0);
        lcd.print("Water Temp:");
        sensors.requestTemperatures();
        lcd.setCursor(2, 1);
        lcd.print("Temp C: ");
        lcd.print(sensors.getTempCByIndex(0));
    //}else{    // (5)
    //    lcd.setCursor(0, 0);
    //    lcd.print("Press a Button");
    }
}

//void printTemp(DeviceAddress deviceAddress){
    //float tempC = sensors.getTempC(deviceAddress);
    //lcd.setCursor(2, 1);
    //lcd.print("Temp C: ");
    //lcd.print(tempC);
    //lcd.setCursor(2, 1);
    //lcd.print("Temp F:");
    //lcd.print(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
//}

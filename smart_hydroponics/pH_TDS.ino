#include "ph_tds.h"

void ph_tds_setup(){
    lcd_i2c.init(); 
    lcd_i2c.begin(16, 2);
    lcd_i2c.backlight();
    //lcd_i2c.setCursor(0, 0);
    //lcd_i2c.print("For more projects");
    //lcd_i2c.setCursor(0, 1);
    //lcd_i2c.print("CircuitSchools");
    //delay(2000);
    //lcd_i2c.clear();
    //Serial.begin(115200);
    //lcd_i2c.begin(16,2);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
}

void ph_tds_loop(){
    for(int i=0;i<10;i++){ //Get 10 sample value from the sensor for smooth the value
        buffer_arr[i]=analogRead(A0);
        delay(30);
    }
    for(int i=0;i<9;i++){ //sort the analog from small to large
        for(int j=i+1;j<10;j++){
            if(buffer_arr[i]>buffer_arr[j]){
                temp=buffer_arr[i];
                buffer_arr[i]=buffer_arr[j];
                buffer_arr[j]=temp;
            }
        }
    }
    avgval=0;
    for(int i=2;i<8;i++){   //take the average value of 6 center sample
        avgval+=buffer_arr[i];
    }
    float volt=(float)avgval*5.0/1024/6; //convert the analog into millivolt
    float ph_act = 3.5*volt; //convert the millivolt into pH value
#ifdef PH_DEBUG
    Serial.print("pH: ");
    Serial.println(ph_act, 2);
#endif
    lcd_i2c.setCursor(0, 0);
    lcd_i2c.print(" pH Val:");
    lcd_i2c.setCursor(8, 0);
    lcd_i2c.print(ph_act);
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
#ifdef TDS_DEBUG
    Serial.print(tdsValue,0);
    Serial.println("ppm");
#endif
    lcd_i2c.setCursor(0,1);
    lcd_i2c.print("TDS Val:");
    lcd_i2c.print(tdsValue);
    lcd_i2c.print("PPM");
    delay(1000);
}

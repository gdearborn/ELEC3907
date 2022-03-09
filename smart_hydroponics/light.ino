#include "light.h"

hp_BH1750 BH1750_1, BH1750_2;
RTC_DS3231 rtc;
TimeSpan light_target_buffer;
TimeSpan light_target_duration;
TimeSpan light_current_duration;
DateTime light_last_time;
bool light_current_state;

void light_setup(){
    bool rtc_ready = false;
    bool bh1750_1_ready = false;
    bool bh1750_2_ready = true;

    pinMode(LIGHT_RESET_PIN, INPUT);
    pinMode(LIGHT_CONTROL_PIN, OUTPUT);
    digitalWrite(LIGHT_CONTROL_PIN, HIGH);
    light_current_state = false;
    do{
        if (!rtc_ready){
            if (rtc.begin()){
                Serial.print("\nFound RTC");
                rtc_ready = true;
            }else{
                Serial.print("\nCouldn't find RTC");
                Serial.flush();
                delay(10);
            }
        }
        if (!bh1750_1_ready){
            if (BH1750_1.begin(BH1750_TO_GROUND)){
                Serial.print("\nFound BH1750 1");
                bh1750_1_ready = true;
            }else{
                Serial.print("\nCouldn't find BH1750 1");
                Serial.flush();
                delay(10);
            }
        }
        if (!bh1750_2_ready){
            if (BH1750_2.begin(BH1750_TO_VCC)){
                Serial.print("\nFound BH1750 2");
                bh1750_2_ready = true;
            }else{
                Serial.print("\nCouldn't find BH1750 2");
                Serial.flush();
                delay(10);
            }
        }
    }while (!(rtc_ready && bh1750_1_ready && bh1750_2_ready));
    
    light_target_buffer = TimeSpan(0, LIGHT_TARGET_BUFFER_HOURS, LIGHT_TARGET_BUFFER_MINUTES, LIGHT_TARGET_BUFFER_SECONDS);
    light_target_duration = TimeSpan(0, LIGHT_TARGET_DURATION_HOURS, LIGHT_TARGET_DURATION_MINUTES, LIGHT_TARGET_DURATION_SECONDS);
    light_current_duration = TimeSpan(0);
    light_last_time = rtc.now();
    Serial.println();
#ifdef LIGHT_DEBUG    
    Serial.print("Light current state: ");
    Serial.println(light_current_state);
    Serial.print("Light target buffer: ");
    Serial.print(light_target_buffer.totalseconds());
    Serial.println(" seconds");
    Serial.print("Light target duration: ");
    Serial.print(light_target_duration.totalseconds());
    Serial.println(" seconds");
    Serial.print("Light current duration: ");
    Serial.print(light_current_duration.totalseconds());
    Serial.println(" seconds");
    Serial.print("Light last time: ");
    printDateTime(light_last_time);
    Serial.println();
#endif
}

void light_loop(){
    bool light_new_state;
    float lux_1;
    
    DateTime now = rtc.now();
    if ((now - light_last_time).totalseconds() < 1) return;
    
    if (digitalRead(LIGHT_RESET_PIN) == HIGH){
        Serial.println("Reset button pressed");
        light_current_duration = TimeSpan(0);
    }else if (now.day() != light_last_time.day()){
        Serial.println("A new day has dawned");
        light_current_duration = TimeSpan(0);
    }
    
    Serial.print("Light current time: ");
    printDateTime(now);
    Serial.println();
    Serial.print("RTC temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");

    BH1750_1.start();
    //BH1750_2.start();
    lux_1 = BH1750_1.getLux();
    //lux_2 = BH1750_2.getLux();
    Serial.print("Light intensity: ");
    Serial.print(lux_1);
    //Serial.print(" lux");
    //Serial.print(", ");
    //Serial.print(lux_2);
    Serial.println(" lux");

    Serial.print("Light current state: ");
    Serial.println(light_current_state);
    light_new_state = light_current_state;
    if (lux_1 >= LIGHT_THRESHOLD /*&& lux_2 >= LIGHT_THRESHOLD*/){
        light_current_duration = now - light_last_time + light_current_duration;
#ifdef LIGHT_DEBUG    
        Serial.print("Light current duration: ");
        Serial.print(light_current_duration.totalseconds());
        Serial.println(" seconds");
#endif
        if (light_current_state){
            if (light_current_duration.totalseconds() >= light_target_duration.totalseconds()){
                light_new_state = false;
            }
            light_new_state = (light_current_duration.totalseconds() < light_target_duration.totalseconds()) &&
                              ((now + light_target_duration + light_target_buffer - light_current_duration).day() != now.day());
        }
    }else{
        if (light_current_state) Serial.println("Lights are broken");
        light_new_state = (light_current_duration.totalseconds() < light_target_duration.totalseconds()) &&
                          ((now + light_target_duration + light_target_buffer - light_current_duration).day() != now.day());
    }

#ifdef LIGHT_DEBUG    
    Serial.print("Light new state: ");
    Serial.println(light_new_state);
#endif
    digitalWrite(LIGHT_CONTROL_PIN, light_new_state?LOW:HIGH);
    light_current_state = light_new_state;
    light_last_time = now;
}

void printDateTime(DateTime dt){
    Serial.print(dt.year(), DEC);
    Serial.print('/');
    Serial.print(dt.month(), DEC);
    Serial.print('/');
    Serial.print(dt.day(), DEC);
    Serial.print(" ");
    Serial.print(dt.hour(), DEC);
    Serial.print(':');
    Serial.print(dt.minute(), DEC);
    Serial.print(':');
    Serial.print(dt.second(), DEC);
}

#include <Adafruit_NeoPixel.h> //Biblioteket som gjør kommunikasjon med highscore mulig
#include <Wire.h>
#include "RTClib.h"

//      REAL TIME CLOCK(RTC)
RTC_DS1307 RTC; 
//      LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

//      P I N S
const int LED_PIN = 2; 

//      C O N S T A N T S
const int SWITCH_PIN = 5;
const int NUMBER_LEDS = 60;    // Number of leds in series
const int ALARM_HOUR = 5;      // The hour the alarm is set 
const int ALARM_MINUTE = 5;    // The minute the alarm is set 
const int LIGHT_TIME = 5;      // The light time

//      V A R I A B L E S
bool Alarm_on = false;

// Setup runs once
void setup() {
  Serial.begin(9600);  
  strip.begin();                         // activate LED strip 
  Wire.begin();                          // activate communication 
  pinMode(SWITCH_PIN,INPUT_PULLUP);      // Defines switch input to input with pull-up resistor
  lightOff();                            // Turn off lights
}

// Loop runs continous
void loop(){
   DateTime now = RTC.now(); 

   Alarm_bool = digitalRead(SWITCH_PIN);
   
    if(Alarm_bool && now.hour()== 19 && now.minute()==38){
      Serial.print("alarm on");
        wakeUpLight();
        lightShow();
        
        theaterChase(strip.Color(127, 127, 127), 50); // White
        theaterChase(strip.Color(127, 0, 0), 50); // Red
        theaterChase(strip.Color(0, 0, 127), 50); // Blue

        lightOff();
    }
}

void wakeUpLight(){
       for(int j=1;j<LIGHT_TIME+1;j++){     
          for(int i=0;i<NUMBER_LEDS;i++){                
              strip.setPixelColor(i, strip.Color(j*200/LIGHT_TIME, j*200/LIGHT_TIME, j*200/LIGHT_TIME));
              strip.show();
          }
          delay(60000);
        }
}

void lightShow(){
  
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<100; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


void lightOff(){
          for(int i=0;i<NUMBER_LEDS;i++){                
              strip.setPixelColor(i, strip.Color(0, 0, 0));
              strip.show();
          }
}


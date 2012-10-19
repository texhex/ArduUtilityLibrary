#include <MillisDuration.h>

/*
MillisDuration Example 1
*/


//Pin 13 has an LED connected on most Arduino boards.
int led_pin = 13;

//Declare a MillisDuration object with a duration of 500ms
MillisDuration msDuration=MillisDuration(500);

void setup() { 
  pinMode(led_pin, OUTPUT);   
}

boolean currentLEDState=false;

void loop() {

  if (msDuration.check()) { //this is the same as .check()==true
     //duration has passed, let's do something
		
     currentLEDState=!currentLEDState; //reverse the bool: TRUE becomes FALSE, FALSE becomes TRUE
     
     //Turn the LED on or off, depeneding on currentLEDState
     digitalWrite(led_pin,currentLEDState);
  }


}

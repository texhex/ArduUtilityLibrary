#include <HeartbeatLED.h>

/*
Heartbeat Example 2
*/


//Defaults to the LED on pin 13
HeartbeatLED heartbeat=HeartbeatLED();
int randomNumber;

void setup() { 
 //Init the PRNG with the (hopefully) unconnected analog input 0
 randomSeed(analogRead(0));
}

void loop() {
  //Get a random value between 0 and 300
  randomNumber=random(0,300);
  
  //Wait this random delay...
  delay(randomNumber);

  //Because of the delay, the "heartbeat" should be "unrhythmical"
  
  //Update the heartbeat 
  heartbeat.update();


}

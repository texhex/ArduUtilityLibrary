#include <HeartbeatLED.h>

/*
Heartbeat Example
*/


//Defaults to the LED on pin 13
HeartbeatLED heartbeat=HeartbeatLED();

void setup() {                
}

void loop() {
	heartbeat.update();
}

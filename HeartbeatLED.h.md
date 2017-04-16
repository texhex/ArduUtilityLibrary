{{HeartbeatLED}} tries to imitate a human heartbeat (Long pause - BLINK - Short pause - BLINK - Long pause...) by using a LED.

### Example

{code:c++}
#include <HeartbeatLED.h>

//Defaults to the LED on pin 13
HeartbeatLED heartbeat=HeartbeatLED();

void setup() {                
}

void loop() {
	heartbeat.update();
}
{code:c++}

### Usage

Create an instance of {{HeartbeatLED()}}, then call {{update()}} from the main loop of your sketch. Each call to {{update()}} will turn on or turn off the LED as needed and not further block your sketch ({{delay()}} is not used). 

The LED can be used as an indicator if you program is still running normally (LED blinks as desired) or if your program has crashed (aka flat lined, the LED will no longer bling).

By default, {{HeartbeatLED}} will use PIN 13 as the output, but you can use a different pin (e.g. 11) also: {{ HeartbeatLED heartbeat=HeartbeatLED(11);}}

### References 

Paul Badger: Heartbeat sketch
[http://arduino.cc/playground/Main/HeartbeatSketch](http://arduino.cc/playground/Main/HeartbeatSketch)

Wikipedia: Heart Sounds
[http://en.wikipedia.org/wiki/Heart_sounds](http://en.wikipedia.org/wiki/Heart_sounds)



**
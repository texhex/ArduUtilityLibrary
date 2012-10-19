// HeartbeatLED.h
/*
HeartbeatLED Version 3, part of the ArduUtilityLibrary (http://aul.codeplex.com/)
HeartbeatLED tries to imitate a human heartbeat (Long pause – BLINK – Short pause – BLINK – Long pause...) with a LED
Copyright (C) 2011-2012 Michael 'TeX' Hex (http://www.texhex.info/)


This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA


!!! Revision history:

Version 1: First release
Version 2: Renamed the short phase to LubDub
Version 3: Used MillisDuration for the millis() check 


!!! Documentation

The most recent documentation can be found on the project homepage
http://aul.codeplex.com/wikipage?title=HeartbeatLED.h


This is a snapshot of this page:
{{HeartbeatLED}} tries to imitate a human heartbeat (Long pause – BLINK – Short pause – BLINK – Long pause...) by using a LED.

!!! Example

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

!!! Usage

Create an instance of {{HeartbeatLED()}}, then call {{update()}} from the main loop of your sketch. Each call to {{update()}} will turn on or turn off the LED as needed and not further block your sketch ({{delay()}} is not used). 

The LED can be used as an indicator if you program is still running normally (LED blinks as desired) or if your program has crashed (aka flat lined, the LED will no longer bling).

By default, {{HeartbeatLED}} will use PIN 13 as the output, but you use a different pin (e.g. 11) as well: {{ HeartbeatLED heartbeat=HeartbeatLED(11);}}

!!! References 

Paul Badger: Heartbeat sketch
[url:http://arduino.cc/playground/Main/HeartbeatSketch]

Wikipedia: Heart Sounds
[url:http://en.wikipedia.org/wiki/Heart_sounds]

*/



#ifndef _HEARTBEATLED_h
#define _HEARTBEATLED_h

#include "Arduino.h"
#include "MillisDuration.h";

enum LEDStateEnum { ON, OFF };


//Many thanks to Christian Murphy for this post about class initializer, else I would have gone mad. 
//http://arduinoetcetera.blogspot.com/2011/01/classes-within-classes-initialiser.html


class HeartbeatLED
{
public:

	//Defaults to PIN 13 as the LED pin, this LED exists on most Arduino board
	//This is the same as writing: HeartbeatLED heartbeat=HeartbeatLED(13);
	HeartbeatLED();

	//Define custom LED pin
	HeartbeatLED(uint8_t LEDPin);

public: 

	//Updates the heartbeat class. Will turn the LED on or off, as needed.
	void update();


private:
	uint8_t _ledPin;

	MillisDuration _durationBetweenBeats; 
	MillisDuration _durationLubDub;

	boolean _isLubDubPhase;
	byte _lubDubStep;


	void setup(uint8_t LEDPin);
	void displayLubDub();

	void turnLED(LEDStateEnum state);
};





#endif


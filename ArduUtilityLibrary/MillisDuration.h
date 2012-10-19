// MillisDuration.h
/*
MillisDuration Version 3, part of the ArduUtilityLibrary (http://aul.codeplex.com/)
MillisDuration keeps track if a specified duration in milliseconds (“millis”) has passed.
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
Version 2: Change duration to unsigned int to avoid any problems with rollover code
Version 3: Added MillisDurationAdv for use in other classes


!!! Documentation

The most recent documentation can be found on the project homepage
http://aul.codeplex.com/wikipage?title=MillisDuration.h

This is a snapshot of this page:


{{MillisDuration}} keeps track if a specified duration in milliseconds (“millis”) has passed.

!!! Example

{code:c++}
#include <MillisDuration.h>

// Pin 13 has an LED connected on most Arduino boards.
int led_pin = 13;

void setup() {                
	// initialize the digital pin as an output.
	pinMode(led_pin, OUTPUT);     
}

//Set duration to 500ms (1/2 second)
MillisDuration msDuration=MillisDuration(500);

boolean currentLEDState=false;

void loop() {
	if (msDuration.check()) { //is the same as .check()==true
		//duration has passed, let's do something
		
		currentLEDState=!currentLEDState; //TRUE becomes FALSE, FALSE becomes TRUE
		digitalWrite(led_pin,currentLEDState);
	}
}
{code:c++}

!!! Usage

Create an instance of {{MillisDuration}} with the desired amount of milliseconds (ms). Then call {{check()}} to check if this duration is over (result will be {{true}}). The maximum supported duration is round about 65 seconds. 

Every time the {{check()}} function is called, the class _rearms_ itself and will return true based on the current time and the given duration. This shouldn’t be a problem for 99% of all projects, but if you need very exact timing, call {{reset()}} which will recalculate the next point in time when the duration is over. 

The class was designed as immutable, so you can’t change the duration once it has been created. In case you need to change duration during runtime, the class {{MillisDurationAdv}} exists. It contains the function {{setDuration()}} to do exactly this. 

Beside this, that class also features a default constructor which allows you to use it in when you want to use it from other classes, but need to determine the duration during runtime (which is impossible with the normal class since Arduino forces you to use an initializer list as new is not implemented). 

If you don’t know what I’m talking about, you feel exactly like me about an hour ago. Read this awesome post from Christian Murphy and you will understand: [url:http://arduinoetcetera.blogspot.com/2011/01/classes-within-classes-initialiser.html]

The millis() function returns data as {{unsingned long}} and hence will rollover to 0 after approx. 50 days of operation. This does not affect this class, the duration will be correctly indicated even when the rollover happens. (As reference: 50 days are appox. 4.320.000.000ms, unsigned long max value is 4.294.967.295, +1 will make it rollover to 0).

This class does not keep track of “missed” durations. So, if you have set duration to 100ms, then your code needs 300ms to do its work, the next call to check() will be TRUE only once and return TRUE again after 100ms. 

!!! References 

Thomas Ouellet Fredericks: Metro library
[url: http://www.arduino.cc/playground/code/metro]

Arduino playground: Rollover of millis() or micros()
[url:http://arduino.cc/playground/Code/TimingRollover]

Christian Murphy: Classes within Classes - Initialiser Lists 
[url: http://arduinoetcetera.blogspot.de/2011/01/classes-within-classes-initialiser.html]

Alexander Brevig: TimedAction library 
[url:http://wiring.uniandes.edu.co/source/trunk/wiring/firmware/libraries/TimedAction/]


*/




#ifndef _MILLISDURATION_h
#define _MILLISDURATION_h

#include "Arduino.h"



/*
  --- DESCRIPTION ----


#include "MillisDuration.h"

	  // Pin 13 has an LED connected on most Arduino boards.
	  int led_pin = 13;

  // the setup routine runs once when you press reset:
  void setup() {                
	  // initialize the digital pin as an output.
	  pinMode(led_pin, OUTPUT);     
  }

  MillisDuration msDuration=MillisDuration(500);
  boolean currentLEDState=false;

  void loop() {
	  if (msDuration.check()) { //is the same as .check()==true
		  //duration has passed, let's do something

		  currentLEDState=!currentLEDState; //toogle bool: TRUE becomes FALSE, FALSE becomes TRUE
		  digitalWrite(led_pin,currentLEDState);
	  }
  }





Thanks to the following people as I used their code and description as insperation and reference:

"Metro" by Thomas Ouellet: http://www.arduino.cc/playground/Code/Metro
"TimedAction" by Alexander Brevia: http://www.alexanderbrevig.com/projects.php#wiring
"Timing Rollover information" by ?????: http://arduino.cc/playground/Code/TimingRollover
*/





//Basis class
class MillisDuration {
public:
	//Create the class with the given duration
	MillisDuration(unsigned int duration);

public:
	//"Rearms" the class with the current point in time 
	void reset();

	//Returns TRUE if the duration has passed, FALSE otherwise
	boolean check();

protected:
	void setDuration(unsigned int duration);

private:
	unsigned long _ulDuration, _ulNextTriggerValue;
	boolean _bIsRolloverHandling;
	
	//Declaring the default constructor normally brings up better error messages
	MillisDuration();
};


//ADVanced class to allow usage in other classes with durations unknown at compile time
class MillisDurationAdv : MillisDuration {
public:
	//Default constructor, the duration is set to 250ms. Please use setDuration() later on.
	MillisDurationAdv();

	//Same as MillisDuration()
	MillisDurationAdv(unsigned int duration);

public:
	//Sets a new duration and "rearms" the class 
	void setDuration(unsigned int duration);
};








#endif
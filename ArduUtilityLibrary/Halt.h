// Halt.h
/*
halt() Version 2, part of the ArduUtilityLibrary (http://aul.codeplex.com/)
Execute halt() to stop execution of your sketch permanently
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
Version 2: Added while(true)


!!! Documentation

The most recent documentation can be found on the project homepage
http://aul.codeplex.com/wikipage?title=Halt.h

This is a snapshot of this page:


Calling {{halt()}} will halt execution of your sketch permanently.

!!! Example

{code:c++}
#include <Halt.h>

void setup() { 
  Serial.begin(9600);   

  //Wait a little bit
  delay(2000);
}

void loop() {
  //Start countdown  
  Serial.println(F("Three..."));
  delay(1000);  
  Serial.println(F("Two..."));
  delay(1000);
  Serial.println(F("One..."));
  delay(1000);

  halt();   //No code is executed beyond this line
   
  Serial.println(F("You will not see this message..."));
}
{code:c++}

!!! Usage

Execute {{halt()}} to stop execution of your sketch permanently.

Please note that this function does *NOT* turn off any digital outputs. They will stay in the current state as they are when halt() is executed.

If you have any project that needs an "Emergency Off" function (because it includes moving parts that could harm somebody), this function is not what you are searching for. You better use an external watchdog that turns off the board completely. 

!!! References 

Peter Knight (Cathedrow): Narcoleptic, Sleep library for Arduino
[url:https://code.google.com/p/narcoleptic/]

Rocket Scream: Lightweight Low Power Arduino Library
[url:http://www.rocketscream.com/blog/2011/07/04/lightweight-low-power-arduino-library/]

Ruben Laguna: Arduino Sleep Mode - Waking Up When Receiving Data on the USART
[url:http://rubenlaguna.com/wp/2008/10/15/arduino-sleep-mode-waking-up-when-receiving-data-on-the-usart/index.html/]

Some more information about Arduino sleep can be found in this playground post:
[url:http://www.arduino.cc/playground/Learning/ArduinoSleepCode]


*/


#ifndef _HALT_h
#define _HALT_h

#include "Arduino.h"

#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>



void halt_internal_func() {	
	/* 
	According to the docs (http://www.nongnu.org/avr-libc/user-manual/group__avr__sleep.html), this would be right way to enable a sleep mode where the device has a chance to wake up again

	------------------------------
	set_sleep_mode(<mode>);
	cli(); //aka noInterrupts() in Arduino 

	sleep_enable();
	sei(); //aka interrupts() in Arduino        
	sleep_cpu();

	sleep_disable();
	-------------------------------

	But since we intend to shut it down, we will simply deactive any interrupts, disable the watchdog time and then set the CPU to sleep which should trigger a "never wake up again" sleep
	*/

	//Disable the watchdog timer, in case it is set do perform a reset or anything else which would stop us from halting the CPU
	//http://www.nongnu.org/avr-libc/user-manual/group__avr__watchdog.html
	wdt_disable();

	//Disable any interrupts that might still be active
	noInterrupts();

	//Sleep mode: Power down
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	//Enable sleep bit, else sleep_cpu() will not do anything
	//It would also be possible to skip this step and just call sleep_mode(), but I think the longer version with sleep_cpu() is easier to understand
	sleep_enable();

	//I really have no idea what a "Brown Out Detector" is, so I'm not using this macro 
	//http://www.nongnu.org/avr-libc/user-manual/group__avr__sleep.html
	//sleep_bod_disable();	

	//Turn off whatever the CPU is capable to turn off
	//http://www.nongnu.org/avr-libc/user-manual/group__avr__power.html
	power_all_disable();

	//Good night, see you next reset!
	sleep_cpu(); 
}



void halt() {
	//This endless loop is in place for two reasons:
	//- If the first try to put Arduino to sleep does not work, keep on trying until it works.
	//- This code will never return and thus halt() will work as exptected: it completly halts execution. 	
	//
	//I know a recursive function call would also be possible, but I always wanted to have while(true) for a good reason in a program ;)
	while(true){
		halt_internal_func();		
	}

}










#endif


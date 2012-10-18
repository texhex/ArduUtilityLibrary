// Halt.h

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


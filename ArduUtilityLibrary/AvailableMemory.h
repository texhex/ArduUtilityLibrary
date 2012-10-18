//AvailableMemory.h
/*
availableMemory() Version 1, part of the ArduUtilityLibrary (http://aul.codeplex.com/)
This function returns the number of free memory (in bytes) 
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


!!! Documentation

The most recent documentation can be found on the project homepage
http://aul.codeplex.com/wikipage?title=AvailableMemory.h

This is a snapshot of this page:


Executing {{availableMemory()}} returns the number of free memory (in bytes) 

!!! Example

{code:c++}
void setup() { 
 Serial.begin(9600);   
}

void loop() {
  int iFreeMem=availableMemory();
  
  Serial.print(F("Free memory (bytes): "));
  Serial.print(iFreeMem);
  Serial.println();
    
  delay(1500);
}
{code:c++}

!!! Usage

Execute {{availableMemory()}} to get the number of free bytes in memory. 

Please note that memory requirements can change very fast in any sketch and even by executing this function the free memory is altered. Use the information as _one_ indicator if your sketch goes haywire.

I have created sketches that reported 1100 free bytes in the main loop() function just to crash a second later because a different routine needed more memory than expected.

!!! References 

This function is based on get_free_memory() by "Paul" described in the following post:
[url:http://forum.pololu.com/viewtopic.php?p=4218&sid=7f231afba6e616f87950ffa4689d94f0#p4218]

An advanced version of this code is freeRam() found here:
[url:http://www.arduino.cc/playground/Code/AvailableMemory]

The original code is also used inside the SdFat Library (SdFatUtil.h - FreeRam()) and documented in "Jonathan Oxer, Hugh Blemings: Practical Arduino: Cool Projects for Open Source Hardware", so I’m sticking with the original version.

The name "availableMemory" is taken from "flash_example.pde", an example for the Flash library created by Mikal Hart 
[url:http://arduiniana.org/libraries/flash/]



*/




#ifndef _AVAILABLEMEMORY_H
#define _AVAILABLEMEMORY_H

#include "Arduino.h"


//Returns the number of free memory (in bytes) that is currently available. 
int availableMemory()
{
	extern int  __bss_end;
	extern int *__brkval;

	int free_memory;

	if((int)__brkval == 0)
		free_memory = ((int)&free_memory) - ((int)&__bss_end);
	else
		free_memory = ((int)&free_memory) - ((int)__brkval);

	return free_memory;
}






#endif
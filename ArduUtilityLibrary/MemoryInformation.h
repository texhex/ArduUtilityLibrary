//MemoryInformation.h
/*
MemoryInformation Version 2, part of the ArduUtilityLibrary (http://aul.codeplex.com/)
Returns the size (in bytes) of different memory sections
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
Version 2: Added Printable support


!!! Documentation

The most recent documentation can be found on the project homepage
http://aul.codeplex.com/wikipage?title=MemoryInformation.h

This is a snapshot of this page:


The members of {{MemoryInformation}} return the size (in bytes) of different memory sections

!!! Example

{code:c++}
#include <MemoryInformation.h>

void setup() { 
 Serial.begin(9600);   
}

//Create MemoryInformation class
MemoryInformation memInfo=MemoryInformation();

void loop() {
  //If you want to display all values at once, sent it directly to print() or println():
  Serial.println(memInfo);
  Serial.println(F("-----------------------------"));
 
  //Or you access each member:
  Serial.print(F("DATA section: "));
  Serial.println( memInfo.dataSize() );  
  
  Serial.print(F("BSS section: "));
  Serial.println( memInfo.bssSize() );  
  
  Serial.print(F("Heap size: "));
  Serial.println( memInfo.heapSize() );  
  
  Serial.print(F("Free memory: "));
  Serial.println( memInfo.freeMemorySize() );

  Serial.print(F("Stack size: "));
  Serial.println( memInfo.stackSize() );

  Serial.print(F("RAM Total Size: "));
  Serial.println( memInfo.ramSize() );
  
  Serial.println(F("-----------------------------"));
  
  //Refresh memory information
  memInfo.refresh();
 
  delay(1500);
}
{code:c++}

!!! Usage

This class can aid in debugging, if you want to know how the memory on your Arduino is currently organized.  In case you just want to know how many free memory your board currently has, use {{availableMemory()}} in [AvailableMemory.h].

If you just want to know how the memory is currently organized, just sent the class instance to Serial:  {{Serial.println(memInfo);}}. To know how big the different sections are use the corresponding function like this {{int i=memInfo.heapSize();}}. The data can be refreshed at any time by calling {{memInfo.refresh();}}.

The memory on a ATmega CPUs is divided into several parts: DATA and BSS are static, they do not change when executing your sketch. Heap is used every time you need memory, and Stack is used when one function calls another (e.g. you call pinMode(13, OUTPUT) from inside the loop() function). Between them the free memory is located. Note also that Heap grows towards the free memory section, while Stack grows downward (as indicated by the arrows).

{{
  +----------+----------+--------+--------------+--------+
  | DATA     | BSS      |  Heap  |     FREE     |  Stack |
  | (Static) | (Static) |  --->  |     MEM      |  <---  |
  +----------+----------+--------+--------------+--------+
}}
For a much better description about this topic, please see "Jean-Claude Wippler: ATmega memory use" [url:http://jeelabs.org/2011/05/22/atmega-memory-use/].

!!! References 

Smilen Dimitrov: Corrupt Array Variables And Memory
[url:http://www.arduino.cc/playground/Main/CorruptArrayVariablesAndMemory]

The general calculation code was published by Marc Compere in this forum post (Please be warned that the calculation is incorrect if {{__brkval}} is 0):
[url:http://arduino.cc/forum/index.php/topic,27536.msg204023.html#msg204023]

AVR Malloc Manual:
[url:http://www.nongnu.org/avr-libc/user-manual/malloc.html]

Andy Brown: Debugging AVR dynamic memory allocation
[url:http://andybrown.me.uk/wk/2011/01/01/debugging-avr-dynamic-memory-allocation/]


*/



#ifndef _MEMORYINFORMATION_h
#define _MEMORYINFORMATION_h

#include "Arduino.h"

class MemoryInformation : public Printable
{
public:
	//Default constructor, performs refresh() automatically
	MemoryInformation();

public: 
	//Refreshes the data
	void refresh();

	//each of these functions return the size (in bytes) of the given section
	int dataSize();
	int bssSize();
	int heapSize();
	int freeMemorySize();
	int stackSize();
	int ramSize();

private:
	int _ramSize, _dotDataSection, _dotBssSection, _heapSection, _freeMem, _stackSection;

public:
	//Printable support
	virtual size_t printTo(Print& p) const;

};



#endif
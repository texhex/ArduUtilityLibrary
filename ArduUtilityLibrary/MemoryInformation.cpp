#include "MemoryInformation.h"
/*
For a description and detailed license information, please see the .h file noted above.


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
*/




#include "AvailableMemory.h" //For availableMemory() function


MemoryInformation::MemoryInformation() {
	refresh();
}


void MemoryInformation::refresh()
{
  //import all required variabled
  extern int __data_start, __data_end;  
  //RAMEND is automatically available
  extern int __bss_start, __bss_end;
  extern int *__brkval, __heap_start; //Sadly, this isn't available: __heap_end;
  //SP is automatically available
  
 
  //__data_start seems to be always 256 (0x0100) - the memory pictures of AVR also show this (http://www.nongnu.org/avr-libc/user-manual/malloc.html)  
  _ramSize   = (int) RAMEND - (int) &__data_start;
  
  //Special notice about RAMEND:
  //RAMEND should be 2048 on my UNO R3 as per specs, but is somehow 2047
  //According to AVR docs: "RAMEND: The last on-chip RAM address. " (http://www.nongnu.org/avr-libc/user-manual/group__avr__io.html)
  //Given that C and C++ start counting at 0, I'm assuming that the first byte has the address of 0 and thus adding one byte to ramSize
  //Adding all section again, the result is 2048 so I think this calculation is correct.
  _ramSize++;
    
  //This calculation should be 100% accurate, since "avr-size.exe THIS-SKETCH.cpp.elf" shows the same size in column "data"
  _dotDataSection = (int) &__data_end - (int) &__data_start;

  //This calculation should be 100% accurate, since "avr-size.exe THIS-SKETCH.cpp.elf" shows the same size in column "bss"  
  _dotBssSection = (int) &__bss_end - (int) &__bss_start;
  
  //__brkval can be 0 if nothing was allocated so far (http://andybrown.me.uk/wk/2011/01/01/debugging-avr-dynamic-memory-allocation/)
  _heapSection=0;
  if (__brkval != 0) {
     _heapSection=(int) __brkval - (int) &__heap_start;
  }

  _freeMem=availableMemory();

  //Stack
  _stackSection = (int) RAMEND - (int) SP;
}


int MemoryInformation::ramSize() {
	return _ramSize;
}

int MemoryInformation::dataSize(){
	return _dotDataSection;
}

int MemoryInformation::bssSize() {
	return _dotBssSection;
}

int MemoryInformation::heapSize() {
	return _heapSection;
}

int MemoryInformation::freeMemorySize(){
	return _freeMem;
}

int MemoryInformation::stackSize(){
	return _stackSection;
}

//Printable support
size_t MemoryInformation::printTo(Print& p) const
{
	size_t size=0;

	size += p.print(F("DATA....: "));
	size += p.println(_dotDataSection);  

	size += p.print(F("BSS.....: "));
	size += p.println(_dotBssSection);  

	size += p.print(F("Heap....: "));
	size += p.println(_heapSection);  

	size += p.print(F("Free mem: "));
	size += p.println(_freeMem);

	size += p.print(F("Stack...: "));
	size += p.println(_stackSection);

	size += p.print(F("RAM size: "));
	size += p.println(_ramSize);

	return size;
}



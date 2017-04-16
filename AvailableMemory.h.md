Executing {{availableMemory()}} returns the number of free memory (in bytes) 

### Example

{code:c++}
#include <AvailableMemory.h>

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

### Usage

Execute {{availableMemory()}} to get the number of free bytes in memory. 

Please note that memory requirements can change very fast in any sketch and even by executing this function the free memory is altered. Use the information as _one_ indicator if your sketch goes haywire.

I have created sketches that reported 1100 free bytes in the main loop() function just to crash a second later because a different routine needed more memory than expected.

### References 

This function is based on {{get_free_memory()}} by "Paul" described in the following post:
[http://forum.pololu.com/viewtopic.php?p=4218&sid=7f231afba6e616f87950ffa4689d94f0#p4218](http://forum.pololu.com/viewtopic.php?p=4218&sid=7f231afba6e616f87950ffa4689d94f0#p4218)

An advanced version of this code is {{freeRam()}} found here:
[http://www.arduino.cc/playground/Code/AvailableMemory](http://www.arduino.cc/playground/Code/AvailableMemory)

The original code is also used inside the SdFat Library (SdFatUtil.h - FreeRam()) and documented in "Jonathan Oxer, Hugh Blemings: Practical Arduino: Cool Projects for Open Source Hardware", so I’m sticking with the original version.

The name "availableMemory" is taken from "flash_example.pde", an example for the Flash library created by Mikal Hart 
[http://arduiniana.org/libraries/flash/](http://arduiniana.org/libraries/flash/)





**
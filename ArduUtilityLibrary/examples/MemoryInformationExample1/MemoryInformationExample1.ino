#include <MemoryInformation.h>

/*
MemoryInformation Example
*/


void setup() { 
 Serial.begin(9600);   
}

MemoryInformation memInfo=MemoryInformation();

void loop() {
 
  //If you want to display all values at once, sent it directly to print() or println():
  Serial.println(memInfo);
  Serial.println(F("-----------------------------"));
 
 
  //Or you access each member yourself:
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
  
   
  
  //Waste some bytes
  produceMemoryLeak(11);
  
  //Refresh memory information
  memInfo.refresh();
 
  delay(3000);
}


//This function will waste some bytes for no reason at all
void produceMemoryLeak(unsigned int size) {
  if (malloc(size)==NULL) {
   Serial.println(F("produceMemoryLeak() failed - Memory full?"));
  }
}



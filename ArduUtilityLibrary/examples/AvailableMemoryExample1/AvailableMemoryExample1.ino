#include <AvailableMemory.h>

/*
availableMemory() Example
*/


void setup() { 
 Serial.begin(9600);   
}

void loop() {
  int iFreeMem=availableMemory();
  
  Serial.print(F("Free memory (bytes): "));
  Serial.print(iFreeMem);
  Serial.println();
    
  delay(1500);
  
  //Waste some bytes
  produceMemoryLeak(11);
 
}


//This function will waste some bytes for no reason at all
void produceMemoryLeak(unsigned int size) {
  if (malloc(size)==NULL) {
   Serial.println(F("produceMemoryLeak() failed - Memory full?"));
  }
}




#include <Halt.h>

/*
halt() Example 1
*/

//Pin 13 has an LED connected on most Arduino boards.
int led_pin = 13;


void setup() { 
  Serial.begin(9600);   

  pinMode(led_pin, OUTPUT);   

  //Wait a little bit
  delay(2000);
}

void loop() {
  //Turn LED on - It just looks nicer :)
  digitalWrite(led_pin,true);
  
    
  //A little word of warning might be a good idea
  Serial.println(F("WARNING!"));
  Serial.println(F("This will turn off your Arduino!"));
  Serial.println(F("You will need to reset or power cycle it to wake it up again"));
  Serial.println();

 //Start countdown
  
  Serial.println(F("Five..."));
  delay(1000);
  
  Serial.println(F("Four..."));
  delay(1000);
  
  Serial.println(F("Three..."));
  delay(1000);
  
  Serial.println(F("Two..."));
  delay(1000);

  Serial.println(F("One..."));
  delay(1000);

  Serial.println(F("Halting!"));
  delay(1000);

  halt();   //No code is executed beyond this line
  
  
  Serial.println(F("You will not see this message..."));

}


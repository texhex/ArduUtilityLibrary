Calling ``halt()`` will halt execution of your sketch permanently.

### Example

```cpp
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
```

### Usage

Execute ``halt()`` to stop execution of your sketch permanently.

Please note that this function does **NOT** turn off any digital outputs. They will stay in the current state as they are when halt() is executed.

If you have any project that needs an "Emergency Off" function (because it includes moving parts that could harm somebody), this function is not what you are searching for. You better use an external watchdog that turns off the board completely. 

### References 

Peter Knight (Cathedrow): Narcoleptic, Sleep library for Arduino
https://code.google.com/p/narcoleptic/

Rocket Scream: Lightweight Low Power Arduino Library
http://www.rocketscream.com/blog/2011/07/04/lightweight-low-power-arduino-library/

Ruben Laguna: Arduino Sleep Mode - Waking Up When Receiving Data on the USART
http://rubenlaguna.com/wp/2008/10/15/arduino-sleep-mode-waking-up-when-receiving-data-on-the-usart/index.html/

Some more information about Arduino sleep can be found in this playground post:
http://www.arduino.cc/playground/Learning/ArduinoSleepCode



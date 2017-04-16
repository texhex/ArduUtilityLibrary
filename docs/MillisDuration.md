``MillisDuration`` keeps track if a specified duration in milliseconds (“millis”) has passed.

### Example

```cpp
#include <MillisDuration.h>

// Pin 13 has an LED connected on most Arduino boards.
int led_pin = 13;

void setup() {                
	// initialize the digital pin as an output.
	pinMode(led_pin, OUTPUT);     
}

//Set duration to 500ms (1/2 second)
MillisDuration msDuration=MillisDuration(500);

boolean currentLEDState=false;

void loop() {
	if (msDuration.check()) { //is the same as .check()==true
		//duration has passed, let's do something
		
		currentLEDState=!currentLEDState; //TRUE becomes FALSE, FALSE becomes TRUE
		digitalWrite(led_pin,currentLEDState);
	}
}
```

### Usage

Create an instance of ``MillisDuration`` with the desired amount of milliseconds (ms). Then call ``check()`` to check if this duration is over (result will be ``true``). The maximum supported duration is round about 65 seconds. 

Every time the ``check()`` function is called, the class _rearms_ itself and will return true based on the current time and the given duration. This shouldn’t be a problem for 99% of all projects, but if you need very exact timing, call ``reset()`` which will recalculate the next point in time when the duration is over. 

The class was designed as immutable, so you can’t change the duration once it has been created. In case you need to change duration during runtime, the class ``MillisDurationAdv`` exists. It contains the function ``setDuration()`` to do exactly this. 

Beside this, that class also features a default constructor which allows you to use it in when you want to use it from other classes, but need to determine the duration during runtime (which is impossible with the normal class since Arduino forces you to use an initializer list as new is not implemented). 

If you don’t know what I’m talking about, you feel exactly like me about an hour ago. Read this awesome post from Christian Murphy and you will understand: [http://arduinoetcetera.blogspot.com/2011/01/classes-within-classes-initialiser.html](http://arduinoetcetera.blogspot.com/2011/01/classes-within-classes-initialiser.html)

The ``millis()`` function returns data as ``unsingned long`` and hence will rollover to 0 after approx. 50 days of operation. This does not affect this class, the duration will be correctly indicated even when the rollover happens. (As reference: 50 days are appox. 4.320.000.000ms, unsigned long max value is 4.294.967.295, +1 will make it rollover to 0).

This class does not keep track of “missed” durations. So, if you have set duration to 100ms, then your code needs 300ms to do its work, the next call to check() will be TRUE only once and return TRUE again after 100ms. 

### References 

Thomas Ouellet Fredericks: Metro library
http://www.arduino.cc/playground/code/metro

Arduino playground: Rollover of millis() or micros()
http://arduino.cc/playground/Code/TimingRollover

Christian Murphy: Classes within Classes - Initialiser Lists 
http://arduinoetcetera.blogspot.de/2011/01/classes-within-classes-initialiser.html

Alexander Brevig: TimedAction library 
http://wiring.uniandes.edu.co/source/trunk/wiring/firmware/libraries/TimedAction/


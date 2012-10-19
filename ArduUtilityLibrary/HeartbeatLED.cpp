#include "HeartbeatLED.h"
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


#include "MillisDuration.h"


//These values should imitate the heartbeat quite well
#define Duration_Between_Beats_Millisconds 1187   
#define Duration_For_Lub_and_Dub_Milliseconds 221  //I didn't come up with this name, see this: http://en.wikipedia.org/wiki/Heart_sounds





HeartbeatLED::HeartbeatLED() 
	: _durationBetweenBeats(Duration_Between_Beats_Millisconds), 
	_durationLubDub(Duration_For_Lub_and_Dub_Milliseconds)
{
	setup(13);	
}

HeartbeatLED::HeartbeatLED(uint8_t LEDPin) 
	: _durationBetweenBeats(Duration_Between_Beats_Millisconds), 
	_durationLubDub(Duration_For_Lub_and_Dub_Milliseconds)

{
	setup(LEDPin);
}


void HeartbeatLED::setup(uint8_t LEDPin) 
{
	_ledPin=LEDPin;
	pinMode(_ledPin, OUTPUT);     

	_isLubDubPhase=false;
	_lubDubStep=0;
}


void HeartbeatLED::update()
{
	if (_isLubDubPhase) {
		//we are in the LubDub phase

		displayLubDub();

	} else {

		//we are waiting for the next beat
		if (_durationBetweenBeats.check()) { 

#ifdef AUL_DEBUG
			Serial.println("AUL Heartbeat: --LubDub starting--");
#endif

			displayLubDub();
		}
	}


}

void HeartbeatLED::displayLubDub()
{

	if (_isLubDubPhase==false) {

		_isLubDubPhase=true; //LubDub phase is now active
		
		_lubDubStep=1; //we are currently in phase 1
		turnLED(ON);

		_durationLubDub.reset(); //start timing now
	} else {

		if (_durationLubDub.check()) {
			
			//Move to next phase
			_lubDubStep++;

			switch (_lubDubStep) {

            //1 is not present since we have entered this phase already (see above)
			case 2: 
				turnLED(OFF);
				break;
			case 3:
				turnLED(ON);
				break;
			case 4:
				turnLED(OFF);
				_isLubDubPhase=false;

				break;
			}
			

		} //Checking _durationLubDub



	}

}

void HeartbeatLED::turnLED(LEDStateEnum state) 
{
	if (state == ON) {
		digitalWrite(_ledPin,HIGH);
#ifdef AUL_DEBUG
		Serial.println("AUL Heartbeat: LED ON at ");
		Serial.println(millis());
#endif
	} else {
		digitalWrite(_ledPin,LOW);
#ifdef AUL_DEBUG
		Serial.println("AUL Heartbeat: LED OFF at ");
		Serial.println(millis());
#endif
	}
}






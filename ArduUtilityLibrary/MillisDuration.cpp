#include "MillisDuration.h"
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




MillisDuration::MillisDuration(unsigned int duration)
{
	setDuration(duration);
}

MillisDuration::MillisDuration()
{	
}

void MillisDuration::reset() 
{
	unsigned long ulCurMillis=millis();

	_ulNextTriggerValue=ulCurMillis + _ulDuration;

	//In case we are close when millis() flips back to 0 (rollover) very soon, _ulNextTriggerValue will be SMALLER than ulCurMillis.
	if (_ulNextTriggerValue < ulCurMillis) { //It's "<" and not "<=". Else a duration of 0 could activate this handling also
		_bIsRolloverHandling=true;
	}

	/* 
	I think this is not needed as the only way to change _bIsRolloverHandling is by using setDuration()
	and this function resets the variable already.

	}  else {
	//no rollover effect, we are fine
	_bIsRolloverHandling=false;
	}
	*/
}

boolean MillisDuration::check() 
{
	if (_bIsRolloverHandling==false) {
		//normal handling, no rollover

		if (millis() >= _ulNextTriggerValue) {
			reset();
			return true;

		} else {
			return false;

		}

	} else {

		//The duration is defined as unsigned int, which means we can have a maximum duration of 65,535.
		//When ulCurrentMillis is smaller than this max value, we know that the rollover has happened.
		if (millis() < 65535) {
			_bIsRolloverHandling=false;

			return check();

		} else {
			//we are still waiting for the rollover and can't do anything
			return false;
		}

	}

}

//unsigned int to avoid setting a duration that would break our rollover handling 
void MillisDuration::setDuration(unsigned int duration) 
{
	_ulDuration=duration;
	_bIsRolloverHandling=false;

	reset();
}




// --- MillisDurationAdv ---

MillisDurationAdv::MillisDurationAdv(unsigned int duration)
	: MillisDuration(duration)
{
}

//a little extra: a default constructor when you want to use this class in other classes but need to set the duration during runtime
MillisDurationAdv::MillisDurationAdv() 
	:MillisDuration(250) //default value, will be changed later on (hopefully) anyway
{
}



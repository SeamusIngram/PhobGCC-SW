#ifndef READHARDWARE_H
#define READHARDWARE_H

//include this after the pins are defined in the Teensy board-specific headers

#include <ADC.h>
#include <VREF.h>
#include "../common/structsAndEnums.h"

ADC *adc = new ADC();

void setPinModes(){
	pinMode(_pinL,INPUT_PULLUP);
	pinMode(_pinR,INPUT_PULLUP);
#ifndef DPAD_BUTTON
	pinMode(_pinDr,INPUT_PULLUP);
	pinMode(_pinDu,INPUT_PULLUP);
	pinMode(_pinDl,INPUT_PULLUP);
	pinMode(_pinDd,INPUT_PULLUP);
#else
	pinMode(_pinD,INPUT_PULLUP);
#endif
	pinMode(_pinX,INPUT_PULLUP);
	pinMode(_pinY,INPUT_PULLUP);

	pinMode(_pinA,INPUT_PULLUP);
	pinMode(_pinB,INPUT_PULLUP);
	pinMode(_pinZ,INPUT_PULLUP);
	pinMode(_pinS,INPUT_PULLUP);
#ifdef ANALOG_TRIGGER_BUTTONS
	pinMode(_pinLS,INPUT_PULLUP);
	pinMode(_pinMS,INPUT_PULLUP);
#endif
#ifdef C_BUTTONS
	pinMode(_pinCr,INPUT_PULLUP);
	pinMode(_pinCu,INPUT_PULLUP);
	pinMode(_pinCl,INPUT_PULLUP);
	pinMode(_pinCd,INPUT_PULLUP);
#endif

#ifdef TEENSY4_0
#ifdef HALFDUPLEX
	pinMode(_pinRX,INPUT_PULLUP);
#else // HALFDUPLEX
	pinMode(9,    INPUT_PULLUP); //the normal RX pin doesn't work on teensy 4 with full duplex
#endif // HALFDUPLEX
	pinMode(_pinLED,   OUTPUT);
#endif // TEENSY4_0

#ifdef RUMBLE
	pinMode(_pinRumble, OUTPUT);
	pinMode(_pinBrake, OUTPUT);
#endif

	//Teensy 4 has some weird jump in the analog with default pin mode
#ifndef ANALOG_TRIGGER_BUTTONS
	pinMode(_pinLa,INPUT_DISABLE);
	pinMode(_pinRa,INPUT_DISABLE);
#endif
	pinMode(_pinAx,INPUT_DISABLE);
	pinMode(_pinAy,INPUT_DISABLE);
#ifndef C_BUTTONS
	pinMode(_pinCx,INPUT_DISABLE);
	pinMode(_pinCy,INPUT_DISABLE);
#endif
}

void readButtons(const Pins &pin, Buttons &hardware) {
	hardware.A = !digitalRead(pin.pinA);
	hardware.B = !digitalRead(pin.pinB);
	hardware.X = !digitalRead(pin.pinX);
	hardware.Y = !digitalRead(pin.pinY);
	hardware.L = !digitalRead(pin.pinL);
	hardware.R = !digitalRead(pin.pinR);
	hardware.Z = !digitalRead(pin.pinZ);
	hardware.S = !digitalRead(pin.pinS);
#ifndef DPAD_BUTTON
	hardware.Du = !digitalRead(pin.pinDu);
	hardware.Dd = !digitalRead(pin.pinDd);
	hardware.Dl = !digitalRead(pin.pinDl);
	hardware.Dr = !digitalRead(pin.pinDr);
#else
	hardware.Du = !digitalRead(pin.pinD) & !digitalRead(pin.pinCu);
	hardware.Dd = !digitalRead(pin.pinD) & !digitalRead(pin.pinCd);
	hardware.Dl = !digitalRead(pin.pinD) & !digitalRead(pin.pinCl);
	hardware.Dr = !digitalRead(pin.pinD) & !digitalRead(pin.pinCr);

#endif
}

void readADCScale(float &ADCScale, float ADCScaleFactor) {
#ifdef USEADCSCALE
	ADCScale = ADCScale*0.999 + ADCScaleFactor/adc->adc1->analogRead(ADC_INTERNAL_SOURCE::VREF_OUT);
#endif
	// otherwise _ADCScale is 1
}

//these are 12 bit but we right shift to get 8 bit
//implement a 3 unit deadzone
#ifndef ANALOG_TRIGGER_BUTTONS
int readLa(const Pins &pin, const int initial, const float scale) {
	float temp = (adc->adc0->analogRead(pin.pinLa)) / 16.0;
	if(temp < 3) {
		temp = 0.0f;
	}
	return (uint8_t) min(255, max(0, temp - initial) * scale);
}
int readRa(const Pins &pin, const int initial, const float scale) {
	float temp = (adc->adc0->analogRead(pin.pinRa)) / 16.0;
	if(temp < 3) {
		temp = 0.0f;
	}
	return (uint8_t) min(255, max(0, temp - initial) * scale);
}
#else
void readAnalogTriggerButtons(const Pins &pin, Buttons &hardware){
#ifdef MOD_SHIELD
	hardware.La = !digitalRead(pin.pinL)? 140: !digitalRead(pin.pinMS) & !digitalRead(pin.pinLS)? 94 : !digitalRead(pin.pinLS)? 49: 0;
#else
	hardware.La = !digitalRead(pin.pinL)? 140: !digitalRead(pin.pinMS)? 94 : !digitalRead(pin.pinLS)? 49: 0;
#endif
	hardware.Ra = !digitalRead(pin.pinR)? 140 : 0;
}
#endif
//these are native 12-bit
int readAx(const Pins &pin) {
	return adc->adc0->analogRead(pin.pinAx);
}
int readAy(const Pins &pin) {
	return adc->adc0->analogRead(pin.pinAy);
}
#ifndef C_BUTTONS
int readCx(const Pins &pin) {
	return adc->adc0->analogRead(pin.pinCx);
}
int readCy(const Pins &pin) {
	return adc->adc0->analogRead(pin.pinCy);
}
#else
void readCButtons(const Pins &pin, Buttons &hardware) {
	bool readDown = hardware.Ay <= 105 ;
	bool mod = !digitalRead(pin.pinMS);
	bool cUp = !digitalRead(pin.pinCu);
	bool cLeft = !digitalRead(pin.pinCl);
	bool cVertical = !digitalRead(pin.pinCu) != !digitalRead(pin.pinCd);
  bool cHorizontal = !digitalRead(pin.pinCl) != !digitalRead(pin.pinCr);
	if (!digitalRead(pin.pinD)){
		hardware.Cx = (uint8_t) 128;
		hardware.Cy = (uint8_t) 128;
	}
	else if (cVertical & cHorizontal){
		if (cLeft){
			hardware.Cx = (uint8_t) 86;
		}
		else{
			hardware.Cx = (uint8_t) 170;
		}
		if (cUp){
			hardware.Cy = (uint8_t) 196;
		}
		else{
			hardware.Cy = (uint8_t) 60;
		}
	} 
	else if (cHorizontal){
		#ifdef MOD_SHIELD
		if (mod){
			if (readDown)
				hardware.Cy = (uint8_t) 103;
			else
				hardware.Cy = (uint8_t) 153;
			if (cLeft){
				hardware.Cx = (uint8_t) 61;
			}
			else{
				hardware.Cx = (uint8_t) 195;
			}
		}
		else{
			hardware.Cy = (uint8_t) 128;
			if (cLeft){
				hardware.Cx = (uint8_t) 0;
			}
			else{
				hardware.Cx = (uint8_t) 255;
			}
		}
		#else
		hardware.Cy = (uint8_t) 128;
		if (cLeft){
			hardware.Cx = (uint8_t) 0;
		}
		else{
			hardware.Cx = (uint8_t) 255;
		}
		#endif
	}
	else if (cVertical){
		hardware.Cx = (uint8_t) 128;
		if (cUp){
			hardware.Cy = (uint8_t) 255;
		}
		else{
			hardware.Cy = (uint8_t) 0;
		}
	} 
  else{
		hardware.Cx = (uint8_t) 128;
		hardware.Cy = (uint8_t) 128;
	}
}
#endif //C_BUTTONS
#endif //READHARDWARE_H

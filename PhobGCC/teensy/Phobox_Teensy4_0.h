#ifndef BOARD_H
#define BOARD_H

#include <ADC.h>
#include <VREF.h>
#include "settings.h"

//Hardware specific code for PhobGCC board revision 1.2 with a Teensy 4.0
#define TEENSY4_0
#define C_BUTTONS
#define DPAD_BUTTON
#define RECTANGLE
#define ANALOG_TRIGGER_BUTTONS
//#define RUMBLE

//Hardware specific code for half duplex—using one pin for both TX and RX
#define HALFDUPLEX

//defining which pin is what on the teensy
// const int _pinLa = 16;
// const int _pinRa = 23;
// const int _pinCx = 22;
// const int _pinCy = 21;
// const int _pinDr = 9;
// const int _pinDu = 17;
// const int _pinDl = 9;
// const int _pinDd = 9;

const int _pinAx = 15;
const int _pinAy = 14;
const int _pinRX = 7;
const int _pinTX = 8;
const int _pinL = 6;
const int _pinR = 3;
const int _pinX = 4;
const int _pinY = 5;
const int _pinA = 20;
const int _pinB = 10;
const int _pinZ = 2;
const int _pinS = 16;
const int _pinLED = 13;
const int _pinRumble = 12;
const int _pinBrake = 11;
const int _pinInt = 7;

const int _pinCr = 18;
const int _pinCu = 19;
const int _pinCl = 21;
const int _pinCd = 23;
const int _pinD = 17;
const int _pinLS = 0;
const int _pinMS = 1;

//don't #define USEADCSCALE

void serialSetup() {
    Serial.begin(115200);
    Serial.println("This is the header for a Teensy 4.0 in a rectangle controller.");
}

void ADCSetup(ADC * adc,
              float &,/*ADCScale not used*/
              float & /*ADCScaleFactor not used*/) {
    adc->adc0->setAveraging(1);
    adc->adc0->setResolution(12);
    adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::HIGH_SPEED);
    adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);

}

//must include at the end
#include "readHardware.h"
#include "comms.h"
#endif // BOARD_H

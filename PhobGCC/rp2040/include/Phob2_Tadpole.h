#ifndef BOARD_H
#define BOARD_H

// #ifndef RUMBLE
// #define RUMBLE
// #endif //RUMBLE

#ifndef CLEANADC
#define CLEANADC
#endif //CLEANADC

#ifndef ANALOG_TRIGGER_BUTTONS
#define ANALOG_TRIGGER_BUTTONS
#endif

// #ifndef MOD_SHIELD
// #define MOD_SHIELD
// #endif

#ifndef C_BUTTONS
#define C_BUTTONS
#endif

#ifndef DPAD_BUTTON
#define DPAD_BUTTON
#endif

//defining which pin is what
//GPIO
//TODO: these are all temporary
const int _pinA =  21;
const int _pinB =  2;
const int _pinL =  10;
const int _pinR =  3;
const int _pinX =  4;
const int _pinY =  5;
const int _pinZ =  6;
const int _pinS =  1;
const int _pinRumble = -1;
const int _pinBrake = -1;
const int _pinTX  = 28;
//GPIO for rectangle controllers
const int _pinCr = 26;
const int _pinCu = 27;
const int _pinCl = 22;
const int _pinCd = 20;
const int _pinD = 0;
const int _pinLS = 7;
const int _pinMS = 8;
//GPIO SPI for ADCs
const int _pinSPIclk = 18;
const int _pinSPItx  = 19;
const int _pinSPIrx  = 16;
const int _pinAcs    = 17;
// const int _pinCcs = 1;
//a little resistor ladder DAC
const int _pinDac0 = -1;
const int _pinDac1 = -1;
const int _pinDac2 = -1;
const int _pinDac3 = -1;
//this is only for the pico itself, not necessarily the phob
const int _pinLED = 25;

//and two more
const int _pinSpare0 = -1;
const int _pinSpare1 = -1;
const int _pinSpare2 = -1;


const int _pinAx = -1;
const int _pinAy = -1;
const int _pinRX = -1;
const int _pinCx = -1;
const int _pinCy = -1;
const int _pinCcs = -1;
const int _pinDr = -1;
const int _pinDu = -1;
const int _pinDl = -1;
const int _pinDd = -1;

//two of the built-in ADCs:
const int _pinRa = -1; //GPIO number
const int _pinRadc = 0; //ADC number
const int _pinLa = -1; //GPIO number
const int _pinLadc = 1; //ADC number
#include "readHardware.h"
#include "debug.h"
#endif //BOARD_H

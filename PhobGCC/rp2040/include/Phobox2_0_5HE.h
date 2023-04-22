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

#ifndef MOD_SHIELD
#define MOD_SHIELD
#endif

#ifndef RP2040_BOX
#define RP2040_BOX
#endif

#ifndef C_BUTTONS
#define C_BUTTONS
#endif

#ifndef DPAD_BUTTON
#define DPAD_BUTTON
#endif

#ifndef HE_BUTTONS_LSTICK
#define HE_BUTTONS_LSTICK
#endif

#ifndef HE_BUTTON_R
#define HE_BUTTON_R
#endif
//defining which pin is what
//GPIO
//TODO: these are all temporary
const int _pinA =  10;
const int _pinB =  19;
const int _pinL =  18;
const int _pinX =  16;
const int _pinY =  17;
const int _pinZ =  15;
const int _pinS =  21;

const int _pinTX  = 28;
//GPIO for rectangle controllers
const int _pinCr = 8;
const int _pinCu = 9;
const int _pinCl = 11;
const int _pinCd = 12;
const int _pinD = 22;
const int _pinLS = 14;
const int _pinMS = 13;
//GPIO SPI for ADCs
const int _pinSPIclk = 6;
const int _pinSPItx  = 7;
const int _pinSPIrx  = 4;
const int _pinAcs    = 5;
const int _pinCcs    = 1;
//a little resistor ladder DAC
const int _pinDac0 = 0;
const int _pinDac1 = 1;
const int _pinDac2 = 2;
const int _pinDac3 = 3;
//this is only for the pico itself, not necessarily the phob
const int _pinLED = 25;

//and two more
const int _pinSpare0 = 26;
const int _pinSpare1 = 26;
const int _pinSpare2 = 27;

const int _pinRumble = -1;
const int _pinBrake = -1;
const int _pinR =  -1;

const int _pinAx = -1;
const int _pinAy = -1;
const int _pinRX = -1;
const int _pinCx = -1;
const int _pinCy = -1;
// const int _pinDr = -1;
// const int _pinDu = -1;
// const int _pinDl = -1;
// const int _pinDd = -1;
// const int _pinCcs = -1;
//two of the built-in ADCs:
// const int _pinRa = 26; //GPIO number
// const int _pinRadc = 0; //ADC number
// const int _pinLa = 27; //GPIO number
// const int _pinLadc = 1; //ADC number
#include "readHardware.h"

#endif //BOARD_H

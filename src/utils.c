#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

volatile unsigned char oldButtonState = 0x0;

//Get input from the 4 buttons
unsigned char getButtons() {
	return (unsigned char) ((PORTD & 0x000000e0) >> 4) | ((PORTF & 0x00000002) >> 1);
}

//Get input from the 4 button if they are pressed
unsigned char getButtonsPress() {
    //Set the output to 0
    unsigned char newButtonState = getButtons();
    if(newButtonState & 0x8 == oldButtonState & 0x8) {
        newButtonState &= 0x7;
    }
    if(newButtonState & 0x4 == oldButtonState & 0x4) {
        newButtonState &= 0xb;
    }
    if(newButtonState & 0x2 == oldButtonState & 0x2) {
        newButtonState &= 0xd;
    }
    if(newButtonState & 0x1 == oldButtonState & 0x1) {
        newButtonState &= 0xe;
    }

    PORTE = newButtonState | (oldButtonState << 4);

    //Save the output to the oldState for next time
    oldButtonState = newButtonState;

    delay(50);

    return newButtonState;
}

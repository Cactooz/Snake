#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

//Get input from the 4 buttons
unsigned char getButtons() {
	return (unsigned char) ((PORTD & 0x000000e0) >> 4) | ((PORTF & 0x00000002) >> 1);
}

//Get input from the 4 switches
unsigned char getSwitches(void) {
	return ((PORTD & 0x00000f00) >> 8);
}

#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

//Get input from the 4 buttons
int getButtons() {
	return ((PORTD & 0x000000f0) >> 4);
}

#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

//Function for turning a single pixel on or off
void updatePixel(unsigned char x, unsigned char y, unsigned char bool) {
	//Check if the pixels are inside of the screen
	if(x < 128 && y < 32 && bool <= 1) {
		//Get the position in the array that should be changed
		short pos = ((y/8)*128) + x;

		//Turn on pixel if bool = 1
		if(bool == 1) {
			displayBuffer[pos] = (displayBuffer[pos] | (0x1 << (y%8)));
		}
		//Turn off pixel if bool = 0
		else if(bool == 0) {
			displayBuffer[pos] = (displayBuffer[pos] & ~(0x1 << (y%8)));
		}
	}
}

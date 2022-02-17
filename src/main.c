#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

//Function to initialize everything
void init() {
	//Set button 1 as input
	TRISFSET = 0x00000002;

	//Set button 2-4 as inputs
	TRISDSET = 0x00000fe0;
}

int main() {
	//Initialize everything
	init();
	return 0;
}

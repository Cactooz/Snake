#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

//Function to initialize everything
void init() {
	//Set button 1 as input
	TRISFSET = 0x00000002;

	//Set button 2-4 as inputs
	TRISDSET = 0x00000fe0;

	//Setup display
	OledHostInit();
	OledDspInit();
}

//Called on interrupt
void user_isr() {
	return;
}

//Main function for the whole game
int main() {
	//Initialize everything
	init();

	//Define the gameStates
	enum gameState{menu, game, gameOver, highscore};
	//Set the gameState to menu
	enum gameState gameState = menu;

	//Used for clearing display
	int column;
	int row;

	//Run the game
	while(1) {
		switch(gameState) {
			case menu:
				switch(runMenu())
				{
					case 1:
						//Clears the screen
    					for (column = 0; column < 128; column++)
        					for(row = 0; row < 32; row++)
            					updatePixel(column, row, 0);

						gameState = game;
						break;
					
					case 2:
						//Clears the screen
    					for (column = 0; column < 128; column++)
        					for(row = 0; row < 32; row++)
            					updatePixel(column, row, 0);
						gameState = highscore;
						break;
				}
				break;
			case game:
				//Code for the game
				//Move the snake
				printWord("GAME", 4, 50, 12);
				OledUpdate();
				break;
			case gameOver:
				//Code for game over menu

				break;
			case highscore:
				//Code for highscore menu
				printWord("HIGHSCORE", 9, 50, 12);
				OledUpdate();
				break;
			default:
				break;
		}
		
		//Delay 500ms
		delay(500);
	}

	return 0;
}

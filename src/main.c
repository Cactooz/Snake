#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

//Declare stdout as NULL
void *stdout = (void *) 0;

//Function to initialize everything
void init() {
	//Set button 1 as input
	TRISFSET = 0x00000002;

	//Set button 2-4 as inputs
	TRISDSET = 0x00000fe0;

	OledHostInit();
	OledDspInit();
	initGame();
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
	enum gameState gameState = game;

	//Run the game
	while(1) {
		switch(gameState) {
			case menu:
				//Code for main menu
				printWord("MENU", 4, 50, 15);
				OledUpdate();
				
				break;
			case game:
				//Code for the game
				//Run the game, if we get 1 back move to gameOver
				if(runGame())
					gameState = gameOver;

				//Draw the game
				drawGame();
				OledUpdate();
				break;
			case gameOver:
				//Code for game over menu

				break;
			case highscore:
				//Code for highscore menu

				break;
			default:
				break;
		}
		
		//Delay 500ms
		delay(500);
	}

	return 0;
}

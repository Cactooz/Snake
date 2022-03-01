#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

//Declare stdout as NULL
void *stdout = (void *) 0;

//Function to initialize everything
void init() {
	//Set button 1 as input
	TRISFSET = 0x00000002;

	//Set button 2-4 as inputs and the switches
	TRISDSET = 0x00000fe0;

	//Setup for lamps
	TRISECLR = 0x000000ff;
	PORTECLR = 0x000000ff;

	PORTE = 0;

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

	//Run the game
	while(1) {
		switch(gameState) {
			case menu:
				clearDisplay();
				switch(runMenu())
				{
					case 1: //Easy
						//Clears the screen
    					clearDisplay();

						//Change the gameState to game and init the game
						speed = 10;
						gameState = game;
						initGame();
						break;
					
					case 2: //Hard
						//Clears the screen
    					clearDisplay();
						speed = 3;
						gameState = game;
						initGame();
						break;

					case 3: //Leaderboard
						clearDisplay();
						gameState = highscore;
				}
				break;
			case game:
				//Code for the game
				//Run the game, if we get 0 back move to gameOver
				if(!runGame())
					gameState = gameOver;
				else	
					//Draw the game and update the screen
					drawGame();

				OledUpdate();
				break;
			case gameOver:
				//Code for game over menu
				clearDisplay();
				if(addHighscore(length-2))
					gameState = menu;
				OledUpdate();
				break;
			case highscore:
				//Code for highscore menu
				if(displayHighscore())
				{
					clearDisplay();
					gameState = menu;
				}
				OledUpdate();

				break;
			default:
				break;
		}
		//Delay 33ms
		delay(33);
	}

	return 0;
}

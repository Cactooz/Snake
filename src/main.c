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
				//Code for main menu
				
				break;
			case game:
				//Code for the game
				//Move the snake
				moveSnake();

				//Draw the snake
				printSnake();

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
	}

	return 0;
}

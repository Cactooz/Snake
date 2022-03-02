#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

int timecount = 0;
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

	//Set the seed for the random
	srand(getSwitches());

	//Setup display
	OledHostInit();
	OledDspInit();

	//Initialize Timer2
  	T2CONSET = 0x70; //0111 0000, Sets prescale to 1:256
  	IFSCLR(0) = 0x100;//0001 0000 0000
  	PR2 = 31250;
  	TMR2 = 0;
  	T2CONSET = 0x08000; // 1000 0000 0000 0000, Start timer

  	IPCSET(2) = 0x1f; //0001 1111 - Bit 4:2 Priority, Bit 1:0 Subpriority.
  	IECSET(0) = 0x100; // 0001 0000 0000 - Bit 8 enable interupts from Timer2

	enable_interrupts();

	IPCSET(2) = 0x1f; 
  	IECSET(0) = 0x100;
}

//Called on interrupt
void user_isr() {
	OledUpdate();
	IFSCLR(0) = 0x100;//0001 0000 0000
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
					case 1: //Play
						//Clears the screen
						clearDisplay();

						//Change the gameState to game and init the game
						gameState = game;
						initGame();
						break;
					
					case 2: //Leaderboard
						//Clears the screen
						clearDisplay();
						gameState = highscore;
						break;
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
				break;
			case gameOver:
				//Code for game over menu
				clearDisplay();
				if(addHighscore(length-START_LENGTH))
					gameState = menu;
				break;
			case highscore:
				//Code for highscore menu
				if(displayHighscore())
				{
					clearDisplay();
					gameState = menu;
				}
				break;
			default:
				break;
		}
		//Delay 33ms
		delay(33);
	}

	return 0;
}

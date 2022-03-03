#include <stdint.h>
#include <pic32mx.h>
#include <stdio.h>
#include "game.h"

int runs = 1;

void chooseAiMode()
{
	int row;
	int column;
	//Turn off every pixel
	clearDisplay();
	int select = 1;
	unsigned char loop = 1;
	while (loop)
	{
		switch (select)
		{
		case 1:
			printCharacterAZ(91, 50, 8, 1); //Marker
			printWord("AI", 2, 60, 8);
			printWord("IRL", 3, 55, 16);
			if(getButtonsPress() & 8) //Press BTN4 to scroll
			{
				printCharacterAZ(91, 50, 8, 0); //Remove Marker
				delay(50);
				select = 2; //Switch to case 2
			}
			if (getButtonsPress() & 4)
			{
				ai = 1; //Set player mode to 1
				chooseDifficulty();
				loop = 0; //Stop the loop
			}
			break;
		case 2:
			printCharacterAZ(91, 45, 16, 1); //Marker
			printWord("AI", 2, 60, 8);
			printWord("IRL", 3, 55, 16);
			if(getButtonsPress() & 8) //Press BTN4 to scroll
			{
				printCharacterAZ(91, 45, 16, 0); //Remove Marker
				delay(50);
				select = 1; //Switch to case 1
			}
			if (getButtonsPress() & 4)
			{
				ai = 0; //Set player mode to 2
				chooseDifficulty();
				loop = 0; //Stop the loop
			}
			break;
		}
	}
}

void choosePlayerMode()
{
	int row;
	int column;
	//Turn off every pixel
	clearDisplay();
	int select = 1;
	unsigned char loop = 1;
	while (loop)
	{
		switch (select)
		{
		case 1:
			printCharacterAZ(91, 25, 8, 1); //Marker
			printWord("ONE PLAYER", 10, 35, 8);
			printWord("TWO PLAYER", 10, 35, 16);
			if(getButtonsPress() & 8) //Press BTN4 to scroll
			{
				printCharacterAZ(91, 25, 8, 0); //Remove Marker
				delay(50);
				select = 2; //Switch to case 2
			}
			if (getButtonsPress() & 4)
			{
				player = 1; //Set player mode to 1
				ai = 0;
				chooseDifficulty();
				loop = 0; //Stop the loop
			}
			break;
		case 2:
			printCharacterAZ(91, 25, 16, 1); //Marker
			printWord("ONE PLAYER", 10, 35, 8);
			printWord("TWO PLAYER", 10, 35, 16);
			if(getButtonsPress() & 8) //Press BTN4 to scroll
			{
				printCharacterAZ(91, 25, 16, 0); //Remove Marker
				delay(50);
				select = 1; //Switch to case 1
			}
			if (getButtonsPress() & 4)
			{
				player = 2; //Set player mode to 2
				chooseAiMode();
				loop = 0; //Stop the loop
			}
			break;
		}
	}
}

unsigned char runMenu()
{
	int column;
	int row;

	//Loading
	if (runs)
	{
		//Light up each column separately
		for (column = 0; column < 128; column++)
		{
			for(row = 0; row < 32; row++)
				updatePixel(column, row, 1);

			delay(5);
		}
		//Turn off every pixel
		clearDisplay(); 

		//Display text
		printWord("SNAKE", 5, 50, 0);
		printWord("BY", 2, 58, 10);
		if(getSwitches() == 5) //Easter egg 
			printWord("POTNUS AND HUGO", 15, 20, 20);
		else
			printWord("PONTUS AND HUGO", 15, 20, 20);

		delay(2000);

		//Turn off every pixel
		clearDisplay();

		runs = 0; //Makes sure the loadingscreen only runs once :P
	}
	
	

	int select = 1;
	while (1)
	{
		switch (select)
		{
		case 1:
			printCharacterAZ(91, 40, 8, 1); //Marker
			printWord("PLAY", 4, 50, 8);
			printWord("LEADERBOARD", 11, 30, 16);
			if(getButtonsPress() & 8) //Press BTN4 to scroll
			{
				printCharacterAZ(91, 40, 8, 0); //Remove Marker
				delay(50);
				select = 2; //Switch to case 2
			}
			if (getButtonsPress() & 4) //Press BTN3 to select
			{
					delay(50);
					choosePlayerMode();
					return 1; //Return 1 to start game
			}
			break;
		case 2:
			printCharacterAZ(91, 20, 16, 1); //Marker
			printWord("PLAY", 4, 50, 8);
			printWord("LEADERBOARD", 11, 30, 16);
			if(getButtonsPress() & 8) //Press BTN4 to scroll
			{
				printCharacterAZ(91, 20, 16, 0); //Remove Marker
				delay(50);
				select = 1; //Switch to case 1
			}
			if (getButtonsPress() & 4) //Press BTN3 to select
				return 2; //Return 2 to open leaderboard
			break;            
		}
	}
}

void chooseDifficulty()
{
	int row;
	int column;
	//Turn off every pixel
	clearDisplay();
	int select = 1;
	unsigned char loop = 1;
	while (loop)
	{
		switch (select)
		{
		case 1:
			printCharacterAZ(91, 40, 8, 1); //Marker
			printWord("EASY", 4, 50, 8);
			printWord("HARD", 4, 50, 16);
			if(getButtonsPress() & 8) //Press BTN4 to scroll
			{
				printCharacterAZ(91, 40, 8, 0); //Remove Marker
				delay(50);
				select = 2; //Switch to case 2
			}
			if (getButtonsPress() & 4) //Press BTN3 to select
			{
				hardMode = 0;
				loop = 0; //Stop loop
			}
			
			break;
		
		case 2:
			printCharacterAZ(91, 40, 16, 1); //Marker
			printWord("EASY", 4, 50, 8);
			printWord("HARD", 4, 50, 16);
			if(getButtonsPress() & 8) //Press BTN4 to scroll
			{
				printCharacterAZ(91, 40, 16, 0); //Remove Marker
				delay(50);
				select = 1;
			}
			if (getButtonsPress() & 4) //Press BTN3 to select
			{
				hardMode = 1;
				loop = 0; //Stop loop
			}
			break;
		}
	}
}



//TWO PLAYER -> AI/IRL -> Difficulty, AI TRUE/FALSE
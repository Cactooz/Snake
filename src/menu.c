#include <stdint.h>
#include <pic32mx.h>
#include <stdio.h>
#include "game.h"

int runs = 1;

unsigned char runMenu()
{
	int column;
	int row;

	//Loading
	if (runs)
	{
		for (column = 0; column < 128; column++)
		{
			for(row = 0; row < 32; row++)
				updatePixel(column, row, 1);

			delay(5);
		}
		clearDisplay();

		//Display text
		printWord("SNAKE", 5, 50, 0);
		printWord("BY", 2, 58, 10);
		printWord("PONTUS", 6, 20, 20);
		printWord("AND", 3, 60, 20);
		printWord("HUGO", 4, 83, 20);

		delay(2000);

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
				select = 2;
			}
			if (getButtonsPress() & 4)
			{
					delay(50);
					chooseDifficulty();
					return 1;
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
				select = 1;
			}
			if (getButtonsPress() & 4)
				return 2;
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
				select = 2;
			}
			if (getButtonsPress() & 4)
			{
				speed = 10;
				loop = 0;
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
			if (getButtonsPress() & 4)
			{
				speed = 3;
				loop = 0;
			}
			break;
		}

	}

}
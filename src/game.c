#include <stdint.h> 
#include <stdlib.h>
#include <pic32mx.h>
#include "game.h"

unsigned short snakePos[10][42] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

//The moving direction of the snake
//0=left, 1=up, 2=down, 3=right
unsigned char direction = 0;

//The length of the snake
unsigned short length = 2;

//The position of the snake
unsigned char currentX;
unsigned char currentY;

//Set the snake heads position
void placeHead(unsigned char x, unsigned char y) {
	//Set the position of the snake head
	snakePos[y][x] = length;

	//Set the current position for the snake head
	currentX = x;
	currentY = y;
}

//Function to intilize the position of the snake
void gameInit() {
	//Get a random start position and moving direction
	unsigned char startX = rand() % 21 + 10;
	unsigned char startY = rand() % 5 + 3;
	direction = rand() % 4;

	//Put the starting position of the head
	placeHead(startX, startY);
}

//Change the snakeDirection depending on the button presses
void snakeDirection() {
	//Get the current pressed buttons
	unsigned char buttonState = getButtons();

	//If button 4 is pressed go left
	if(buttonState & 8) {
		direction = 0;
	}
	//If button 3 is pressed go up
	else if(buttonState & 4) {
		direction = 1;
	}
	//If button 2 is pressed go down
	else if(buttonState & 2) {
		direction = 2;
	}
	//If button 1 is pressed go right
	else if(buttonState & 1) {
		direction = 3;
	}
}

void moveSnake() {
	snakeDirection();
	
	//Loop through all the snakePositions
	for(unsigned char i = 0; i < 10; i++) {
		for(unsigned char j = 0; j < 42; j++) {
			//Remove one from each used snake position
			if(snakePos[i][j] != 0) {
				snakePos[i][j]--;
			}
		}
	}

	//Set the head to the new position
	if(direction == 0) {
		placeHead(currentX-1, currentY);
	}
	else if(direction == 1) {
		placeHead(currentX, currentY-1);
	}
	else if(direction == 2) {
		placeHead(currentX, currentY+1);		
	}
	else if(direction == 3) {
		placeHead(currentX+1, currentY);		
	}
}

//Print a 3x3 block for the snake
void printBlock(unsigned char x, unsigned char y, unsigned char bool) {
	//Multiply in input coords by 3
	x = x*3;
	y = y*3;

	//Update the pixels
	updatePixel(x, y, bool);
	updatePixel(x, y+1, bool);
	updatePixel(x, y+2, bool);
	updatePixel(x+1, y, bool);
	updatePixel(x+1, y+1, bool);
	updatePixel(x+1, y+2, bool);
	updatePixel(x+2, y, bool);
	updatePixel(x+2, y+1, bool);
	updatePixel(x+2, y+2, bool);
}

//Print the snake on the screen
void printSnake() {
	//Loop through the full snakePos array
	for(unsigned char row = 0; row < 10; row++) {
		for(unsigned char column = 0; column < 42; column++) {
			//Turn on the pixel if there is a value in the array, else turn it off
			if(snakePos[row][column] != 0)
				printBlock(row, column, 1);
			else
				printBlock(row, column, 0);
		}
	}
}

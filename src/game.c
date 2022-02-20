#include <stdint.h> 
#include <stdlib.h>
#include <pic32mx.h>
#include "game.h"

//Array for all the posible snake positions and storing the data of the tail
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

//Keeping track of the apple count
unsigned char appleCount = 0;

//The position of the apple
unsigned char appleX;
unsigned char appleY;

//Keep track if the snake is alive or not, 0 = alive, 1 = dead
unsigned char alive = 0;

//Set the snake heads position
void placeHead(unsigned char x, unsigned char y) {
	//Set the position of the snake head
	snakePos[y][x] = length;

	//Set the current position for the snake head
	currentX = x;
	currentY = y;
}

//Function to intilize the position of the snake
void initGame() {
	//Get a random start position and moving direction
	unsigned char startX = rand() % 21 + 10;
	unsigned char startY = rand() % 5 + 3;
	direction = rand() % 4;

	//Put the starting position of the head
	placeHead(startX, startY);
}

//Place an apple on a random position on the screen
void placeApple() {
	unsigned char x = rand() % 42;
	unsigned char y = rand() % 10;

	//Place an apple if the snake isn't there
	if(!snakePos[y][x]) {
		appleX = x;
		appleY = y;
	}
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
	unsigned char i;
	unsigned char j;
	//Loop through all the snakePositions
	for(i = 0; i < 10; i++) {
		for(j = 0; j < 42; j++) {
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

//Main function for running the game, returns 1 when game over
unsigned char runGame() {
	//Place an apple if there are non on the screen
	if(!appleCount)
		placeApple();

	//Check if the snakeDirection have changed
	snakeDirection();

	//Move the snake
	moveSnake();

	//Return the current state of the snake
	return alive;
}


//Draw a 3x3 block for the snake
void drawBlock(unsigned char x, unsigned char y, unsigned char state) {
	//Multiply in input coords by 3
	x = x*3;
	y = y*3;

	//Update the pixels
	updatePixel(x, y, state);
	updatePixel(x, y+1, state);
	updatePixel(x, y+2, state);
	updatePixel(x+1, y, state);
	updatePixel(x+1, y+1, state);
	updatePixel(x+1, y+2, state);
	updatePixel(x+2, y, state);
	updatePixel(x+2, y+1, state);
	updatePixel(x+2, y+2, state);
}

//Draw the snake on the screen
void drawSnake() {
	unsigned char row;
	unsigned char column;
	//Loop through the full snakePos array
	for(row = 0; row < 10; row++) {
		for(column = 0; column < 42; column++) {
			//Turn on the pixel if there is a value in the array, else turn it off
			if(snakePos[row][column] != 0)
				drawBlock(row, column, 1);
			else
				drawBlock(row, column, 0);
		}
	}
}

//Main function for drawing everything in the game
void drawGame() {
	//Draw the snake
	drawSnake();
}

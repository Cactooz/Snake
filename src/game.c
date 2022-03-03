#include <stdint.h> 
#include <stdlib.h>
#include <pic32mx.h>
#include "game.h"

//Define constants
//The width of the snakePos array
#define WIDTH 126
//The height of the snakePos array
#define HEIGHT 30

//Array for all the posible snake positions and storing the data of the tail
unsigned short snakePos[HEIGHT][WIDTH];

//The moving direction of the snake
//0=left, 1=up, 2=down, 3=right
unsigned char direction;

//The length of the snake
unsigned short length;

//The position of the snake
unsigned char currentX;
unsigned char currentY;

//Keeping track of the apple count
unsigned char appleCount;

//The position of the apple
unsigned char appleX;
unsigned char appleY;

//Keep track if the snake is alive or not, 1 = alive, 0 = dead
unsigned char alive;

//AI variables
//Keeping track of AI moving direction
unsigned char aiDirection;
//The position of the AI
unsigned char aiX;
unsigned char aiY;
//The length of the AI
unsigned short aiLength;

//Keeping track of the movement timings
unsigned char moveCounter;

//Keeping track if the game is in hardMode
unsigned char hardMode;

//Keeping track of the amount of players
unsigned char player;

//Set the snake heads position
void placeHead(unsigned char x, unsigned char y) {
	//Set the position of the snake head
	unsigned char i;
	unsigned char j;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			snakePos[y+i][x+j] = length;
		}
	}

	//Set the current position for the snake head
	currentX = x;
	currentY = y;
}

//Place the AI head in the snakePos array
void placeAiHead(unsigned char x, unsigned char y) {
	//Set the position of the snake head
	snakePos[y][x] = aiLength;

	//Set the current position for the snake head
	aiX = x;
	aiY = y;
}

void drawGameBorder() {
	unsigned char i;
	//Turn on the top and bottom row
	for(i = 0; i < 128; i++) {
		updatePixel(i,0, 1);
		updatePixel(i,31, 1);
	}

	//Turn on the most right and most left row of pixels
	displayBuffer[0] = 255;
	displayBuffer[128] = 255;
	displayBuffer[256] = 255;
	displayBuffer[384] = 255;
	displayBuffer[127] = 255;
	displayBuffer[255] = 255;
	displayBuffer[383] = 255;
	displayBuffer[511] = 255;
}

//Function to intilize the position of the snake
void initGame() {
	//Clear the snakePos array
	unsigned char y;
	unsigned char x;
	//Loop through the full snakePos array
	for(y = 0; y < HEIGHT; y++) {
		for(x = 0; x < WIDTH; x++) {
			//Clear the pos value
			snakePos[y][x] = 0;
		}
	}

	//Turn on a 1 pixel border around the game area
	drawGameBorder();

	//Reset the data variables
	appleCount = 0;
	length = START_LENGTH;
	alive = 1;
	moveCounter = 100;

	//Get a random start position and moving direction
	unsigned char startX = rand() % (WIDTH/2) + (WIDTH/4);
	unsigned char startY = rand() % (HEIGHT/2) + (HEIGHT/4);
	direction = rand() % 4;
	
	//Only add the AI in one player mode and hard mode
	if(player == 1 && hardMode) {
		//Set AI start position, moving direction and length
		unsigned char startAiX = rand() % WIDTH;
		unsigned char startAiY = rand() % HEIGHT;
		aiDirection = rand() % 4;
		aiLength = 5;
		
		//Put the starting position of the AI
		placeAiHead(startAiX, startAiY);
	}

	//Put the starting position of the head
	placeHead(startX, startY);
}

//Place an apple on a random position on the screen
void placeApple() {
	unsigned char x = rand() % (WIDTH-2) + 1;
	unsigned char y = rand() % (HEIGHT-2) + 1;

	//Place an apple if the snake isn't there
	if(!snakePos[y][x]) {
		appleX = x;
		appleY = y;

		appleCount++;
	}
}

//Check if an apple gets eaten
void appleEat() {
	if(currentX == appleX && currentY == appleY) {
		//Remove the apple
		appleCount--;
		//Increase the length of the snake
		length++;
	}
}

void aiAppleEat() {
	if(aiX == appleX && aiY == appleY) {
		//Remove the apple
		appleCount--;
		//Increase the length of the snake
		aiLength++;
	}
}

//Change the snakeDirection depending on the button presses
void snakeDirection() {
	//Get the current pressed buttons
	unsigned char buttonState = getButtons();

	//If button 4 is pressed go left
	if(buttonState & 8 && direction != 3) {
		direction = 0;
	}
	//If button 3 is pressed go up
	else if(buttonState & 4 && direction != 2) {
		direction = 1;
	}
	//If button 2 is pressed go down
	else if(buttonState & 2 && direction != 1) {
		direction = 2;
	}
	//If button 1 is pressed go right
	else if(buttonState & 1 && direction != 0) {
		direction = 3;
	}
}

//Function for moving the snake around on the screen
void moveSnake() {	
	unsigned char i;
	unsigned char j;
	//Loop through all the snakePositions
	for(i = 0; i < HEIGHT; i++) {
		for(j = 0; j < WIDTH; j++) {
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

//Move the AI on the screen
void moveAI() {
	if(aiX < appleX && aiX >= 0) {
		placeAiHead(aiX+1, aiY);
	}
	else if(aiX > appleX && aiX <= WIDTH) {
		placeAiHead(aiX-1, aiY);
	}
	else if(aiY < appleY && aiY >= 0) {
		placeAiHead(aiX, aiY+1);
	}
	else if(aiY > appleY && aiY <= HEIGHT) {
		placeAiHead(aiX, aiY-1);
	}
}

//Check if the snake is outside of the screen or if the head hits the tail and kill it
void deathCheck() {
	if(currentX < 0 || currentX + 3 > WIDTH || currentY < 0 || currentY + 3 > HEIGHT
		|| (direction == 0 && snakePos[currentY + 1][currentX - 1])
		|| (direction == 1 && snakePos[currentY - 1][currentX + 1])
		|| (direction == 2 && snakePos[currentY + 3][currentX + 1])
		|| (direction == 3 && snakePos[currentY + 1][currentX + 3]))
		alive = 0;
}

//Main function for running the game, returns 1 when game over
unsigned char runGame() {
	//Place an apple if there are non on the screen
	if(!appleCount)
		placeApple();

	//Check if the snakeDirection have changed
	snakeDirection();

	//Only update every once in a while
	if(moveCounter > 2) {
		//Check if the snake died
		deathCheck();
		//Move the snake
		if(alive) {
			//Move the snake
			moveSnake();
			//Check if the snake ate the apple
			appleEat();
			//Display the points on the lamps
			PORTE=(length-START_LENGTH);

			//Only update the AI in one player mode and hard mode
			if(player == 1 && hardMode) {
				//Move the AI
				moveAI();
				//Check if the AI ate the apple
				aiAppleEat();
			}
		}
		//Reset the counter
		moveCounter = 0;
	}
	else
		moveCounter++;
	
	//Return the current state of the snake
	return alive;
}

//Draw the snake on the screen
void drawSnake() {
	unsigned char y;
	unsigned char x;
	//Loop through the full snakePos array
	for(y = 0; y < HEIGHT; y++) {
		for(x = 0; x < WIDTH; x++) {
			//Turn on the pixel if there is a value in the array, else turn it off
			if(snakePos[y][x] != 0)
				updatePixel(x+1,y+1, 1);
			else
				updatePixel(x+1,y+1, 0);
		}
	}
}

void drawApple() {
	//Add the apple to the screen buffer
	updatePixel(appleX + 1, appleY + 1, 1);
}

//Main function for drawing everything in the game
void drawGame() {
	//Draw the snake
	drawSnake();
	//Draw the apple
	drawApple();
}

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
unsigned char newDirection;

//The length of the snake
unsigned short length;

//The position of the snake
unsigned char currentX;
unsigned char currentY;

//The moving direction of the 2nd snake
//0=left, 1=up, 2=down, 3=right
unsigned char direction2;
unsigned char newDirection2;

//The length of the 2nd snake
unsigned short length2;

//The position of the 2nd snake
unsigned char currentX2;
unsigned char currentY2;

//Keeping track of the apple count
unsigned char appleCount;

//The position of the apple
unsigned char appleX;
unsigned char appleY;

//Keep track if the snake is alive or not, 1 = alive, 0 = dead
unsigned char alive;
//Keep track if the 2nd snake is alive or not, 1 = alive, 0 = dead
unsigned char alive2;

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
//Keeping track of the AI movement timings
unsigned char aiMoveCounter;
//Keeping track of the steps for the 1st snake
unsigned char stepCounter;
//Keeping track of the steps for the 2nd snake
unsigned char stepCounter2;

//Keeping track if the game is in hardMode
unsigned char hardMode;

//Keeping track of the amount of players
unsigned char player;

//Keeping track if the player should play against an AI
unsigned char ai;

//Keeping track of who won in a 2 player game
unsigned char winner;

//Obstacle 1 variables
//Keeping track of the obstacle1 moving direction
unsigned char obstacle1Direction;
//The X position of the obstacle1
unsigned char obstacle1X;

//Obstacle 2 variables
//Keeping track of the obstacle2 moving direction
unsigned char obstacle2Direction;
//The Y position of the obstacle2
unsigned char obstacle2Y;


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

//Set the 2nd snake heads position
void placeHead2(unsigned char x, unsigned char y) {
	//Set the position of the snake head
	unsigned char i;
	unsigned char j;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			snakePos[y+i][x+j] = length2;
		}
	}

	//Set the current position for the snake head
	currentX2 = x;
	currentY2 = y;
}

//Place the AI head in the snakePos array
void placeAiHead(unsigned char x, unsigned char y) {
	//Set the position of the snake head
	snakePos[y][x] = aiLength;

	//Set the current position for the snake head
	aiX = x;
	aiY = y;
}

//Place the obstacle1 "head"
void placeObstacle1(unsigned char x) {
	//Set the position of the obstacle
	snakePos[15][x] = 4;
	snakePos[16][x] = 4;

	//Set the current position for the obstacle
	obstacle1X = x;
}

//Place the obstacle2 "head"
void placeObstacle2(unsigned char y) {
	//Set the position of the obstacle
	snakePos[y][63] = 4;
	snakePos[y][64] = 4;

	//Set the current position for the obstacle
	obstacle2Y = y;
}

//Draw a one pixel border around the whole game area
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
	alive2 = 1;
	moveCounter = 100;

	//Get a random start position and moving direction
	unsigned char startX = rand() % (WIDTH/2) + (WIDTH/4);
	unsigned char startY = rand() % (HEIGHT/2) + (HEIGHT/4);
	direction = rand() % 4;
	newDirection = direction;
	
	if(hardMode) {
		//Only add the obstacle in hardmode
		//Setup obstacle1
		placeObstacle1(10);
		obstacle1Direction = 3;
		//Setup obstacle2
		placeObstacle2(3);
		obstacle2Direction = 2;

		if(player == 1) {

		}
	}

	if(ai) {
		//Set AI start position, moving direction and length
		unsigned char startAiX = rand() % WIDTH;
		unsigned char startAiY = rand() % HEIGHT;
		aiDirection = rand() % 4;
		aiLength = 5;
		aiMoveCounter = 100;
		
		//Put the starting position of the AI
		placeAiHead(startAiX, startAiY);
	}

	//Init snake 2 if two player mode is chosen
	if(player == 2 && !ai) {
		//Reset the data variables for the 2nd snake
		length2 = START_LENGTH;

		//Get a random start position and moving direction
		unsigned char startX2 = rand() % (WIDTH/2) + (WIDTH/4);
		unsigned char startY2 = rand() % (HEIGHT/2) + (HEIGHT/4);
		direction2 = rand() % 4;
		newDirection2 = direction2;

		//Put the starting position of the 2nd snakes head
		placeHead2(startX2, startY2);
	}

	//Put the starting position of the head
	placeHead(startX, startY);
}

//Place an apple on a random position on the screen
void placeApple() {
	unsigned char x = rand() % (WIDTH-6) + 3;
	unsigned char y = rand() % (HEIGHT-6) + 3;

	//Place an apple if the snake isn't there
	if(!snakePos[y][x]) {
		appleX = x;
		appleY = y;

		appleCount++;
	}
}

//Check if an apple gets eaten
void eatApple() {
	unsigned char i;
	unsigned char j;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(currentX+i == appleX && currentY+j == appleY && appleCount) {
				//Remove the apple
				appleCount--;
				//Increase the length of the snake
				length++;
			}
		}
	}
}

//Check if an apple gets eaten by the 2nd snake
void eatApple2() {
	unsigned char i;
	unsigned char j;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			if(currentX2+i == appleX && currentY2+j == appleY && appleCount) {
				//Remove the apple
				appleCount--;
				//Increase the length of the 2nd snake
				length2++;
			}
		}
	}
}

//Check if the  AI ate an apple
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
		newDirection = 0;
	}
	//If button 3 is pressed go up
	else if(buttonState & 4 && direction != 2) {
		newDirection = 1;
	}
	//If button 2 is pressed go down
	else if(buttonState & 2 && direction != 1) {
		newDirection = 2;
	}
	//If button 1 is pressed go right
	else if(buttonState & 1 && direction != 0) {
		newDirection = 3;
	}

	//Change the direction after 6 updates, while keeping the input responsivity
	if(stepCounter > 6) {
		direction = newDirection;
		stepCounter = 0;
	}
	else
		stepCounter++;
}


//Change the snakeDirection for the 2nd snake depending on the switches
void snakeDirection2() {
	//Get the current pressed buttons
	unsigned char switchState = getSwitches();

	//If button 4 is pressed go left
	if(switchState & 8 && direction2 != 3) {
		newDirection2 = 0;
	}
	//If button 3 is pressed go up
	else if(switchState & 4 && direction2 != 2) {
		newDirection2 = 1;
	}
	//If button 2 is pressed go down
	else if(switchState & 2 && direction2 != 1) {
		newDirection2 = 2;
	}
	//If button 1 is pressed go right
	else if(switchState & 1 && direction2 != 0) {
		newDirection2 = 3;
	}

	//Change the direction after 6 updates, while keeping the input responsivity
	if(stepCounter2 > 6) {
		direction2 = newDirection2;
		stepCounter2 = 0;
	}
	else
		stepCounter2++;
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

//Function for moving the 2nd snake around on the screen
void moveSnake2() {	
	//Set the head to the new position
	if(direction2 == 0) {
		placeHead2(currentX2-1, currentY2);
	}
	else if(direction2 == 1) {
		placeHead2(currentX2, currentY2-1);
	}
	else if(direction2 == 2) {
		placeHead2(currentX2, currentY2+1);		
	}
	else if(direction2 == 3) {
		placeHead2(currentX2+1, currentY2);		
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

//Move obstacle1 back and forth on the x-axis
void moveObstacle1() {
	//Change the moving direction
	if(obstacle1X > WIDTH - 10)
		obstacle1Direction = 0;
	else if(obstacle1X < 10)
		obstacle1Direction = 3;

	//Move the obstacle
	if(obstacle1Direction == 0)
		placeObstacle1(obstacle1X-1);
	else
		placeObstacle1(obstacle1X+1);
	
	snakePos[15][obstacle1X] = 4;
}

//Move obstacle3 back and forth on the y-axis
void moveObstacle2() {
	//Change the moving direction
	if(obstacle2Y > HEIGHT - 3)
		obstacle2Direction = 1;
	else if(obstacle2Y < 3)
		obstacle2Direction = 2;

	//Move the obstacle
	if(obstacle2Direction == 1)
		placeObstacle2(obstacle2Y-1);
	else
		placeObstacle2(obstacle2Y+1);
	
	snakePos[obstacle2Y][63] = 4;
}

//Check if the snake is outside of the screen or if the head hits the tail and kill it
void deathCheck() {
	if(currentX < 0 || currentX + 3 > WIDTH || currentY < 0 || currentY + 3 > HEIGHT
		|| (direction == 0 && snakePos[currentY + 1][currentX - 1])
		|| (direction == 1 && snakePos[currentY - 1][currentX + 1])
		|| (direction == 2 && snakePos[currentY + 3][currentX + 1])
		|| (direction == 3 && snakePos[currentY + 1][currentX + 3])) {
			alive = 0;
			if(player == 2)
				winner = 2;
		}
}

//Check if the 2nd snake is outside of the screen or if the head hits the tail and kill it
void deathCheck2() {
	if(currentX2 < 0 || currentX2 + 3 > WIDTH || currentY2 < 0 || currentY2 + 3 > HEIGHT
		|| (direction2 == 0 && snakePos[currentY2 + 1][currentX2 - 1])
		|| (direction2 == 1 && snakePos[currentY2 - 1][currentX2 + 1])
		|| (direction2 == 2 && snakePos[currentY2 + 3][currentX2 + 1])
		|| (direction2 == 3 && snakePos[currentY2 + 1][currentX2 + 3])) {
			alive2 = 0;
			winner = 1;
		}
}

//Main function for running the game, returns 1 when game over
unsigned char runGame() {
	//Place an apple if there are non on the screen
	if(!appleCount)
		placeApple();

	//Check if the snakeDirection have changed
	snakeDirection();

	//Check if the snakeDirection have changed for the 2nd snake in 2 player mode
	if(player == 2)
		snakeDirection2();

	//Only update every once in a while
	if(moveCounter > 2) {
		if(player == 2 && !ai) {
			//Check if one of the snakes died
			deathCheck();
			deathCheck2();

			//Move the snakes
			if(alive & alive2) {
				//Move the snakes
				moveSnake();
				moveSnake2();

				//Check if the snakes ate the apple
				eatApple();
				eatApple2();

				if(hardMode) {
					//Move the obstacles
					moveObstacle1();
					moveObstacle2();
					
					//Display the points on the lamps
					PORTE=(length-START_LENGTH)*2;
				}
				else {
					//Display the points on the lamps
					PORTE=(length-START_LENGTH);
				}
			}
		}
		else {
			//Check if the snake died
			deathCheck();
			//Move the snake
			if(alive) {
				//Move the snake
				moveSnake();
				//Check if the snake ate the apple
				eatApple();

				//Only add obstacles in hardMode without AI
				if(hardMode && !ai) {
					//Move the obstacles
					moveObstacle1();
					moveObstacle2();
				}

				if(hardMode)
					//Display the points on the lamps
					PORTE=(length-START_LENGTH)*2;
				else
					//Display the points on the lamps
					PORTE=(length-START_LENGTH);

				//Only update the AI in two player mode vs AI
				if(ai) {
					if(!hardMode) {
						if(aiMoveCounter > 0) {
							moveAI();
							aiMoveCounter = 0;
						}
						else
							aiMoveCounter++;
					}
					else {
						//Move the AI
						moveAI();
					}
					//Check if the AI ate the apple
					aiAppleEat();
				}
			}
		}
		//Reset the counter
		moveCounter = 0;
	}
	else
		moveCounter++;
	
	//Return the current state of the snakes
	return alive & alive2;
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
			else if(appleX != x || appleY != y)
				updatePixel(x+1,y+1, 0);
		}
	}
}

//Draw the apple on the screen
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

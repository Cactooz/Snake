//Functions for inputs
unsigned char getButtons();
unsigned char getButtonsPress();
unsigned char getSwitches();

//Enable interrupts with MIPS
void enable_interrupts();

//Simple delay function with rough ms, with MIPS
void delay(int ms);

//OLED functions
void OledHostInit();
void OledDspInit();
void OledUpdate();
void quickDelay(int time);
void OledPutBuffer(int cb, unsigned char* rgbTx);
unsigned char Spi2PutByte (unsigned char bVal);
void updatePixel(unsigned char x, unsigned char y, unsigned char state);
void clearDisplay();

//Buffer for the OLED display
extern unsigned char displayBuffer[512];

//Prints out capital letters A-Z on display
void printCharacterAZ(char ch, unsigned char xPos, unsigned char yPos, unsigned char state);

//Prints out digits 1 - 9 on display
void printDigit(unsigned char digit, unsigned char xPos, unsigned char yPos, unsigned char state);

//Print word with length "length" at xPos,yPos
void printWord(char* word, unsigned char length, unsigned char xPos, unsigned char yPos);

//Print number with length "length" at xPos,yPos
void printNumber(int number, unsigned char xPos, unsigned char yPos);

//Functions for the menu
unsigned char runMenu();
void chooseDifficulty();

//Game functions
void initGame();
unsigned char runGame();
void drawGame();

//The length of the snake
extern unsigned short length;
//The start length of the snake 
#define START_LENGTH 12
//Keeping track of if the game is in hardMode
extern unsigned char hardMode;
//The amount of snakes
extern unsigned char player;
//The winner of the game in 2 player mode
extern unsigned char winner;
//Functions for highscore
unsigned char displayHighscore();
unsigned char addHighscore(int score);

//Functions for inputs
unsigned char getButtons();

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

//Buffer for the OLED display
extern unsigned char displayBuffer[512];

//Prints out capital letters A-Z on display
void printCharacterAZ(char ch, unsigned char xPos, unsigned char yPos, unsigned char state);

//Print word with length "length" at xPos,yPos
void printWord(char* word, unsigned char length, unsigned char xPos, unsigned char yPos);

//Functions for the game
void gameInit();
void moveSnake();
void drawSnake();

//Functions for the menu
void runMenu();

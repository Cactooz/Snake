//Functions for inputs
unsigned char getButtons();

//Enable interrupts with MIPS
void enable_interrupts();

//OLED functions
void OledHostInit();
void OledDspInit();
void OledUpdate();
void quickDelay(int time);
void OledPutBuffer(int cb, unsigned char* rgbTx);
unsigned char Spi2PutByte (unsigned char bVal);
void updatePixel(unsigned char x, unsigned char y, unsigned char bool);

//Buffer for the OLED display
extern unsigned char displayBuffer[512];

//Functions for the game
void gameInit();
void moveSnake();
void drawSnake();

//Functions for inputs
int getButtons();

//Enable interrupts with MIPS
void enable_interrupts();

//Oled functions
void OledHostInit();
void OledDspInit();
void OledUpdate();
void updatePixel(unsigned char x, unsigned char y, unsigned char bool);

//Declare scrrenbuffer
extern unsigned char displayBuffer[512];

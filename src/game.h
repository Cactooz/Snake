//Functions for inputs
int getButtons();

//Enable interrupts with MIPS
void enable_interrupts();

//Oled functions
void OledHostInit();
void OledDspInit();
void OledUpdate();

//Declare scrrenbuffer
extern unsigned char displayBuffer[512];

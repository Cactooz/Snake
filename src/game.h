//Functions for inputs
int getButtons();

//Enable interrupts with MIPS
void enable_interrupts();

//OLED functions
void updatePixel(unsigned char x, unsigned char y, unsigned char bool);

//Buffer for the OLED display
extern unsigned char displayBuffer[512];

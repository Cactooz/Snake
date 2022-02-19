#include <stdint.h>
#include <pic32mx.h>
#include "game.h"

unsigned char displayBuffer[512] = //Skärmarrayen
{ 
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

//One array for each capital letter A-Z
char font[26][30] = 
{
  {1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1}, //A
  {1,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,0,1,0,0,0,1,1,1,1,1,0}, //B
  {1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1}, //C 
  {1,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0}, //D
  {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1}, //E
  {1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0}, //F
  {1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1,1,1,1,1,1}, //G
  {1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1}, //H
  {0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0}, //I
  {0,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,0}, //J
  {1,0,0,1,0,1,0,1,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,0,0,1,0,0,1,0}, //K
  {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1}, //L
  {1,0,0,0,1,1,1,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1}, //M
  {1,0,0,0,1,1,1,0,0,1,1,0,1,0,1,1,0,1,0,1,1,0,0,1,1,1,0,0,0,1}, //N
  {1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1}, //O
  {1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0}, //P
  {1,1,1,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,1,0,1,1,1,1,0,0,0,0,0,1}, //Q
  {1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,0,1,0,0,0,1}, //R
  {0,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0}, //S
  {1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0}, //T
  {1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1}, //U
  {1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0}, //V
  {1,0,0,0,1,1,0,0,0,1,1,0,1,0,1,1,0,1,0,1,0,1,1,1,0,0,0,1,0,0}, //W
  {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1}, //X
  {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0}, //Y
  {1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1}, //Z
};

void quickDelay(int time) {
	int i;
	for(i = time; i > 0; i--);
}

void OledPutBuffer(int size, unsigned char* transmitByte)
{
  unsigned char bTmp;
  
  int i;
  //Write/Read the data
  for (i = 0; i < size; i++)
  {
	//Wait for transmitter to be ready
	while ((SPI2STAT & 0x08) == 0); //0000 1000 . SPITBE = Bit 3
	
	//Write the next transmit byte.
	SPI2BUF = *transmitByte++;

	//Wait for recieve byte
	while ((SPI2STAT & 0x1) == 0); //0001 . SPIRBF = Bit 0
	bTmp = SPI2BUF;
  }
}

unsigned char Spi2PutByte (unsigned char value)
{
  unsigned char bRx;

  //Wait for transmitter to be ready
  while ((SPI2STAT & 0x08) == 0); //0000 1000 . SPITBE = Bit 3

  //Write the next transmit byte
  SPI2BUF = value;

  //Wait for receive byte
  while ((SPI2STAT & 0x1) == 0); //0001 . SPIRBF = Bit 0

  //Put the received byte in the buffer
  bRx = SPI2BUF;

  return bRx;
} 

void OledHostInit()
{
  //Initialize SPI port 2
  SPI2CON = 0;
  SPI2BRG = 15;
  SPI2STATCLR = 0x40;//0100 0000 Bit 6, Family data sheet sida 61. SPIROV
  SPI2CONSET = 0x40; // Bit 6, Family data sheet sida 61. CKP
  SPI2CONSET = 0x20; //Bit 5 0010 0000, MSTEN
  SPI2CONSET = 0x8000; //Bit 15 1000 0000 0000 0000, ON

  //Make pins RF4, RF5, and RF6 be outputs
  TRISFCLR = 0x70; //0111 0000
  PORTFSET = 0x70; 

  //Make the RG9 pin be an output.
  TRISGCLR = 0x200;//0010 0000 0000
  PORTGSET = 0x200; 
}

void OledDspInit()
{
  //Clear the Data/Cmd bit
  PORTFCLR = 0x10; //0001 0000 . RF4 = Data/CMD
  quickDelay(10);

  //Turn VDD on and wait for the power to come up
  PORTFCLR = 0x40; //0100 0000 . RF6 = VDD Enable
  quickDelay(1000000);

  //Display off command
  Spi2PutByte(0xAE);

  //Bring Reset low and then high
  PORTGCLR = 0x200;// 0010 0000 0000 . RG9= Reset
  quickDelay(10);
  PORTGSET = 0x200;
  quickDelay(10);

  //Send the Set Charge Pump and Set Pre-Charge Period commands
  Spi2PutByte(0x8D);
  Spi2PutByte(0x14);  
  Spi2PutByte(0xD9);
  Spi2PutByte(0xF1); 

  //Turn on VCC and wait 100ms
  PORTFCLR = 0x20;// 0010 0000 . VCC = RF5
  quickDelay(10000000);

  //Send commands to invert the display, put display origin in upper left corner
  Spi2PutByte(0xA1); 
  Spi2PutByte(0xC8); 

  //Send the commande to select sequential COM configuration. This makes the display
  //memory non-interleaved

  Spi2PutByte(0xDA);
  Spi2PutByte(0x20); 

  //Send Display On command
  Spi2PutByte(0xAF); 
}

void OledUpdate()
{
  unsigned char* pagePart;

  pagePart = displayBuffer;

  int page;

  for(page = 0; page < 4; page++) 
  {
	PORTFCLR = 0x10; //0001 0000 . DataCMD = RF4

	//Set page address
	Spi2PutByte(0x22); //Set page command
	Spi2PutByte(page); //page number

	//Start at the left column
	Spi2PutByte(0x00);
	Spi2PutByte(0x10); 

	PORTFSET = 0x10; //0001 0000 . DataCMD = RF4

	//Copy this memory page of display data
	OledPutBuffer(128, pagePart);
	pagePart  += 128;
  }
}

//Function for turning a single pixel on or off
void updatePixel(unsigned char x, unsigned char y, unsigned char state) {
	//Check if the pixels are inside of the screen
	if(x < 128 && y < 32 && state <= 1) {
		//Get the position in the array that should be changed
		short pos = ((y/8)*128) + x;

		//Turn on pixel if state = 1
		if(state == 1) {
			displayBuffer[pos] = (displayBuffer[pos] | (0x1 << (y%8)));
		}
		//Turn off pixel if state = 0
		else if(state == 0) {
			displayBuffer[pos] = (displayBuffer[pos] & ~(0x1 << (y%8)));
		}
	}
}

//Prints out capital letters A-Z on display
void printCharacterAZ(char ch, unsigned char xPos, unsigned char yPos, unsigned char bool)
{
  int pixel;
  if(bool == 1)
    for(pixel = 0; pixel < 30; pixel++)
      updatePixel(xPos + (pixel % 5), yPos + (pixel / 5), font[ch-0x41][pixel]);
  else if(bool == 0)
    for(pixel = 0; pixel < 30; pixel++)
      updatePixel(xPos + (pixel % 5), yPos + (pixel / 5), 0);
}


//Print word with length "length" at xPos,yPos
void printWord(char* word, unsigned char length, unsigned char xPos, unsigned char yPos)
{
		int i;
		for(i = 0; i < length*6; i += 6)
		{	
			if(*word)
				printCharacterAZ(*word, xPos+i, yPos, 1);
			word += 1;
		}
}

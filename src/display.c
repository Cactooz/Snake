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
	0,0,0,0,0,0,0,0,
};

void quickDelay(int time) {
	int i;
	for(i = time; i > 0; i--);
}

void OledPutBuffer(int cb, unsigned char* rgbTx)
{
  int ib;
  unsigned char bTmp;
  
  //Write/Read the data
  for (ib = 0; ib < cb; ib++)
  {
	//Wait for transmitter to be ready
	while ((SPI2STAT & 0x08) == 0); //0000 1000 . SPITBE = Bit 3
	
	//Write the next transmit byte.
	SPI2BUF = *rgbTx++;

	//Wait for recieve byte
	while ((SPI2STAT & 0x1) == 0); //0001 . SPIRBF = Bit 0
	bTmp = SPI2BUF;
  }
}

unsigned char Spi2PutByte (unsigned char bVal)
{
  unsigned char bRx;

  //Wait for transmitter to be ready
  while ((SPI2STAT & 0x08) == 0); //0000 1000 . SPITBE = Bit 3

  //Write the next transmit byte
  SPI2BUF = bVal;

  //Wait for receive byte
  while ((SPI2STAT & 0x1) == 0); //0001 . SPIRBF = Bit 0

  //Put the receive byte in the buffer
  bRx = SPI2BUF;

  return bRx;
} 

void OledHostInit()
{

  unsigned int tcfg;
  //Initialize SPI port 2
  SPI2CON = 0;
  SPI2BRG = 15;
  SPI2STATCLR = 0x40;//0100 0000 Bit 6, Family data sheet sida 61. SPIROV
  SPI2CONSET = 0x40; // Bit 6, Family data sheet sida 61. CKP
  SPI2CONSET = 0x20; //Bit 5 0010 0000, MSTEN
  SPI2CONSET = 0x8000; //Bit 15 1000 0000 0000 0000, ON

  //Make pins RF4, RF5, and RF6 be outputs
  TRISFCLR = 0x70; //0111 0000
  PORTFSET = 0x70; //Skulle kunna va CLR

  //Make the RG9 pin be an output.
  TRISGCLR = 0x200;//0010 0000 0000
  PORTGSET = 0x200; //Skulle kunna va CLR
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
  unsigned char* pb;

  pb = displayBuffer;

  int ipag;

  for(ipag = 0; ipag < 512; ipag++) 
  {
	PORTFCLR = 0x10; //0001 0000 . DataCMD = RF4

	//Set page address
	Spi2PutByte(0x22); //Set page command
	Spi2PutByte(ipag); //page number

	//Start at the left column
	Spi2PutByte(0x00);
	Spi2PutByte(0x10); 

	PORTFSET = 0x10; //0001 0000 . DataCMD = RF4

	//Copy this memory page of display data
	OledPutBuffer(128, pb);
	pb += 128;
  }
}

//Function for turning a single pixel on or off
void updatePixel(unsigned char x, unsigned char y, unsigned char bool) {
	//Check if the pixels are inside of the screen
	if(x < 128 && y < 32 && bool <= 1) {
		//Get the position in the array that should be changed
		short pos = ((y/8)*128) + x;

		//Turn on pixel if bool = 1
		if(bool == 1) {
			displayBuffer[pos] = (displayBuffer[pos] | (0x1 << (y%8)));
		}
		//Turn off pixel if bool = 0
		else if(bool == 0) {
			displayBuffer[pos] = (displayBuffer[pos] & ~(0x1 << (y%8)));
		}
	}
}

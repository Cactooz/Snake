#include <stdint.h>
#include <pic32mx.h>
#include <stdio.h>
#include "game.h"

unsigned char podiumDesign[512] = 
{ 
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
    128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,128,128,128,128,128,128,128,128,128,128,128,
    128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,

    128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
    128,128,128,128,128,128,128,128,128,128,128,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

int highscoreArray[3][4]  = //Initial 1, Initial 2, Score
{
    {'P', 'B', 3, 7},
    {'W', 'H', 2, 3},
    {'M', 'H', 3, 2},
};

void nameSelect()
{
    printWord("NAME", 4, 35, 2);
    printWord("SELECT", 6, 65, 2); //30 pixlar mellan orden
    updatePixel(61, 21, 1);
    int i = 'A';
    int x = 1;
    while (x == 1) //Choose first character
    {
        unsigned char buttonState = getButtons();
        printCharacterAZ(i, 55, 16, 1);
        OledUpdate();
        if (buttonState & 8) //BTN4 Change character
        {
            printCharacterAZ(i,55,16,0);
            i++;
            delay(300);
        }  

        if(i == 'Z' + 1) //Jump to beginning
            i = 'A';

        if(buttonState & 4) //BTN3 Select character
        {
            x = 2;
            delay(300);
        }
    }

    i = 'A';

    while (x == 2) //Choose second character
    {
        unsigned char buttonState = getButtons();
        printCharacterAZ(i, 63, 16, 1);
        OledUpdate();
        if (buttonState & 8) //BTN4 Change character
        {
            printCharacterAZ(i,63,16,0);
            i++;
            delay(300);
        }

        if(i == 'Z' + 1) //Jump to beginning
            i = 'A';
    }
    
}

void displayHighscore()
{   
    int i;
    for(i = 0; i<512; i++)
        displayBuffer[i] = podiumDesign[i];
    //First position
    //printDigit(1,42,5,1);
    //printNumber(12, 50, 15,1);
    //printCharacterAZ(highscoreArray[0][0], 50, 5, 1); //First initial
    //printCharacterAZ(highscoreArray[0][1], 58, 5, 1); //Second initial
    //printDigit(highscoreArray[0][2], 66, 5, 1); //First number
    //printDigit(highscoreArray[0][3], 74, 5, 1); //Second number
}

//void addHighscore(), lägger till ett highscore i arrayen

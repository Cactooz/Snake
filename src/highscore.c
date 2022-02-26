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

int highscoreArray[3][3]  = //Initial 1, Initial 2, Score
{
    {'P', 'B', 370},
    {'M', 'H', 320},
    {'W', 'H', 230},
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

unsigned char displayHighscore()
{   
    int i;
    for(i = 0; i<512; i++)
        displayBuffer[i] = podiumDesign[i];

    //First place
    printCharacterAZ(highscoreArray[0][0], 45, 5, 1);
    printCharacterAZ(highscoreArray[0][1], 51, 5, 1);
    printNumber(highscoreArray[0][2], 60, 5);

    //Second place
    printCharacterAZ(highscoreArray[1][0], 90, 12, 1);
    printCharacterAZ(highscoreArray[1][1], 96, 12, 1);
    printNumber(highscoreArray[1][2], 105, 12);

    //Third place
    printCharacterAZ(highscoreArray[2][0], 5, 20, 1);
    printCharacterAZ(highscoreArray[2][1], 11, 20, 1);
    printNumber(highscoreArray[2][2], 20, 20);

    OledUpdate();
    while (1)
    {
        if(getButtons() & 8)
        {
            int column;
            int row;
            for (column = 0; column < 128; column++) //Turns off every pixel
                for(row = 0; row < 32; row++)
                    updatePixel(column, row, 0);
            return 1;
        }
        delay(100);
    }
}

//void addHighscore(), lägger till ett highscore i arrayen

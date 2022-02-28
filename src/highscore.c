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

    128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
    128,128,128,128,128,128,128,128,128,128,128,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,128,128,128,128,128,128,128,128,
    128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
};

int highscoreArray[3][3]  = //Initial 1, Initial 2, Score
{
    {92, 92, 0},
    {92, 92, 0},
    {92, 92, 0},
};

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
    printCharacterAZ(highscoreArray[1][0], 5, 12, 1);
    printCharacterAZ(highscoreArray[1][1], 11, 12, 1);
    printNumber(highscoreArray[1][2], 20, 12);

    //Third place
    printCharacterAZ(highscoreArray[2][0], 90, 20, 1);
    printCharacterAZ(highscoreArray[2][1], 96, 20, 1);
    printNumber(highscoreArray[2][2], 105, 20);

    OledUpdate();
    while (1)
    {
        if(getButtons() & 8)
        {
            int column;
            int row;
            clearDisplay();
            return 1;
        }
        delay(100);
    }
}

//void addHighscore(), lägger till ett highscore i arrayen
unsigned char addHighscore(int score)
{
    char first;
    char second;
    printWord("NAME", 4, 35, 2);
    printWord("SELECT", 6, 65, 2);
    updatePixel(61, 21, 1);
    char ch = 'A';
    unsigned char x = 1;
    while (x == 1) //Choose first character
    {
        unsigned char buttonState = getButtons();
        printCharacterAZ(ch, 55, 16, 1);
        OledUpdate();
        if (buttonState & 8) //BTN4 Change character
        {
            printCharacterAZ(ch,55,16,0);
            ch++;
            delay(300);
        }  

        if(ch == 'Z' + 1) //Jump to beginning
            ch = 'A';

        if(buttonState & 4) //BTN3 Select character
        {
            first = ch;
            x = 2;
            delay(300);
        }
    }

    ch = 'A';

    while (x == 2) //Choose second character
    {
        unsigned char buttonState = getButtons();
        printCharacterAZ(ch, 63, 16, 1);
        OledUpdate();
        if (buttonState & 8) //BTN4 Change character
        {
            printCharacterAZ(ch,63,16,0);
            ch++;
            delay(300);
        }

        if(buttonState & 4) //BTN3 Select character
        {
            second = ch;
            x = 3;
            delay(300);
        }

        if(ch == 'Z' + 1) //Jump to beginning
            ch = 'A';
    }

    unsigned char i = 0;
    while (highscoreArray[i][2])
    {
        if(i == 2)
            break;
        i++;
    }
      
    if(score > highscoreArray[0][2])
    {
        highscoreArray[0][0] = first;
        highscoreArray[0][1] = second;
        highscoreArray[0][2] = score;
    }

    else if(score > highscoreArray[1][2])
    {
        highscoreArray[1][0] = first;
        highscoreArray[1][1] = second;
        highscoreArray[1][2] = score;
    }

    else if(score > highscoreArray[2][2])
    {
        highscoreArray[2][0] = first;
        highscoreArray[2][1] = second;
        highscoreArray[2][2] = score;
    }
    return 1;

    
    //Name select här 
    //Kollar om det finns en tom plats i arrayen med while loop
    //Jämför med första plats, if
    //Jämför med andra plats, else if
    //Jämför med tredje plats, else if 
}

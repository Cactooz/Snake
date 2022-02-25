#include <stdint.h>
#include <pic32mx.h>
#include <stdio.h>
#include "game.h"

int highscoreArray[3][3]  = //Initial 1, Initial 2, Score
{
    {'P', 'B', 37},
    {'W', 'H', 23},
    {'M', 'H', 32},
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

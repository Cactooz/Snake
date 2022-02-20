#include <stdint.h>
#include <pic32mx.h>
#include <stdio.h>
#include "game.h"

unsigned char runMenu()
{
    int column;
    int row;

    //Loading
    for (column = 0; column < 128; column++)
    {
        for(row = 0; row < 32; row++)
            updatePixel(column, row, 1);

        OledUpdate();
        delay(10);
    }

    //Turn off every pixel
    for (column = 0; column < 128; column++)
        for(row = 0; row < 32; row++)
            updatePixel(column, row, 0);

    //Display text
    printWord("SNAKE", 5, 50, 0);
    printWord("BY", 2, 58, 10);
    printWord("POTNUS", 6, 20, 20);
    printWord("AND", 3, 60, 20);
    printWord("HUGO", 4, 83, 20);
    OledUpdate();

    delay(3000);

    //Turn off every pixel
    for (column = 0; column < 128; column++)
        for(row = 0; row < 32; row++)
            updatePixel(column, row, 0);

    OledUpdate();

    int select = 1;
    while (1)
    {
        switch (select)
        {
        case 1:
            printCharacterAZ(91, 40, 8, 1); //Marker
            printWord("PLAY", 4, 50, 8);
            printWord("LEADERBOARD", 11, 30, 16);
            if(getButtons() & 8) //Press BTN4 to scroll
            {
                printCharacterAZ(91, 40, 8, 0); //Remove Marker
                delay(300);
                select = 2;
            }
            if (getButtons() & 4)
                return 1;
            
            break;
        
        case 2:
            printCharacterAZ(91, 20, 16, 1); //Marker
            printWord("PLAY", 4, 50, 8);
            printWord("LEADERBOARD", 11, 30, 16);
            if(getButtons() & 8) //Press BTN4 to scroll
            {
                printCharacterAZ(91, 20, 16, 0); //Remove Marker
                delay(300);
                select = 1;
            }
            if (getButtons() & 4)
                return 2;
            break;            
        }
        
        OledUpdate();
    }
    

    
}
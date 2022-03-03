#include <stdint.h>
#include <pic32mx.h>
#include <stdio.h>
#include "game.h"

unsigned char podiumDesign[512] = //The screenArray to display the podium
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
    //Score is zero and initials are blank from start
    {92, 92, 0}, 
    {92, 92, 0},
    {92, 92, 0},
};

unsigned char displayHighscore()
{   
    int i;
    for(i = 0; i<512; i++) //Draw the podium design on display
        displayBuffer[i] = podiumDesign[i];

    //First place
    printCharacterAZ(highscoreArray[0][0], 49, 5, 1);
    printCharacterAZ(highscoreArray[0][1], 55, 5, 1);
    printNumber(highscoreArray[0][2], 64, 5);

    //Second place
    printCharacterAZ(highscoreArray[1][0], 9, 12, 1);
    printCharacterAZ(highscoreArray[1][1], 15, 12, 1);
    printNumber(highscoreArray[1][2], 24, 12);

    //Third place
    printCharacterAZ(highscoreArray[2][0], 94, 20, 1);
    printCharacterAZ(highscoreArray[2][1], 100, 20, 1);
    printNumber(highscoreArray[2][2], 109, 20);

    while (1)
    {
        if(getButtonsPress() & 8) //BTN4 to exit
        {
            clearDisplay();
            return 1; //Return 1 to exit to menu
        }
        delay(100);
    }
}

//Adds a highscore to the array if the score places top 3
unsigned char addHighscore(int score)
{
    if(score >= highscoreArray[2][2]) //You get a place on the leaderboard
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
            printCharacterAZ(ch, 55, 16, 1);
            if (getButtonsPress() & 0x8) //BTN4 Change character
            {
                printCharacterAZ(ch,55,16,0);
                ch++;
                delay(300);
            }  

            if(ch == 'Z' + 1) //Jump to beginning
                ch = 'A';

            if(getButtonsPress() & 0x4) //BTN3 Select character
            {
                first = ch;
                x = 2;
                delay(300);
            }
        }

        ch = 'A';

        while (x == 2) //Choose second character
        {
            printCharacterAZ(ch, 63, 16, 1);
            if (getButtonsPress() & 0x8) //BTN4 Change character
            {
                printCharacterAZ(ch,63,16,0);
                ch++;
                delay(300);
            }

            if(getButtonsPress() & 0x4) //BTN3 Select character
            {
                second = ch;
                x = 3;
                delay(300);
            }

            if(ch == 'Z' + 1) //Jump to beginning
                ch = 'A';
        }

        if(score >= highscoreArray[0][2]) //First place 
        { 
            //Move second place down to third
            highscoreArray[2][0] = highscoreArray[1][0];
            highscoreArray[2][1] = highscoreArray[1][1];
            highscoreArray[2][2] = highscoreArray[1][2];

            //Move first place down to second
            highscoreArray[1][0] = highscoreArray[0][0];
            highscoreArray[1][1] = highscoreArray[0][1];
            highscoreArray[1][2] = highscoreArray[0][2];

            //New first place
            highscoreArray[0][0] = first;
            highscoreArray[0][1] = second;
            highscoreArray[0][2] = score;
        }

        else if(score >= highscoreArray[1][2]) //Second place
        {
            //Move second place down to third
            highscoreArray[2][0] = highscoreArray[1][0];
            highscoreArray[2][1] = highscoreArray[1][1];
            highscoreArray[2][2] = highscoreArray[1][2];

            //New second place
            highscoreArray[1][0] = first;
            highscoreArray[1][1] = second;
            highscoreArray[1][2] = score;
        }

        else if(score >= highscoreArray[2][2])
        {
            //New third place
            highscoreArray[2][0] = first;
            highscoreArray[2][1] = second;
            highscoreArray[2][2] = score;
        }
        return 1;
    }
    else //Game over, no place on the leaderboard
    {
        clearDisplay();
        printWord("GAME OVER", 9, 40, 10);
        delay(2000);
        return 1;   
    }
}


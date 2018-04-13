#include <iostream>
#include <bits/stdc++.h>
#include "drawing.hpp"
#include "ColorDisplay.h"
#include <windows.h>
#include <conio.h>
#include "others.hpp"

using namespace std;

void printMainMenu()
{
    int bgcolor=BLUE*16;
    system("cls");
    ColorDisplay background(98,28, {1,1});
    background.setBackGroundColor(bgcolor+BLACK);
    background.resetDisplay();
    draw(29,47,bgcolor+LIGHT_PURPLE,"3.3.1");
    ///Header
    IMAGE snake(9,bgcolor+WHITE);
    snake.image=   {"      _  _  _  _                                  _                          ",
                    "    _(_)(_)(_)(_)_                               (_)                         ",
                    "   (_)          (_) _  _  _  _      _  _  _      (_)     _   _  _  _  _      ",
                    "   (_)_  _  _  _   (_)(_)(_)(_)_   (_)(_)(_) _   (_)   _(_) (_)(_)(_)(_)_    ",
                    "     (_)(_)(_)(_)_ (_)        (_)   _  _  _ (_)  (_) _(_)  (_) _  _  _ (_)   ",
                    "    _           (_)(_)        (_) _(_)(_)(_)(_)  (_)(_)_   (_)(_)(_)(_)(_)   ",
                    "   (_)_  _  _  _(_)(_)        (_)(_)_  _  _ (_)_ (_)  (_)_ (_)_  _  _  _     ",
                    "     (_)(_)(_)(_)  (_)        (_)  (_)(_)(_)  (_)(_)    (_)  (_)(_)(_)(_)    ",
                    "                                                                             "
                   };
    displayImage(snake,2,12);
    draw(13,20,bgcolor+LIGHT_GREEN,"1. Start Game");
    draw(14,20,bgcolor+LIGHT_GREEN,"2. How to Play");
    draw(15,20,bgcolor+LIGHT_GREEN,"3. Highscore");
    draw(16,20,bgcolor+LIGHT_GREEN,"4. Quit");
    draw(18,20,bgcolor+LIGHT_YELLOW,"Press 1,2,3 or 4 to continue");
}

void printHowtoPlay()
{
    int bgcolor=BLUE*16;
    system("cls");
    ColorDisplay background(98,28, {1,1});
    background.setBackGroundColor(bgcolor+BLACK);
    background.resetDisplay();
    IMAGE instruction(14,bgcolor+LIGHT_GREEN);
    instruction.image=
    {
        "GENERAL RULE",
        "   - Don't run into the Wall or your own tail: you die, apparently  ",
        "   - Eat foods to gain score and length, eat special foods to gain massive score ",
        "   - Reach the required score to advance to next map",
        "CONTROL",
        "   - Use WASD or UP LEFT DOWN RIGHT to change the snake's direction",
        "   - Press P to pause (or unpause)",
        "SPECIAL FOOD",
        "   - Eat special food will give the player 10 points",
        "   - Special food will give you one random effect (buff or debuff)",
        "   - Notification contains information about the effect, keep an eye on it",
        "Tips: Press pause when eat special food to check the effect before you continue",
        "",
        "Press [SPACE] to go back to main menu"
    };
    displayImage(instruction,5,10);
    while (1)
    {
        if (kbhit())
        {
            char tmp=getch();
            if (tmp==SPACE)
            {
                printMainMenu();
                break;
            }
        }
    }
}

void printHighScore(int highscore)
{
    int bgcolor=BLUE*16;
    system("cls");
    ColorDisplay background(98,28, {1,1});
    background.setBackGroundColor(bgcolor+BLACK);
    background.resetDisplay();
    draw(15,30,bgcolor+LIGHT_GREEN,"Local highscore is "+to_string(highscore));
    draw(18,30,bgcolor+LIGHT_GREEN,"Press [SPACE] to go back to main menu");
    while (1)
    {
        if (kbhit())
        {
            char tmp=getch();
            if (tmp==SPACE)
            {
                printMainMenu();
                break;
            }
        }
    }
}
int gameOver(int length,int score,int bscore)
{
    int start=0;
    draw(26,2,10,"Game over! Your final length is " + to_string(length));
    modHighscore(bscore,score);
    draw(29,2,10,"Would you like to retry ? y/n?");
    while (1)
    {
        if (kbhit())
        {
            char tmp=getch();
            if (tmp=='n')
                break;
            if (tmp=='y')
            {
                start=1;
                break;
            }
        }
    }
    return 0;
}
void gameClear(int length,int score,int bscore)
{
    cout<<"Just kidding, there isn't Stage 4, You cleared the game! Congratulation\n";
    gameOver(length,score,bscore);
    cout<<"Credit\n\n";
    cout<<"Me - Do everything lol\n";
    cout<<"Thank you for playing my game\n";
    cout<<"Press [Enter] to exit";
}

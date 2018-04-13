#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED



#endif // GUI_HPP_INCLUDED

#include <iostream>

#define PLAY '1'
#define HTP '2'
#define HC '3'
#define QUIT '4'

void printMainMenu();
void printHowtoPlay();
void printHighScore(int highscore);
int gameOver(int length,int score,int bscore);
void gameClear(int length,int score,int bscore);

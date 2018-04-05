#include <conio.h>
#include <windows.h>
#include <iostream>
#include "ColorDisplay.h"

using namespace std;

void gotoxy(int y, int x)
{
    x--;
    y--;
    COORD cor;
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

void textColor(int x)//Xac dinh mau cua chu
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void draw(int x,int y,int color,std::string text)
{
    textColor(color);
    gotoxy(x,y);
    cout<<text;
}
void draw(int x,int y,int color,char symbol)
{
    textColor(color);
    gotoxy(x,y);
    cout<<symbol;
}
void clear_notification()
{
    int defaultcolor=10;
    textColor(defaultcolor);
    gotoxy(10,52);
    std::cout<<"                                           ";
}

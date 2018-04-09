#include <conio.h>
#include <windows.h>
#include <iostream>
#include "drawing.hpp"
#include "ColorDisplay.h"

using namespace std;

/// Move cursor to COORDINATION (x,y)
void gotoxy(int y, int x)
{
    x--;
    y--;
    COORD cor;
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}
/// Set typing color to x
void textColor(int x)//Xac dinh mau cua chu
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

/// Draw a text
void draw(int x,int y,int color,std::string text)
{
    textColor(color);
    gotoxy(x,y);
    cout<<text;
}
/// Draw a character
void draw(int x,int y,int color,char symbol)
{
    textColor(color);
    gotoxy(x,y);
    cout<<symbol;
}

/// Clear notification area
void clear_notification()
{
    int defaultcolor=10;
    textColor(defaultcolor);
    gotoxy(10,52);
    std::cout<<"                                           ";
}

void displayImage(IMAGE Image,int x,int y)
{
    for (int i=0;i<Image.height;i++)
    {
        gotoxy(x+i,y);
        textColor(Image.color);
        cout<<Image.image[i]<<"\n";
    }
}

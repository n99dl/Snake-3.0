#include <ctime>
#include <conio.h>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

int mapW=50;
int mapH=20;

int defaultcolor=10;
typedef pair<int,int> ii;

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

ii generate_food(int regenerate,int playground[][201])
{
    int x,y;
    x=rand()%(mapH-2)+2;
    y=rand()%(mapW-2)+2;
    while (playground[x][y])
    {
        x=rand()%(mapH-2)+2;
        y=rand()%(mapW-2)+2;
    }
    if (regenerate==1)
    {
        playground[x][y]=-2;
        textColor(28);
    }
    else if (regenerate==0)
    {
        playground[x][y]=-4;
        textColor(30);
    }
    else if (regenerate==-1)
    {
        playground[x][y]=-5;
        textColor(26);
    }
    gotoxy(x,y);
    char food_symbol=254;
    cout<<food_symbol;
    textColor(defaultcolor);
    return ii(x,y);
}


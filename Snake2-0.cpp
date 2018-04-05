#include <ctime>
#include <algorithm>
#include <iostream>
#include <windows.h>
#include "drawing.hpp"
#include "ColorDisplay.h"
#include <conio.h>

using namespace std;

void printPlayground(int playground[][201],int mapH,int mapW,int Map)
{
    ColorDisplay screen(48,18,{1,1});
    /*gotoxy(1,1);
    for (int i=1; i<=mapH; i++)
    {
        for (int j=1; j<=mapW; j++)
        {
            if (playground[i][j]==-999)
                textColor(1);
            else if (playground[i][j]>=0)
                textColor(17);
            else
                textColor(31+16*6);
            cout<<" ";
        }
        cout<<"\n";
    }*/
    screen.setBackGroundColor(BLUE*16);
    screen.resetDisplay();
    if (Map==1)
    {
        ColorDisplay middle(18,6,{16,7});
        middle.resetDisplay();
    }
    else
        if (Map==2)
    {
        screen.drawingLineHorizontal(1,10,48);
        screen.drawingLineVertical(24,1,18);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),11,0);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),12,0);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),13,0);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),11+25,0);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),12+25,0);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),13+25,0);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),11+25,19);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),12+25,19);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),13+25,19);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),11,19);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),12,19);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),13,19);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),0,15);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),0,14);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),49,15);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),49,14);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLUE*16),24,15);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLUE*16),24,14);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),49,5);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),49,4);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),0,5);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLACK*16),0,4);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLUE*16),24,5);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLUE*16),24,4);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLUE*16),11,10);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLUE*16),12,10);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLUE*16),13,10);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLUE*16),11+25,10);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLUE*16),12+25,10);
        screen.setColorCharacterAtPosition(ColorCharacter(' ',BLUE*16),13+25,10);
        /*FillConsoleOutputCharacter(outConsole, colorchar.character, 1, position, &garbage);
        FillConsoleOutputAttribute(outConsole, colorchar.color, 1, position, &garbage);*/
    }
    draw(1,52,10,"Press W or Arrow UP to go up");
    draw(2,52,10,"Press D to Arrow RIGHT go right");
    draw(3,52,10,"Press S to Arrow DOWN go down");
    draw(4,52,10,"Press A to Arrow LEFT go left");
    draw(5,52,10,"Press P to pause");
}

void setup_map(int Map,int mapH,int mapW,int playground[][201])
{
    for (int i=1; i<=mapH; i++)
        for (int j=1; j<=mapW; j++)
            playground[i][j]=0;
    for (int i=1; i<=mapW; i++)
        playground[1][i]=playground[mapH][i]=-1;
    for (int i=1; i<=mapH; i++)
        playground[i][1]=playground[i][mapW]=-1;
    if (Map==1)
    {
        for (int i=7; i<=14; i++)
            for (int j=16; j<=35; j++)
                if (i==7||i==14||j==16||j==35)
                    playground[i][j]=-1;
                else
                    playground[i][j]=-999;
    }
    else if (Map==2)
    {
        for (int i=1; i<=50; i++)
            playground[11][i]=-1;
        for (int i=1; i<=20; i++)
            playground[i][25]=-1;
        playground[1][12]=playground[1][13]=playground[1][14]=playground[20][12]=playground[20][13]=playground[20][14]=playground[1][37]=playground[1][38]=playground[1][39]
                                            =playground[20][37]=playground[20][38]=playground[20][39]=playground[5][1]=playground[6][1]=playground[5][50]=playground[6][50]
                                                    =playground[15][1]=playground[16][1]=playground[15][50]=playground[16][50]=10;
        playground[11][12]=playground[11][13]=playground[11][14]=playground[11][37]=playground[11][38]=playground[11][39]=playground[5][25]=playground[6][25]=0;
        playground[15][25]=playground[16][25]=0;
    }
}
pair<int,int> generate_food(int regenerate,int playground[][201],int mapW,int mapH)
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
    return make_pair(x,y);
}

int choose_speed()
{
    int speed;
    bool legal=0;
    while (!legal)
    {
        system("cls");
        speed=0;
        draw(7,52,10,"Choose level (1-10) :");
        cin>>speed;
        if (speed<1||speed>10)
        {
            system("cls");
            cout<<"Invalid speed! Press anykey to retry";
            while (!kbhit());
        }
        else legal=1;
    }
    speed=speed*30+680;
    return speed;
}
void changedir(int &dir)
{
    char ndir=getch();
    if (ndir=='p')
    {
        draw(13,52,10,"Game pause ! Press anykey to resume");
        while (!kbhit());
        draw(13,52,10,"                                   ");
    }
    if ((ndir=='w'||ndir==72)&&dir!=3) dir=1;
    if ((ndir=='d'||ndir==77)&&dir!=4) dir=2;
    if ((ndir=='s'||ndir==80)&&dir!=1) dir=3;
    if ((ndir=='a'||ndir==75)&&dir!=2) dir=4;
}


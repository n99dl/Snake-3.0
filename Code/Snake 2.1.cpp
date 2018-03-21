#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

typedef pair<int,int> ii;

map<int,char> type;
int movex[]= {0,-1,0,1,0};
int movey[]= {0,0,1,0,-1};
int length=0;
int mapW=50;
int mapH=20;
char sn=219;
char head=233;
bool start=0;
int playground[51][51];
int speed;
queue<ii> snake;

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

int headpos_x;
int headpos_y;
int dir;

void generate_food()
{
    int x,y;
    x=rand()%(mapH-2)+2;
    y=rand()%(mapW-2)+2;
    while (playground[x][y])
    {
        x=rand()%(mapH-2)+2;
        y=rand()%(mapW-2)+2;
    }
    playground[x][y]=-2;
    gotoxy(x,y);
    textColor(28);
    char bullshit=254;
    cout<<bullshit;
    textColor(10);
}
void printPlayground()
{

    gotoxy(1,1);
    for (int i=1; i<=mapH; i++)
    {
        for (int j=1; j<=mapW; j++)
        {
            if (playground[i][j]>=0)
                textColor(16);
            else
                textColor(31+16*6);
            cout<<" ";
            type[playground[i][j]];
        }
        cout<<"\n";
    }
    textColor(10);
    gotoxy(1,52);
    cout<<"Press W to go up";
    gotoxy(2,52);
    cout<<"Press D to go right";
    gotoxy(3,52);
    cout<<"Press S to go down";
    gotoxy(4,52);
    cout<<"Press A to go left";
    gotoxy(5,52);
    cout<<"Press P to go pause";
}
void generate_snake()
{
    while (snake.size()) snake.pop();
    textColor(30);
    length=3;
    headpos_x=mapH/2;
    headpos_y=mapW/2;
    playground[headpos_x+2][headpos_y]=playground[headpos_x+1][headpos_y]=playground[headpos_x][headpos_y]=1;
    snake.push(ii(headpos_x+2,headpos_y));
    gotoxy(headpos_x+2,headpos_y);
    cout<<sn;
    snake.push(ii(headpos_x+1,headpos_y));
    gotoxy(headpos_x+1,headpos_y);
    cout<<sn;
    snake.push(ii(headpos_x,headpos_y));
    gotoxy(headpos_x,headpos_y);
    cout<<head;
    textColor(10);
}
void init()
{
    char bullshit=254;
    type[-2]=' ';
    type[-1]='*';
    type[0]=' ';
    type[1]=' ';
    for (int i=1; i<=mapH; i++)
        for (int j=1; j<=mapW; j++)
            playground[i][j]=0;
    for (int i=1; i<=mapW; i++)
        playground[1][i]=playground[mapH][i]=-1;
    for (int i=1; i<=mapH; i++)
        playground[i][1]=playground[i][mapW]=-1;
    dir=1;
    printPlayground();
    generate_food();
    generate_snake();
}
void changedir()
{
    char ndir=getch();
    if (ndir=='p')
    {
        gotoxy(10,60);
        textColor(10);
        cout<<"Game pause ! Press anykey to resume";
        gotoxy(10,60);
        while (!kbhit());
        cout<<"                                   ";
    }
    if (ndir=='w'&&dir!=3) dir=1;
    if (ndir=='d'&&dir!=4) dir=2;
    if (ndir=='s'&&dir!=1) dir=3;
    if (ndir=='a'&&dir!=2) dir=4;
}
void move()
{
    gotoxy(headpos_x,headpos_y);
    textColor(30);
    cout<<sn;
    int nheadpos_x=headpos_x+movex[dir];
    int nheadpos_y=headpos_y+movey[dir];
    snake.push(ii(nheadpos_x,nheadpos_y));
    gotoxy(nheadpos_x,nheadpos_y);
    textColor(30);
    cout<<head;
    textColor(10);
    if (playground[nheadpos_x][nheadpos_y]==-2)
    {
        length++;
        generate_food();
    }
    else
    {
        ii last=snake.front();
        snake.pop();
        playground[last.first][last.second]=0;
        gotoxy(last.first,last.second);
        textColor(17);
        cout<<" ";
         if (playground[nheadpos_x][nheadpos_y]!=0)
        start=0;
    }
    gotoxy(22,1 );
    headpos_x=nheadpos_x;
    headpos_y=nheadpos_y;
    playground[headpos_x][headpos_y]=1;
}
/*void updateSnake()
{
    for (int i=1; i<=mapH; i++)
        for (int j=1; j<=mapW; j++)
            if (playground[i][j]>0) playground[i][j]--;
}*/

void run()
{
    bool legal=0;
    while (!legal)
    {
        system("cls");
        init();
        speed=0;
        gotoxy(7,52);
        cout<<"Choose level (1-10) :";
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
    gotoxy(22,14);
    cout<<"Press any key to start";
    while (!kbhit());
    start=1;
    while (start)
    {
        if (kbhit())
            changedir();

        move();
        //system("cls");
        //updateSnake();
        //printPlayground();
        if (dir==2||dir==4)
            Sleep(1000-speed);
        else
            Sleep(5*(1000-speed)/2);
    }
}
int main()
{
    // cout<<"\";
    system("MODE 100,30");
    textColor(10);
    //system("color 14");
    cout<<"n99dl's snake 2.1\n";
    cout<<"Press [SPACE] to continue";
    while (1)
    {
        if (kbhit)
        {
            char tmp=getch();
            if (tmp==32)
                break;
        }
    }
    start = 1;
    while (start)
    {
        run();

        textColor(10);
        system("cls");
        cout<<"Game over! Your final length is "<<length<<"\n";
        cout<<"Would you like to retry ? y/n?\n";
        while (1)
        {
            if (kbhit())
            {
                char tmp=getch();
                if (tmp=='n') return 0;
                if (tmp=='y')
                {
                    start=1;
                    break;
                }
            }
        }
    }
}

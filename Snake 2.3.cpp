#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>

using namespace std;

typedef pair<int,int> ii;

//Snake 1.0 stuff : map<int,char> type;

//Map properties
int mapW=50;
int mapH=20;
// Snake properties
char sn=219;
char head=233;
bool start=0;
int length=0;
int speed;
queue<ii> snake;
// COLOR
int backgroundcolor=17;
int snakecolor=30;
int defaultcolor=10;
//Game's variables
int playground[51][51];
int movex[]= {0,-1,0,1,0};
int movey[]= {0,0,1,0,-1};
int score;
int food;
//Snake 2.2
int sf_x;
int sf_y;
ii toxic[30+1];
bool invi=0;
bool inputR=0;
bool tlp=0;

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

ii generate_food(int regenerate)
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
        textColor(29);
    }
    gotoxy(x,y);
    char food_symbol=254;
    cout<<food_symbol;
    textColor(defaultcolor);
    return ii(x,y);
}
void printPlayground()
{
    gotoxy(1,1);
    for (int i=1; i<=mapH; i++)
    {
        for (int j=1; j<=mapW; j++)
        {
            if (playground[i][j]>=0)
                textColor(backgroundcolor);
            else
                textColor(31+16*6);
            cout<<" ";
        }
        cout<<"\n";
    }
    textColor(defaultcolor);
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

void clear_notification()
{
    textColor(defaultcolor);
    gotoxy(10,52);
    cout<<"                                           ";
}
void generate_special_food()
{
    sf_x=rand()%(mapH-2)+2;
    sf_y=rand()%(mapW-2)+2;
    while (playground[sf_x][sf_y])
    {
        sf_x=rand()%(mapH-2)+2;
        sf_y=rand()%(mapW-2)+2;
    }
    playground[sf_x][sf_y]=-3;
    gotoxy(sf_x,sf_y);
    textColor(29);
    char specaialfood_symbol='X';
    cout<<specaialfood_symbol;
    textColor(defaultcolor);
}
void half_size()
{
    textColor(backgroundcolor);
    while (snake.size()>length/2)
    {
        ii tmp=snake.front();
        snake.pop();
        gotoxy(tmp.first,tmp.second);
        cout<<" ";
        playground[tmp.first][tmp.second]=0;
    }
    length/=2;
    clear_notification();
    textColor(defaultcolor);
    gotoxy(10,52);
    cout<<"Half size !!";
}
void food_spam()
{
    generate_food(0);
    generate_food(0);
    generate_food(0);
    generate_food(0);
    generate_food(0);
    clear_notification();
    gotoxy(10,52);
    textColor(defaultcolor);
    cout<<"Food spam !!";
}
void invisible()
{
    clear_notification();
    gotoxy(10,52);
    textColor(defaultcolor);
    cout<<"Invisible snake (eat food to reverse)";
    invi=1;
    head=' ';
    textColor(defaultcolor);
    queue<ii> tmp=snake;
    while (tmp.size()>=snake.size()/2)
        tmp.pop();
    while (tmp.size())
    {
        ii tmp1;
        tmp1=tmp.front();
        tmp.pop();
        gotoxy(tmp1.first,tmp1.second);
        cout<<" ";
    }
    sn=' ';
}
void reverse_invi()
{
    textColor(snakecolor);
    invi=0;
    queue<ii> tmp=snake;
    sn=219;
    while (tmp.size()>1)
    {
        ii tmp1;
        tmp1=tmp.front();
        tmp.pop();
        gotoxy(tmp1.first,tmp1.second);
        cout<<sn;
    }
    ii tmp1;
    head=233;
    tmp1=tmp.front();
    tmp.pop();
    gotoxy(tmp1.first,tmp1.second);
    cout<<head;
    clear_notification();
    gotoxy(10,52);
    textColor(defaultcolor);
    cout<<"Invisible reversed !";
}
void toxic_spam()
{
    toxic[0].first=1;
    for (int i=1; i<=30; i++)
        toxic[i]=generate_food(-1);
    clear_notification();
    gotoxy(10,52);
    textColor(defaultcolor);
    cout<<"Toxic spam !! (Eat food to clear toxic)";
}
void clear_toxic()
{
    textColor(backgroundcolor);
    for (int i=1; i<=30; i++)
    {
        gotoxy(toxic[i].first,toxic[i].second);
        cout<<" ";
        playground[toxic[i].first][toxic[i].second]=0;
    }
    toxic[0].first=0;
    clear_notification();
    gotoxy(10,52);
    textColor(defaultcolor);
    cout<<"Toxic cleared!";
}
void reverse_input()
{
    inputR=1;
    swap(movex[1],movex[3]);
    swap(movey[1],movey[3]);
    swap(movex[2],movex[4]);
    swap(movey[2],movey[4]);
    dir=dir+2;
    if (dir>4) dir-=2;
    clear_notification();
    textColor(defaultcolor);
    gotoxy(10,52);
    cout<<"Input reversed (Eat 3 foods to set it back)";
}
void rreverse_input()
{
    inputR=0;
    swap(movex[1],movex[3]);
    swap(movey[1],movey[3]);
    swap(movex[2],movex[4]);
    swap(movey[2],movey[4]);
    dir=dir+2;
    if (dir>4) dir-=2;
    clear_notification();
    textColor(defaultcolor);
    gotoxy(10,52);
    cout<<"Input normalized";
}
void telepoter()
{
    gotoxy(headpos_x,headpos_y);
    textColor(snakecolor);
    cout<<sn;
    int x,y;
    x=rand()%(mapH-4)+3;
    y=rand()%(mapW-4)+3;
    while (playground[x][y])
    {
        x=rand()%(mapH-4)+3;
        y=rand()%(mapW-4)+3;
    }
    int nheadpos_x=x;
    int nheadpos_y=y;
    snake.push(ii(nheadpos_x,nheadpos_y));
    gotoxy(nheadpos_x,nheadpos_y);
    textColor(snakecolor);
    cout<<head;
    gotoxy(22,1 );
    headpos_x=nheadpos_x;
    headpos_y=nheadpos_y;
    playground[headpos_x][headpos_y]=1;
    clear_notification();
    textColor(defaultcolor);
    gotoxy(10,52);
    cout<<"Teleported !";
}

void eat_specialfood()
{
    score+=10;
    int luck=rand()%6;;
    switch (luck)
    {
    case 0:
        half_size();
        break;
    case 1:
        food_spam();
        break;
    case 2:
        invisible();
        break;
    case 3:
        toxic_spam();
        break;
    case 4:
        reverse_input();
        break;
    case 5:
        tlp=1;
        break;
    }
    sf_x=sf_y=0;
}

void generate_snake()
{
    while (snake.size()) snake.pop();
    textColor(snakecolor);
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
    textColor(defaultcolor);
}
void init()
{
    food=3;
    score=3;
    for (int i=1; i<=mapH; i++)
        for (int j=1; j<=mapW; j++)
            playground[i][j]=0;
    for (int i=1; i<=mapW; i++)
        playground[1][i]=playground[mapH][i]=-1;
    for (int i=1; i<=mapH; i++)
        playground[i][1]=playground[i][mapW]=-1;
    dir=1;
    printPlayground();
    generate_food(1);
    generate_snake();
}
void changedir()
{
    char ndir=getch();
    if (ndir=='p')
    {

        clear_notification();
        gotoxy(10,52);
        textColor(defaultcolor);
        cout<<"Game pause ! Press anykey to resume";
        gotoxy(10,52);
        while (!kbhit());
        clear_notification();
    }
    if (ndir=='w'&&dir!=3) dir=1;
    if (ndir=='d'&&dir!=4) dir=2;
    if (ndir=='s'&&dir!=1) dir=3;
    if (ndir=='a'&&dir!=2) dir=4;
}
void move()
{
    gotoxy(headpos_x,headpos_y);
    textColor(snakecolor);
    cout<<sn;
    int nheadpos_x=headpos_x+movex[dir];
    int nheadpos_y=headpos_y+movey[dir];
    snake.push(ii(nheadpos_x,nheadpos_y));
    gotoxy(nheadpos_x,nheadpos_y);
    textColor(snakecolor);
    cout<<head;
    textColor(defaultcolor);
    if (playground[nheadpos_x][nheadpos_y]==-3)
        eat_specialfood();
    else if (playground[nheadpos_x][nheadpos_y]==-2)
    {
        if (invi)
            reverse_invi();
        if (toxic[0].first)
            clear_toxic();
        if (sf_x)
        {
            gotoxy(sf_x,sf_y);
            textColor(backgroundcolor);
            cout<<" ";
            playground[sf_x][sf_y]=0;
            sf_x=sf_y=0;
        }
        length++;
        score++;
        food++;
        if (food%3==0)
        {
            if (inputR)
                rreverse_input();
            generate_special_food();
        }
        generate_food(1);
    }
    else if (playground[nheadpos_x][nheadpos_y]==-4)
    {
        if (toxic[0].first)
            clear_toxic();
        if (invi)
            reverse_invi();
        length++;
        score++;
    }
    else
    {
        ii last=snake.front();
        snake.pop();
        playground[last.first][last.second]=0;
        gotoxy(last.first,last.second);
        textColor(backgroundcolor);
        cout<<" ";
        if (playground[nheadpos_x][nheadpos_y]!=0)
            start=0;
    }
    if (tlp)
    {
        telepoter();
        tlp=0;
    }
    else
    {
        gotoxy(22,1 );
        headpos_x=nheadpos_x;
        headpos_y=nheadpos_y;
        playground[headpos_x][headpos_y]=1;
        if (invi)
        {
            sn=219;
            queue<ii> tmp=snake;
            while (tmp.size()>=snake.size()/2)
            {
                ii t=tmp.front();
                tmp.pop();
                textColor(snakecolor);
                gotoxy(t.first,t.second);
                cout<<sn;
            }
            sn=0;
        }
    }
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
    srand(time(NULL));
    // cout<<"\";
    system("MODE 100,30");
    textColor(defaultcolor);
    //system("color 14");
    cout<<"n99dl's snake 2.2\n";
    cout<<"Use WASD to move the snake. Eat food to earn length\n";
    cout<<"And... enjoy the special food. Who know what you gonna get?\n";
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
        if (invi)
            reverse_invi();
        if (inputR)
            rreverse_input();
        textColor(defaultcolor);
        //system("cls");
        clear_notification();
        textColor(defaultcolor);
        gotoxy(23,1);
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

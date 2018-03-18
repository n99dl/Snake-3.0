#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "Snake2-0.hpp"
//#include "drawing.hpp"

using namespace std;

ifstream fi("highscore.txt");
ofstream fo("highscore.txt");

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
//queue<ii> snake;
ii snake[1000];
int L,R;
// COLOR
int backgroundcolor=17;
int snakecolor=30;
int defaultcolor=10;
//Game's variables
int bscore=0;
int playground[201][201];
int movex[]= {0,-1,0,1,0};
int movey[]= {0,0,1,0,-1};
int score;
int food;
int require[]= {50,150,1000};
//Snake 2.2
int Map=0;
int sf_x;
int sf_y;
ii toxic[30+1];
bool invi=0;
int inviR;
bool inputR=0;
bool tlp=0;

int headpos_x;
int headpos_y;
int dir;

void printPlayground()
{
    gotoxy(1,1);
    for (int i=1; i<=mapH; i++)
    {
        for (int j=1; j<=mapW; j++)
        {
            if (playground[i][j]==-999)
                textColor(1);
            else if (playground[i][j]>=0)
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
    while (R-L+1>length/2)
    {
        ii tmp=snake[L++];
        gotoxy(tmp.first,tmp.second);
        cout<<" ";
        playground[tmp.first][tmp.second]=0;
    }
    length/=2;
    clear_notification();
    textColor(defaultcolor+1);
    gotoxy(10,52);
    cout<<"Half size !!";
}
void food_spam()
{
    generate_food(0,playground);
    generate_food(0,playground);
    generate_food(0,playground);
    generate_food(0,playground);
    generate_food(0,playground);
    clear_notification();
    gotoxy(10,52);
    textColor(defaultcolor+1);
    cout<<"Food spam !!";
}
void invisible()
{
    clear_notification();
    gotoxy(10,52);
    textColor(defaultcolor+1);
    cout<<"Invisible snake (eat food to reverse)";
    invi=1;
    head=' ';
    textColor(defaultcolor);
    /*while (tmp.size()>=snake.size()/2)
        tmp.pop();
    while (tmp.size())
    {
        ii tmp1;
        tmp1=tmp.front();
        tmp.pop();
        gotoxy(tmp1.first,tmp1.second);
        cout<<" ";
    }*/
    for (int i=L+(R-L+1)/2; i<=R; i++)
    {
        ii tmp1;
        tmp1=snake[i];
        gotoxy(tmp1.first,tmp1.second);
        cout<<" ";
    }
    inviR=L+(R-L+1)/2-1;
    sn=' ';
}
void reverse_invi()
{
    textColor(snakecolor);
    invi=0;
    sn=219;
    head=233;
    for (int i=L; i<R; i++)
    {
        gotoxy(snake[i].first,snake[i].second);
        cout<<sn;
    }
    gotoxy(snake[R].first,snake[R].second);
    cout<<head;
    clear_notification();
    gotoxy(10,52);
    textColor(defaultcolor+1);
    cout<<"Invisible reversed !";
}
void toxic_spam()
{
    toxic[0].first=1;
    for (int i=1; i<=30; i++)
        toxic[i]=generate_food(-1,playground);
    clear_notification();
    gotoxy(10,52);
    textColor(defaultcolor+1);
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
    textColor(defaultcolor+1);
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
    if (dir>4) dir-=4;
    clear_notification();
    textColor(defaultcolor+1);
    gotoxy(10,52);
    cout<<"Input reversed (Eat 3 foods to set it back)";
    snakecolor=26;
}
void rreverse_input()
{
    inputR=0;
    swap(movex[1],movex[3]);
    swap(movey[1],movey[3]);
    swap(movex[2],movex[4]);
    swap(movey[2],movey[4]);
    dir=dir+2;
    if (dir>4) dir-=4;
    clear_notification();
    textColor(defaultcolor+1);
    gotoxy(10,52);
    cout<<"Input normalized";
    snakecolor=30;
}
void teleport(int nx,int ny)
{
    gotoxy(headpos_x,headpos_y);
    textColor(snakecolor);
    cout<<sn;
    int x=nx,y=ny;
    if (nx==-1)
    {
        x=rand()%(mapH-4)+3;
        y=rand()%(mapW-4)+3;
        while (playground[x][y])
        {
            x=rand()%(mapH-4)+3;
            y=rand()%(mapW-4)+3;
        }
    }
    int nheadpos_x=x;
    int nheadpos_y=y;
    //snake.push(ii(nheadpos_x,nheadpos_y));
    snake[++R]=ii(nheadpos_x,nheadpos_y);
    gotoxy(nheadpos_x,nheadpos_y);
    textColor(snakecolor);
    cout<<head;
    gotoxy(22,1 );
    headpos_x=nheadpos_x;
    headpos_y=nheadpos_y;
    playground[headpos_x][headpos_y]=1;
    clear_notification();
    textColor(defaultcolor+1);
    gotoxy(10,52);
    if (nx==-1)
    cout<<"Teleported !";
}

void eat_specialfood()
{
    score+=10;
    int luck=rand()%6;
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

void generate_snake(int x,int y)
{
    //while (snake.size()) snake.pop();
    L=1;
    R=0;
    textColor(snakecolor);
    length=3;
    headpos_x=x;
    headpos_y=y;
    playground[headpos_x+2][headpos_y]=playground[headpos_x+1][headpos_y]=playground[headpos_x][headpos_y]=1;
    //snake.push(ii(headpos_x+2,headpos_y));
    snake[++R]=ii(headpos_x+2,headpos_y);
    gotoxy(headpos_x+2,headpos_y);
    cout<<sn;
    //snake.push(ii(headpos_x+1,headpos_y));
    snake[++R]=ii(headpos_x+1,headpos_y);
    gotoxy(headpos_x+1,headpos_y);
    cout<<sn;
    //snake.push(ii(headpos_x,headpos_y));
    snake[++R]=ii(headpos_x,headpos_y);
    gotoxy(headpos_x,headpos_y);
    cout<<head;
    textColor(defaultcolor);
}
void init(int Map)
{
    if (Map==3)
    {
        system("cls");
        textColor(defaultcolor);
        cout<<"Just kidding, there isn't Stage 4, You cleared the game! Congratulation\n";
        cout<<"Your final score is "<<score<<"\n";
        if (score>bscore)
        {
            cout<<" NEW RECORD: "<<score<<"\n";
            bscore=score;
        }
        else
        cout<<"Best score: "<<bscore<<"\n\n";
        cout<<"Credit\n\n";
        cout<<"Me - Do everything lol\n";
        cout<<"Thank you for playing my game\n";
        cout<<"Press [Enter] to exit";
        fo<<bscore;
        while (1)
        {
            if (getch()==13)
                exit(0);
        }
    }
    food=3;
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
        playground[1][12]=playground[1][13]=playground[20][12]=playground[20][13]=playground[1][37]=playground[1][38]
                                            =playground[20][37]=playground[20][38]=playground[5][1]=playground[6][1]=playground[5][50]=playground[6][50]
                                                    =playground[15][1]=playground[16][1]=playground[15][50]=playground[16][50]=10;
        playground[11][12]=playground[11][13]=playground[11][37]=playground[11][38]=playground[5][25]=playground[6][25]=0;
        playground[15][25]=playground[16][25]=0;
    }
    dir=1;
    printPlayground();
    generate_food(1,playground);
    switch (Map)
    {
    case 0:
        generate_snake(mapH/2,mapW/2);
        break;
    case 1:
        generate_snake(10,40);
        break;
    case 2:
        generate_snake(17,4);
        break;
    }
}
void changedir()
{
    char ndir=getch();
    if (ndir=='p')
    {
        gotoxy(13,52);
        textColor(defaultcolor);
        cout<<"Game pause ! Press anykey to resume";
        gotoxy(13,52);
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
    textColor(snakecolor);
    cout<<sn;
    int nheadpos_x=headpos_x+movex[dir];
    int nheadpos_y=headpos_y+movey[dir];
    if (playground[nheadpos_x][nheadpos_y]==10)
    {
        if (nheadpos_x==1)
            teleport(19,nheadpos_y);
        if (nheadpos_x==20)
            teleport(2,nheadpos_y);
        if (nheadpos_y==1)
            teleport(nheadpos_x,49);
        if (nheadpos_y==50)
            teleport(nheadpos_x,2);
        ii last=snake[L++];
        playground[last.first][last.second]=0;
        gotoxy(last.first,last.second);
        textColor(backgroundcolor);
        cout<<" ";
        return;
    }
    //snake.push(ii(nheadpos_x,nheadpos_y));
    snake[++R]=ii(nheadpos_x,nheadpos_y);
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
        generate_food(1,playground);
    }
    else if (playground[nheadpos_x][nheadpos_y]==-4)
    {
        if (toxic[0].first)
            clear_toxic();
        if (invi)
            reverse_invi();
        length++;
        score++;
        food++;
        if (food%3==0)
        {
            if (inputR)
                rreverse_input();
            generate_special_food();
        }
    }
    else
    {
        ii last=snake[L++];
        playground[last.first][last.second]=0;
        gotoxy(last.first,last.second);
        textColor(backgroundcolor);
        cout<<" ";
        if (playground[nheadpos_x][nheadpos_y]!=0)
        {
            if (playground[nheadpos_x][nheadpos_y]!=10)
                start=0;
        }
    }
    gotoxy(22,1 );
    headpos_x=nheadpos_x;
    headpos_y=nheadpos_y;
    playground[headpos_x][headpos_y]=1;
    if (tlp)
    {
        teleport(-1,-1);
        tlp=0;
    }
    if (invi)
    {
        sn=219;
        textColor(snakecolor);
        gotoxy(snake[inviR].first,snake[inviR].second);
        inviR++;
        cout<<sn;
        sn=0;
    }
}
/*void updateSnake()
{
    for (int i=1; i<=mapH; i++)
        for (int j=1; j<=mapW; j++)
            if (playground[i][j]>0) playground[i][j]--;
}*/

void special_food_init()
{
    if (invi)
        reverse_invi();
    if (inputR)
        rreverse_input();
    sf_x=sf_y=0;
    invi=0;
    inviR=0;
    inputR=0;
    tlp=0;
    toxic[0].first=0;
}
void run()
{
    while (1)
    {
        special_food_init();
        system("cls");
        init(Map);
        gotoxy(22,14);
        cout<<"Press [Enter] to start";
        gotoxy(24,14);
        cout<<"Stage "<<Map+1;
        while (1)
        {
            if (getch()==13)
                break;
        }
        start=1;
        while (start)
        {
            gotoxy(19,52);
            textColor(defaultcolor);
            cout<<"Reach ";
            textColor(13);
            cout<<require[Map];
            textColor(defaultcolor);
            cout<<" to move to next map !";
            if (kbhit())
                changedir();
            move();
            textColor(defaultcolor);
            gotoxy(22,54);
            if (score>=require[Map])
            {
                Map++;
                break;
            }
            cout<<"Your score: ";
            textColor(13);
            cout<<score;
            textColor(defaultcolor);
            //system("cls");
            //updateSnake();
            //printPlayground();
            if (dir==2||dir==4)
                Sleep(1000-speed);
            else
                Sleep(5*(1000-speed)/2);
        }
        if (!start) break;
    }
}
void choose_speed()
{
    bool legal=0;
    while (!legal)
    {
        system("cls");
        //init(Map);
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
}
int main()
{
    fi>>bscore;
    srand(time(NULL));
    // cout<<"\";
    system("MODE 100,30");
    textColor(defaultcolor);
    //system("color 14");
    cout<<"n99dl's snake 3.0\n";
    cout<<"Use WASD to move the snake. Eat food to earn length\n";
    cout<<"And... enjoy the special food. Who know what you gonna get?\n";
    cout<<"\n";
    cout<<"Earn score to advance to next map. Eat special food give you bonus score !\n";
    cout<<"Enjoy the game !\n";
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
        score=0;
        Map=0;
        special_food_init();
        clear_notification();
        choose_speed();
        run();
        //system("cls");
        //clear_notification();
        textColor(defaultcolor);
        gotoxy(26,1);
        cout<<"Game over! Your final length is "<<length<<"\n";
        cout<<"Your score is "<<score<<"\n";
        if (score>bscore)
        {
            cout<<" NEW RECORD: "<<score<<"\n";
            bscore=score;
        }
        else
        cout<<"Best score: "<<bscore<<"\n";
        cout<<"Would you like to retry ? y/n?\n";
        while (1)
        {
            if (kbhit())
            {
                char tmp=getch();
                if (tmp=='n') break;
                if (tmp=='y')
                {
                    start=1;
                    break;
                }
            }
        }
    }
    fo<<bscore;
    return 0;
}

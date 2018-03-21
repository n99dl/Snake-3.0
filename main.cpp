#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "Snake2-0.hpp"
#include "drawing.hpp"
#include "snake.hpp"
#include "others.hpp"
#include "Snake2-1.hpp"
#include "Snake2-2.hpp"

using namespace std;

ifstream fi;
ofstream fo;

typedef pair<int,int> ii;

int mapW=50;
int mapH=20;
int playground[201][201];
// Snake properties
bool start=0;
int speed;
SNAKE snake;

int bscore=0;
int movex[]= {0,-1,0,1,0};
int movey[]= {0,0,1,0,-1};
int score;
int food;
int require[]= {50,150,1000};
//Snake 2.2
int Map=0;
ii sf;
ii toxic[30+1];
bool inputR=0;
bool tlp=0;
int dir;

pair<int,int> eat_specialfood()
{
    srand(time(NULL));
    score+=10;
    int luck=rand()%6;
    switch (luck)
    {
    case 0:
        half_size(snake,playground);
        break;
    case 1:
        food_spam(playground,mapW,mapH);
        break;
    case 2:
        invisible(snake);
        break;
    case 3:
        toxic_spam(toxic,playground,mapW,mapH);
        break;
    case 4:
        inputR=reverse_input(snake,movex,movey,dir);
        break;
    case 5:
        tlp=1;
        break;
    }
    return make_pair(0,0);
}

void init(int Map)
{
    if (Map==3)
    {
        system("cls");
        textColor(10);
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
    setup_map(Map,mapH,mapW,playground);
    printPlayground(playground,mapH,mapW);
    generate_food(1,playground,mapW,mapH);
    switch (Map)
    {
    case 0:
        snake.generate_snake(mapH/2,mapW/2,playground);
        break;
    case 1:
        snake.generate_snake(10,40,playground);
        break;
    case 2:
        snake.generate_snake(17,4,playground);
        break;
    }
}

void move()
{
    ii temp=snake.getHead();
    int nheadpos_x=temp.first+movex[dir];;
    int nheadpos_y=temp.second+movey[dir];
    if (playground[nheadpos_x][nheadpos_y]==10)
    {
        if (nheadpos_x==1)
            nheadpos_x=19;
        if (nheadpos_x==20)
            nheadpos_x=2;
        if (nheadpos_y==1)
            nheadpos_y=49;
        if (nheadpos_y==50)
            nheadpos_y=2;
    }
    snake.MoveHead(nheadpos_x,nheadpos_y);
    if (playground[nheadpos_x][nheadpos_y]==-3)
        sf=eat_specialfood();
    else if (playground[nheadpos_x][nheadpos_y]==-2)
    {
        if (snake.inviR)
            reverse_invi(snake);
        if (toxic[0].first)
            clear_toxic(toxic,playground);
        if (sf.first)
        {
            draw(sf.first,sf.second,17,' ');
            playground[sf.first][sf.second]=0;
            sf=ii(0,0);
        }
        score++;
        food++;
        if (food%3==0)
        {
            if (inputR)
                inputR=rreverse_input(snake,movex,movey,dir);
            generate_special_food(playground,mapW,mapH);
        }
        generate_food(1,playground,mapW,mapH);
    }
    else if (playground[nheadpos_x][nheadpos_y]==-4)
    {
        if (snake.inviR)
            reverse_invi(snake);
        if (toxic[0].first)
            clear_toxic(toxic,playground);
        score++;
        food++;
        if (food%3==0)
            if (inputR)
                inputR=rreverse_input(snake,movex,movey,dir);
    }
    else
    {
        snake.PopTail(playground);
        if (playground[nheadpos_x][nheadpos_y]!=0)
        {
            if (playground[nheadpos_x][nheadpos_y]!=10)
                start=0;
        }
    }
    gotoxy(22,1);
    playground[nheadpos_x][nheadpos_y]=1;
    if (tlp)
    {
        teleport(snake,playground,mapH,mapW);
        tlp=0;
    }
    if (snake.inviR)
    {
        char tmp=219;
        draw(snake.coor[snake.inviR].first,snake.coor[snake.inviR++].second,snake.get_snakecolor(),tmp);
    }
}

void special_food_init()
{
    if (snake.inviR)
        reverse_invi(snake);
    if (inputR)
        inputR=rreverse_input(snake,movex,movey,dir);
    sf=ii(0,0);
    tlp=0;
    toxic[0].first=0;
    dir=1;
}
void run()
{
    while (1)
    {
        special_food_init();
        system("cls");
        init(Map);
        gotoxy(22,14);
        draw(22,14,10,"Press [Enter] to start");
        draw(24,14,10,"Stage " + to_string(Map+1));
        while (1)
        {
            if (getch()==13)
                break;
        }
        start=1;
        while (start)
        {
            draw(19,52,10,"Reach ");
            textColor(13);
            cout<<require[Map];
            textColor(10);
            cout<<" to move to next map !";
            if (kbhit())
                changedir(dir);
            move();
            if (score>=require[Map])
            {
                Map++;
                break;
            }
            draw(22,54,10,"Your score: ");
            textColor(13);
            cout<<score;
            if (dir==2||dir==4)
                Sleep(1000-speed);
            else
                Sleep(5*(1000-speed)/2);
        }
        if (!start) break;
    }
}

int main()
{
    fi.open("highscore.txt");
    fi>>bscore;
    fi.close();
    srand(time(NULL));
    system("MODE 100,30");
    textColor(10);
    cout<<"n99dl's snake 3.0\n";
    cout<<"Use WASD or Arrow Key to move the snake. Eat food to earn length\n";
    cout<<"And... enjoy the special food. Who know what you gonna get?\n";
    cout<<"\n";
    cout<<"Earn score to advance to next map. Eat special food give you bonus score !\n";
    cout<<"Enjoy the game !\n";
    cout<<"Press [SPACE] to continue";
    while (1)
    {
        if (kbhit())
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
        clear_notification();
        speed=choose_speed();
        run();
        draw(26,1,10,"Game over! Your final length is " + to_string(snake.length) +"\n");
        cout<<"Your score is "<<score<<"\n";
        if (score>bscore)
        {
            cout<<" NEW RECORD: "<<score<<"\n";
            bscore=score;
        }
        else
            cout<<"Best score: "<<bscore<<"\n";
        fo.open("highscore.txt");
        fo<<bscore;
        fo.close();
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
    return 0;
}

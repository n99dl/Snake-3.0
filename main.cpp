#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "Snake2-0.hpp"                 ///First update : Setting up maps (3 maps), Print Playground and normal controls of the snake.
#include "drawing.hpp"                  ///Drawing functions and some simple interactions with console windows.
#include "snake.hpp"                    ///Snake Class: Managing snake's attribute, Snake's movement, and generating snake.
#include "others.hpp"                   ///Others function: to_String (number to string)
#include "Snake2-1.hpp"                 ///Second update : Adding Special foods, 5 effects (Half size, Food spams, Invisible Snake, Toxic spams, Reverse Input)
#include "Snake2-2.hpp"                 ///Third update : New feature of Special foods (Adding 1 new effects : Teleport )
#include "ColorDisplay.h"               ///ColorDisplay : Tool to draw playground (Creator : khoi~n.le). Modified : Add drawing vertical and horizontal line functions and fast init ColorCharacters.
#include "GUI.hpp"                      ///Graphic User Interface : Drawing Main menu and other notifications.

using namespace std;

ifstream fi;
ofstream fo;

const int MAP_WIDTH=50;
const int MAP_HEIGHT=20;
/// Managing what is on the playground
int playground[201][201];
/// Snake properties
bool start=0;
int speed;
SNAKE snake;

///Best score
int bscore=0;
///Moving Directions
int movex[]= {0,-1,0,1,0};
int movey[]= {0,0,1,0,-1};
int score;
int food;
int require[]= {50,150,1000};
///Snake 2.2
int Map=0;
COORDINATION sf;
COORDINATION toxic[30+1];
bool inputR=0;
bool tlp=0;
int dir;

/// Generating specials effect when eating special foods. Return new coordination for the special foods.
COORDINATION eat_specialfood()
{
    srand(time(NULL));
    score+=10;
    int luck=rand()%6;
    switch (luck)
    {
    case HALF_SIZE:
        half_size(snake,playground);
        break;
    case FOOD_SPAM:
        food_spam(playground,MAP_WIDTH,MAP_HEIGHT);
        break;
    case INVISIBLE:
        invisible(snake);
        break;
    case TOXIC_SPAM:
        toxic_spam(toxic,playground,MAP_WIDTH,MAP_HEIGHT);
        break;
    case REVERSE_INPUT:
        inputR=reverse_input(snake,movex,movey,dir);
        break;
    case TELEPORT:
        tlp=1;
        break;
    }
    return make_pair(0,0);
}

/// Initializing playground and Gameplay Interface

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
    setup_map(Map,MAP_HEIGHT,MAP_WIDTH,playground);
    printPlayground(playground,MAP_HEIGHT,MAP_WIDTH,Map);
    generate_food(1,playground,MAP_WIDTH,MAP_HEIGHT);
    switch (Map)
    {
    case PLAIN:
        snake.generate_snake(MAP_HEIGHT/2,MAP_WIDTH/2,playground);
        break;
    case MIDVOID:
        snake.generate_snake(10,40,playground);
        break;
    case MATRIX:
        snake.generate_snake(17,4,playground);
        break;
    }
}

/// Moving the snake to the directed direction and interact with other objects on the map

void move()
{
    COORDINATION temp=snake.getHead();
    int nheadpos_x=temp.first+movex[dir];;
    int nheadpos_y=temp.second+movey[dir];
    if (playground[nheadpos_x][nheadpos_y]==10)
    {
        if (nheadpos_x==1)
            nheadpos_x=19;
        else if (nheadpos_x==20)
            nheadpos_x=2;
        else if (nheadpos_y==1)
            nheadpos_y=49;
        else if (nheadpos_y==50)
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
            sf=COORDINATION(0,0);
        }
        score++;
        food++;
        if (food%3==0)
        {
            if (inputR)
                inputR=rreverse_input(snake,movex,movey,dir);
            //if (!sf.first)
            sf=generate_special_food(playground,MAP_WIDTH,MAP_HEIGHT);
        }
        generate_food(1,playground,MAP_WIDTH,MAP_HEIGHT);
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
            if (playground[nheadpos_x][nheadpos_y]!=10&&playground[nheadpos_x][nheadpos_y]!=-144)
                start=0;
        }
    }
    gotoxy(22,1);
    playground[nheadpos_x][nheadpos_y]=1;
    if (tlp)
    {
        teleport(snake,playground,MAP_HEIGHT,MAP_WIDTH);
        tlp=0;
    }
    if (snake.inviR)
    {
        char tmp=219;
        draw(snake.coor[snake.inviR].first,snake.coor[snake.inviR].second,snake.get_snakecolor(),tmp);
        snake.inviR++;
    }
}

/// Initializing special foods attribute

void special_food_init()
{
    if (snake.inviR)
        reverse_invi(snake);
    if (inputR)
        inputR=rreverse_input(snake,movex,movey,dir);
    sf=COORDINATION(0,0);
    tlp=0;
    toxic[0].first=0;
    dir=1;
}

/// Play the game step by step
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
            draw(23,54,19,to_string(snake.L)+"   "+to_string(snake.R)+"    "+to_string(snake.length));
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
    /// Opening file to read local high score
    fi.open("highscore.txt");
    fi>>bscore;
    fi.close();
    /// Closing file
    srand(time(NULL));
    system("MODE 100,30");
    bool running = 1;
    while (running)
    {
        printMainMenu();
        start=0;
        while (!start)
        {
            char cmd=' ';
            if (kbhit())
                cmd=getch();
            switch (cmd)
            {
            case PLAY:
                start=1;
                break;
            case HTP:
                printHowtoPlay();
                break;
            case HC:
                printHighScore(bscore);
                break;
            case QUIT:
                exit(0);
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
            /// Opening file to write new local high score
            fo.open("highscore.txt");
            fo<<bscore;
            fo.close();
            /// Close file
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
    }
    return 0;
}

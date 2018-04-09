#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "others.hpp"
#include "drawing.hpp"
#include "snake.hpp"
#include "Snake2-0.hpp"

using namespace std;

void half_size(SNAKE &snake,int playground[][201])
{
    int length=snake.length;
    while (snake.length>length/2)
    snake.PopTail(playground);
    snake.length=length;
    clear_notification();
    draw(10,52,11,"Half size !!");
}

void food_spam(int playground[][201],int mapW,int mapH)
{
    generate_food(0,playground,mapW,mapH);
    generate_food(0,playground,mapW,mapH);
    generate_food(0,playground,mapW,mapH);
    generate_food(0,playground,mapW,mapH);
    generate_food(0,playground,mapW,mapH);
    clear_notification();
    draw(10,52,11,"Food spam !!");
}
void invisible(SNAKE &snake)
{
    clear_notification();
    draw(10,52,11,"Invisible snake (eat food to reverse)");
    snake.set_head_symbol(' ');
    snake.set_sn_symbol(' ');
    for (int i=snake.L+(snake.R-snake.L+1)/2; i<=snake.R; i++)
    {
        ii tmp1;
        tmp1=snake.coor[i];
        draw(tmp1.first,tmp1.second,17,' ');
    }
    snake.inviR=snake.L+(snake.R-snake.L+1)/2-1;
}

/// Reverse invisible
void reverse_invi(SNAKE &snake)
{
    snake.inviR=0;
    snake.set_sn_symbol(219);
    snake.set_head_symbol(233);
    for (int i=snake.L; i<snake.R; i++)
    draw(snake.coor[i].first,snake.coor[i].second,snake.get_snakecolor(),snake.get_sn_symbol());
    draw(snake.coor[snake.R].first,snake.coor[snake.R].second,snake.get_snakecolor(),snake.get_head_symbol());
    clear_notification();
    draw(10,52,11,"Invisible reversed !!");
}

/// Generating new special food , returning the Coordination
COORDINATION generate_special_food(int playground[][201],int mapW,int mapH)
{
    int sf_x=rand()%(mapH-2)+2;
    int sf_y=rand()%(mapW-2)+2;
    while (playground[sf_x][sf_y])
    {
        sf_x=rand()%(mapH-2)+2;
        sf_y=rand()%(mapW-2)+2;
    }
    playground[sf_x][sf_y]=-3;
    draw(sf_x,sf_y,29,'X');
    return make_pair(sf_x,sf_y);
}

void toxic_spam(pair<int,int> toxic[30],int playground[][201],int mapW,int mapH)
{
    toxic[0].first=1;
    for (int i=1; i<=30; i++)
        toxic[i]=generate_food(-1,playground,mapW,mapH);
    clear_notification();
    gotoxy(10,52);
    textColor(10+1);
    cout<<"Toxic spam !! (Eat food to clear toxic)";
}

/// Clear toxic when food is eaten

void clear_toxic(pair<int,int> toxic[30],int playground[][201])
{
    for (int i=1; i<=30; i++)
    {
        draw(toxic[i].first,toxic[i].second,17,' ');
        playground[toxic[i].first][toxic[i].second]=0;
    }
    toxic[0].first=0;
    clear_notification();
    draw(10,52,11,"Toxic cleared !!");
}
bool reverse_input(SNAKE &snake,int movex[],int movey[],int &dir)
{
    clear_notification();
    draw(10,52,11,"Input reversed (Eat 3 foods to set it back)");
    swap(movex[1],movex[3]);
    swap(movey[1],movey[3]);
    swap(movex[2],movex[4]);
    swap(movey[2],movey[4]);
    dir=dir+2;
    if (dir>4) dir-=4;
    snake.set_snakecolor(26);
    return 1;
}

/// Reverse Reverse Input (Normalizing)
bool rreverse_input(SNAKE &snake,int movex[],int movey[],int &dir)
{
    clear_notification();
    draw(10,52,11,"Input normalized");
    swap(movex[1],movex[3]);
    swap(movey[1],movey[3]);
    swap(movex[2],movex[4]);
    swap(movey[2],movey[4]);
    dir=dir+2;
    if (dir>4) dir-=4;
    snake.set_snakecolor(30);
    return 0;
}

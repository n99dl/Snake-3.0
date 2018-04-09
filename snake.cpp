#include "snake.hpp"
#include "drawing.hpp"
#include "others.hpp"
#include <iostream>

using namespace std;

///Generating a 3-length snake with head at (x,y), body at (x+1,y) (x+2,y)
void SNAKE::generate_snake(int x,int y,int playground[][201])
{
    inviR=0;
    sn_symbol=219;
    head_symbol=233;
    snakecolor=30;
    L=1;
    R=0;
    textColor(snakecolor);
    length=3;
    playground[x+2][y]=playground[x+1][y]=playground[x][y]=1;
    coor[++R]=make_pair(x+2,y);
    gotoxy(x+2,y);
    cout<<sn_symbol;
    coor[++R]=make_pair(x+1,y);
    gotoxy(x+1,y);
    cout<<sn_symbol;
    coor[++R]=make_pair(x,y);
    gotoxy(x,y);
    cout<<head_symbol;
    textColor(10);
}

/// Anti overflow snake queue
void SNAKE::MoveQueue()
{
    for (int i=L;i<=R;i++)
        coor[i-100]=coor[i];
    L-=100;
    R-=100;
    if (inviR) inviR-=100;
}
/// Create new head of the snack at the new position
void SNAKE::MoveHead(int x,int y)
{
    if (L>100)
    MoveQueue();
    draw(coor[R].first,coor[R].second,snakecolor,sn_symbol);
    coor[++R]=make_pair(x,y);
    draw(coor[R].first,coor[R].second,snakecolor,head_symbol);
    length++;
}
/// Delete the tail
bool SNAKE::PopTail(int playground[][201])
{
    if (R<L)
        return 0;
    COORDINATION last=coor[L++];
    playground[last.first][last.second]=0;
    draw(last.first,last.second,17,' ');
    length--;
    return 1;
}
/// Get head's position
COORDINATION SNAKE::getHead()
{
    return coor[R];
}

int SNAKE::get_snakecolor()
{
    return snakecolor;
}
void SNAKE::set_snakecolor(int color)
{
    snakecolor=color;
}
char SNAKE::get_sn_symbol()
{
    return sn_symbol;
}
char SNAKE::get_head_symbol()
{
    return head_symbol;
}
void SNAKE::set_sn_symbol(char symbol)
{
    sn_symbol=symbol;
}
void SNAKE::set_head_symbol(char symbol)
{
    head_symbol=symbol;
}

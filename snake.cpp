#include "snake.hpp"
#include "drawing.hpp"
#include <iostream>

using namespace std;

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
void SNAKE::MoveHead(int x,int y)
{
    draw(coor[R].first,coor[R].second,snakecolor,sn_symbol);
    coor[++R]=make_pair(x,y);
    draw(coor[R].first,coor[R].second,snakecolor,head_symbol);
    length++;
}
bool SNAKE::PopTail(int playground[][201])
{
    if (R<L)
        return 0;
    pair<int,int> last=coor[L++];
    playground[last.first][last.second]=0;
    draw(last.first,last.second,17,' ');
    length--;
    return 1;
}
pair<int,int> SNAKE::getHead()
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
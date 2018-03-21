#ifndef SNAKE_HPP_INCLUDED
#define SNAKE_HPP_INCLUDED



#endif // SNAKE_HPP_INCLUDED

#include <algorithm>


class SNAKE
{
private:
    int snakecolor;
    char head_symbol;
    char sn_symbol;
public:
    int inviR;
    int L,R;
    int length;
    std::pair<int,int> coor[1000];
    void generate_snake(int x,int y,int playground[][201]);
    std::pair<int,int> getHead();
    void MoveHead(int x,int y);
    bool PopTail(int playground[][201]);
    int get_snakecolor();
    void set_snakecolor(int color);
    char get_sn_symbol();
    char get_head_symbol();
    void set_sn_symbol(char symbol);
    void set_head_symbol(char symbol);
};
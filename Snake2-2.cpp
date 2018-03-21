#include <cstdlib>
#include "snake.hpp"
#include "drawing.hpp"

void teleport(SNAKE &snake,int playground[][201],int mapH,int mapW)
{
    int x=0,y=0;
    x=rand()%(mapH-4)+3;
    y=rand()%(mapW-4)+3;
    while (playground[x][y])
    {
        x=rand()%(mapH-4)+3;
        y=rand()%(mapW-4)+3;
    }
    snake.MoveHead(x,y);
    clear_notification();
    draw(10,52,11,"Teleported !");
}

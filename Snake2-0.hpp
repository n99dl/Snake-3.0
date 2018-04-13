#ifndef SNAKE2-0_HPP_INCLUDED
#define SNAKE2-0_HPP_INCLUDED



#endif // SNAKE2-0_HPP_INCLUDED

#define PLAIN 0
#define MIDVOID 1
#define MATRIX 2
#define UP_ARROW 72
#define RIGHT_ARROW 77
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

using namespace std;

typedef pair<int,int> ii;

void printPlayground(int playground[][201],int mapH,int mapW,int Map);
void setup_map(int Map,int mapH,int mapW,int playground[][201]);
ii generate_food(int regenerate,int playground[][201],int mapW,int mapH);
int choose_speed();
void changedir(int &dir);




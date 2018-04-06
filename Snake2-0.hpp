#ifndef SNAKE2-0_HPP_INCLUDED
#define SNAKE2-0_HPP_INCLUDED



#endif // SNAKE2-0_HPP_INCLUDED

#define PLAIN 0
#define VOID 1
#define MATRIX 2

using namespace std;

typedef pair<int,int> ii;

void printPlayground(int playground[][201],int mapH,int mapW,int Map);
void setup_map(int Map,int mapH,int mapW,int playground[][201]);
ii generate_food(int regenerate,int playground[][201],int mapW,int mapH);
int choose_speed();
void changedir(int &dir);




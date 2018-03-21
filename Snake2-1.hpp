#ifndef SNAKE2-1_HPP_INCLUDED
#define SNAKE2-1_HPP_INCLUDED



#endif // SNAKE2-1_HPP_INCLUDED

using namespace std;

void half_size(SNAKE &snake,int playgroug[][201]);
void food_spam(int playground[][201],int mapW,int mapH);
void invisible(SNAKE &snake);
void reverse_invi(SNAKE &snake);
void toxic_spam(pair<int,int> toxic[30],int playground[][201],int mapW,int mapH);
void clear_toxic(pair<int,int> toxic[30],int playground[][201]);
bool reverse_input(SNAKE &snake,int movex[],int movey[],int &dir);
bool rreverse_input(SNAKE &snake,int movex[],int movey[],int &dir);
pair<int,int> generate_special_food(int playground[][201],int mapW,int mapH);

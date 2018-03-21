#ifndef DRAWING_HPP_INCLUDED
#define DRAWING_HPP_INCLUDED



#endif // DRAWING_HPP_INCLUDED
#include <string>

void gotoxy(int y, int x);
void textColor(int x);
void draw(int x,int y,int color,std::string text);
void draw(int x,int y,int color,char symbol);
void clear_notification();

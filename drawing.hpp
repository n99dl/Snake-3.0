#ifndef DRAWING_HPP_INCLUDED
#define DRAWING_HPP_INCLUDED



#endif // DRAWING_HPP_INCLUDED
#include <string>
#include <vector>
#include "ColorDisplay.h"

/// Creating empty image with certain height and color
struct IMAGE{
    std::vector<std::string> image;
    int color=BLACK;
    int height=0;
    IMAGE(int _height,int _color)
    {
        height=_height;
        color=_color;
        while (_height-->0)
            image.push_back("");
    }
};

void gotoxy(int y, int x);
void textColor(int x);
void draw(int x,int y,int color,std::string text);
void draw(int x,int y,int color,char symbol);
void clear_notification();
void displayImage(IMAGE image,int x,int y);

#ifndef _COLORDISPLAY_H_INCLUDED
#define _COLORDISPLAY_H_INCLUDED

#include <windows.h>
#include <vector>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

///  Creating a ColorCharacter with color and the symbol
struct ColorCharacter
{
    short color;
    unsigned char character;
    ColorCharacter (unsigned char _character, short _color);
};

/// Create an empty Image (UNUSED)
/*struct Image {
    std::vector < std::vector < ColorCharacter > > image;
    Image( int row , int column )
    {
        ColorCharacter colorcharacter(' ',BLACK);// colorcharacter.color = BLACK; colorcharacter.character = ' ';
        for (unsigned short i = 0; i < row; i++)
        {
            std::vector < ColorCharacter > temp;
            for (unsigned short j = 0; j < column; j++)
            {
                temp.push_back(colorcharacter);
            }
            image.push_back(temp);
        }
    }
};*/

/// Playground
class ColorDisplay
{
    public:
        ColorDisplay( short _xScreeSize , short _yScreenSize , COORD _origin );
        void setColorCharacterAtPosition( const ColorCharacter & colorchar , const COORD & position );
        void setColorCharacterAtPosition( const ColorCharacter & colorchar , short xPosition , short yPosition );
        //void displayImage(const Image & img, const COORD & position);
        void resetDisplay();
        void setBackGroundColor(short color);
        void drawingLineHorizontal(int x,int y,int length);
        void drawingLineVertical(int x,int y,int length);
    private:
        HANDLE outConsole;
        COORD origin;
        short xScreenSize, yScreenSize;
        short backGroundColor = BLACK;
};

#endif // COLORDISPLAY_H_INCLUDED

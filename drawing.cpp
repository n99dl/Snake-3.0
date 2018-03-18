#include <windows.h>
#include <conio.h>

void gotoxy(int y, int x)
{
    x--;
    y--;
    COORD cor;
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

void textColor(int x)//Xac dinh mau cua chu
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

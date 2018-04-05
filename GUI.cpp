#include <iostream>
#include <bits/stdc++.h>
#include "drawing.hpp"
#include "ColorDisplay.h"

using namespace std;

void printMainMenu()
{
    string snake[]={"      _  _  _  _                                  _                          ",
                    "    _(_)(_)(_)(_)_                               (_)                         ",
                    "   (_)          (_) _  _  _  _      _  _  _      (_)     _  _  _  _  _       ",
                    "   (_)_  _  _  _   (_)(_)(_)(_)_   (_)(_)(_) _   (_)   _(_) (_)(_)(_)(_)_    ",
                    "     (_)(_)(_)(_)_ (_)        (_)   _  _  _ (_)  (_) _(_)  (_) _  _  _ (_)   ",
                    "    _           (_)(_)        (_) _(_)(_)(_)(_)  (_)(_)_   (_)(_)(_)(_)(_)   ",
                    "   (_)_  _  _  _(_)(_)        (_)(_)_  _  _ (_)_ (_)  (_)_ (_)_  _  _  _     ",
                    "     (_)(_)(_)(_)  (_)        (_)  (_)(_)(_)  (_)(_)    (_) (_)(_)(_)(_)     "};

    for (int i=0;i<8;i++)
    {
        textColor(BLUE*16+LIGHT_GREEN);
        cout<<snake[i]<<"\n";
    }
     textColor(BLUE*16+LIGHT_GREEN);
    cout<<"                                                                             \n                                                                             \n";
}


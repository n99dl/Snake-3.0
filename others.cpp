
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "drawing.hpp"

using namespace std;

std::string to_string( int n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

int getHighscore()
{
    ifstream fi;
    int tmp;
    /// Opening file to read local high score
    fi.open("highscore.txt");
    fi>>tmp;
    fi.close();
    return tmp;
    /// Closing file
}

void modHighscore(int& highscore,int score)
{
    draw(27,2,10,"Your score is "+to_string(score));
    if (score>highscore)
    {
        cout<<" NEW RECORD: "<<score<<"\n";
        draw(28,2,10," NEW RECORD: "+to_string(score));
        highscore=score;
    }
    else
        draw(28,2,10,"Best score: "+to_string(highscore));
    /// Opening file to write new local high score
    ofstream fo;
    fo.open("highscore.txt");
    fo<<highscore;
    fo.close();
}

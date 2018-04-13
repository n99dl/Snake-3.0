#ifndef OTHERS_HPP_INCLUDED
#define OTHERS_HPP_INCLUDED



#endif // OTHERS_HPP_INCLUDED

#include <string>
#include <algorithm>

#define SPACE 32
#define ENTER 13
/// Pair of int as coordination
typedef std::pair<int,int> COORDINATION;

std::string to_string( int n );
int getHighscore();
void modHighscore(int& highscore,int score);


#include <string>
#include <sstream>

std::string to_string( int n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

#include <iostream>
#include <string>
#include "formatter_ex.h"
#include "solver.h"
#include <sstream>

namespace patch
{
template < typename T > std::string to_string( const T& n )
	{
	std::ostringstream stm ;
	stm « n ;
	return stm.str() ;
	}
}

int main()
{
    float a = 0;
    float b = 0;
    float c = 0;

    std::cin >> a >> b >> c;

    float x1 = 0;
    float x2 = 0;

    try
    {
        solve(a, b, c, x1, x2);

        formatter(std::cout, "x1 = " + patch::to_string(x1));
        formatter(std::cout, "x2 = " + patch::to_string(x2));
    }
    catch (const std::logic_error& ex)
    {
        formatter(std::cout, ex.what());
    }

    return 0;
}

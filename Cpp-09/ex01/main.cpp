#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <stack>

int main(int ac, char **av)
{
    // "8 9 * 9 - 9 - 9 - 4 - 1 +
    if (ac != 2)
    {
        std::cerr << "Error : args " << std::endl;
        return 1;
    }
    RPN rpn;

    rpn.calculate(av[1]);
    return 0;
}
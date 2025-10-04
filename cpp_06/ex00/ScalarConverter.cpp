
#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iomanip>
#include <climits>

ScalarConverter::ScalarConverter(){};
ScalarConverter::~ScalarConverter(){};
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &obj)
{
    (void)obj;
    return *this;
}
ScalarConverter::ScalarConverter(const ScalarConverter &obj)
{
    (void)obj;
}


void ScalarConverter::convert(const std::string &literal)
{   
    if (literal.empty()) {
        std::cout << "Error: Empty input" << std::endl;
        return;
    }
     double value;

    if (literal == "nan" || literal == "nanf")
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
        return;
    }
    else if (literal == "inf" || literal == "+inf" || literal == "inff" || literal == "+inff")
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: inff" << std::endl;
        std::cout << "double: inf" << std::endl;
        return;
    }
    else if (literal == "-inf" || literal == "-inff")
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
        return;
    }

    if (literal.length() == 1 && !std::isdigit(literal[0]))
        value = static_cast<double>(literal[0]);
    else
    {
        std::string modifeid_literal = literal;
        if (literal.find('.') != std::string::npos && literal[literal.length() - 1] == 'f' )
            modifeid_literal = literal.substr(0, literal.length() - 1);

        char *endptr;
        value = std::strtod(modifeid_literal.c_str(), &endptr);

        if (*endptr != '\0')
        {
            std::cout << "Error: Invalid input" << std::endl;
            return;
        }
    }

    if (value < CHAR_MIN || value > CHAR_MAX || std::isnan(value))
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<char>(value)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;

    if (value < INT_MIN || value > INT_MAX || std::isnan(value))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(value) << std::endl;

    std::cout << "float: " << std::fixed << std::setprecision(1)
              << static_cast<float>(value) << "f" << std::endl;

    std::cout << "double: " << std::fixed << std::setprecision(1)
              << value << std::endl;
}
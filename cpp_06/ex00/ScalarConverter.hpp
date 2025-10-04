#pragma once 


#include <string>
#include<iostream>

class ScalarConverter{
    ScalarConverter();
    ScalarConverter(const ScalarConverter &obj);
    ScalarConverter& operator=(const ScalarConverter &obj);
    ~ScalarConverter();
    public:
    static void convert(const std::string& literal);
};
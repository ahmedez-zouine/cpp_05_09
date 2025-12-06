#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <stack>

class  RPN
{

public:
     RPN();
     RPN(const RPN& other);
     RPN& operator=(const RPN& other);
    ~RPN();

    int calculate(std::string input);
    
};



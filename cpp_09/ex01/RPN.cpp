#include "RPN.hpp"
RPN::RPN() {
};
RPN::~RPN() {}

int RPN::calculate(std::string input)
{

    std::stringstream ss(input);
    std::string item;
    std::stack<int> stack;
    while (getline(ss, item, ' '))
    {
        if (item.length() > 1 || (item != "+" && item != "-" && item != "*" &&
                                  item != "/" && !isdigit(item[0])))
        {
            std::cerr << "Error input.\n";
            return 1;
        }

        if (isdigit(item[0]))
        {
            stack.push(item[0] - '0');
        }
        else
        {
            if (stack.size() < 2)
            {
                std::cerr << "Error: size should be at least 2\n";
                return 1;
            }

            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();

            int res;

            switch (item[0])
            {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
                break;
            case '/':
                if (b == 0)
                {
                    std::cerr << "Error : you cant divid on 0\n";
                    return 1;
                }
                res = a / b;
                break;
            }
            stack.push(res);
        }
    }
    if (stack.size() != 1)
    {
        std::cerr << "Error \n";
        return 1;
    }

    std::cout << "result is " << stack.top() << std::endl;

    return 0;
}
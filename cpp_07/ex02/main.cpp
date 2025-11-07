#include <iostream>
#include "Array.hpp"


int main()
{
    Array<int> arr(5);
    for (unsigned int i = 0; i < arr.size(); ++i)
    {
        arr[i] = i * 10;
    }
    printElement(arr);
    std::cout << "After modifying element at index 0:" << std::endl;

    try
    {
        arr[0] = 1337; // This should work fine
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << e.what() << std::endl;
    }
    printElement<int>(arr);

    return 0;
}
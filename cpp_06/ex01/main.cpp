#include "Serializer.hpp"
#include <iostream>
int main()
{

    Data originalData;
    originalData.i = 42;

    std::cout << "Original pointer: " << &originalData << std::endl;
    std::cout << "Original value: " << originalData.i << std::endl;

    uintptr_t serialized = Serializer::serialize(&originalData);
    std::cout << "Serialized value: " << serialized << std::endl;

    Data *deserialized = Serializer::deserialize(serialized);
    std::cout << "Deserialized pointer: " << deserialized << std::endl;
    std::cout << "Deserialized value: " << deserialized->i << std::endl;

    if (deserialized == &originalData)
        std::cout << "SUCCESS" << std::endl;
    else
        std::cout << "ERROR" << std::endl;

    deserialized->i = 99;
    std::cout << "Modified value through deserialized pointer: " << deserialized->i << std::endl;
    std::cout << "Original object's value after modification: " << originalData.i << std::endl;

    return 0;
}

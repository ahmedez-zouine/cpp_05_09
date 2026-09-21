#include "easyfind.hpp"
#include <vector>
#include <list>
#include <deque>
#include <iostream>

int main()
{
    std::cout << "=== EasyFind Tests ===" << std::endl << std::endl;

    // Test 1: Vector test
    std::cout << "Test 1: Vector container" << std::endl;
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);

    std::cout << "Vector: [10, 20, 30, 40, 50]" << std::endl;
    
    int result = easyfind(vec, 30);
    std::cout << "Search for 30: ";
    if (result != -1)
        std::cout << "Found at index " << result << std::endl;
    else
        std::cout << "Not found" << std::endl;

    result = easyfind(vec, 99);
    std::cout << "Search for 99: ";
    if (result != -1)
        std::cout << "Found at index " << result << std::endl;
    else
        std::cout << "Not found" << std::endl;

    std::cout << std::endl;

    // Test 2: List test
    std::cout << "Test 2: List container" << std::endl;
    std::list<int> lst;
    lst.push_back(100);
    lst.push_back(200);
    lst.push_back(300);

    std::cout << "List: [100, 200, 300]" << std::endl;
    
    result = easyfind(lst, 200);
    std::cout << "Search for 200: ";
    if (result != -1)
        std::cout << "Found at index " << result << std::endl;
    else
        std::cout << "Not found" << std::endl;

    result = easyfind(lst, 150);
    std::cout << "Search for 150: ";
    if (result != -1)
        std::cout << "Found at index " << result << std::endl;
    else
        std::cout << "Not found" << std::endl;

    std::cout << std::endl;

    // Test 3: Deque test
    std::cout << "Test 3: Deque container" << std::endl;
    std::deque<int> deq;
    deq.push_back(5);
    deq.push_back(15);
    deq.push_back(25);
    deq.push_back(35);

    std::cout << "Deque: [5, 15, 25, 35]" << std::endl;
    
    result = easyfind(deq, 15);
    std::cout << "Search for 15: ";
    if (result != -1)
        std::cout << "Found at index " << result << std::endl;
    else
        std::cout << "Not found" << std::endl;

    result = easyfind(deq, 50);
    std::cout << "Search for 50: ";
    if (result != -1)
        std::cout << "Found at index " << result << std::endl;
    else
        std::cout << "Not found" << std::endl;

    std::cout << std::endl;

    // Test 4: Empty container
    std::cout << "Test 4: Empty container" << std::endl;
    std::vector<int> empty_vec;
    std::cout << "Empty vector: []" << std::endl;
    
    result = easyfind(empty_vec, 10);
    std::cout << "Search for 10: ";
    if (result != -1)
        std::cout << "Found at index " << result << std::endl;
    else
        std::cout << "Not found" << std::endl;

    std::cout << std::endl;
    std::cout << "=== All tests completed ===" << std::endl;

    return 0;
}
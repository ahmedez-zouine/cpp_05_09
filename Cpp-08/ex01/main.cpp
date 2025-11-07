#include "Span.hpp"
#include <iostream>

int main()
{
    std::cout << "=== Span Tests ===" << std::endl << std::endl;

    // Test 1: Basic functionality
    std::cout << "Test 1: Basic Span functionality" << std::endl;
    try {
        Span sp(5);
        std::cout << "Created Span with capacity 5" << std::endl;
        
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        
        std::cout << "Added numbers: [6, 3, 17, 9, 11]" << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;  // Should be 2 (9-11 or 6-3)
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;    // Should be 14 (17-3)
    }
    catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;

    // Test 2: Edge case - only 2 numbers
    std::cout << "Test 2: Minimum case (2 numbers)" << std::endl;
    try {
        Span sp2(2);
        sp2.addNumber(100);
        sp2.addNumber(50);
        
        std::cout << "Added numbers: [100, 50]" << std::endl;
        std::cout << "Shortest span: " << sp2.shortestSpan() << std::endl;  // Should be 50
        std::cout << "Longest span: " << sp2.longestSpan() << std::endl;    // Should be 50
    }
    catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;

    // Test 3: Error case - not enough numbers
    std::cout << "Test 3: Error handling - not enough numbers" << std::endl;
    try {
        Span sp3(5);
        sp3.addNumber(42);
        std::cout << "Added only 1 number" << std::endl;
        std::cout << "Trying to find shortest span..." << std::endl;
        sp3.shortestSpan();  // Should throw exception
    }
    catch (const std::exception &e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;

    // Test 4: Error case - span is full
    std::cout << "Test 4: Error handling - span is full" << std::endl;
    try {
        Span sp4(3);
        sp4.addNumber(1);
        sp4.addNumber(2);
        sp4.addNumber(3);
        std::cout << "Added 3 numbers to capacity-3 span" << std::endl;
        std::cout << "Trying to add 4th number..." << std::endl;
        sp4.addNumber(4);  // Should throw exception
    }
    catch (const std::exception &e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;

    // Test 5: addNumbers with iterator range
    std::cout << "Test 5: Adding multiple numbers with iterators" << std::endl;
    try {
        Span sp5(10);
        std::vector<int> numbers;
        numbers.push_back(1);
        numbers.push_back(5);
        numbers.push_back(3);
        numbers.push_back(9);
        numbers.push_back(7);
        
        std::cout << "Adding range [1, 5, 3, 9, 7] using addNumbers" << std::endl;
        sp5.addNumbers(numbers.begin(), numbers.end());
        
        std::cout << "Shortest span: " << sp5.shortestSpan() << std::endl;  // Should be 2 (5-3 or 7-9)
        std::cout << "Longest span: " << sp5.longestSpan() << std::endl;    // Should be 8 (9-1)
    }
    catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;

    // Test 6: Error case - too many numbers to add
    std::cout << "Test 6: Error handling - adding too many numbers" << std::endl;
    try {
        Span sp6(3);
        std::vector<int> tooMany;
        for (int i = 0; i < 5; i++)
            tooMany.push_back(i);
        
        std::cout << "Trying to add 5 numbers to capacity-3 span..." << std::endl;
        sp6.addNumbers(tooMany.begin(), tooMany.end());  // Should throw exception
    }
    catch (const std::exception &e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;

    // Test 7: Large numbers test
    std::cout << "Test 7: Large dataset test (1000 numbers)" << std::endl;
    try {
        Span bigSpan(1000);
        std::vector<int> bigNumbers;
        
        // Add numbers: 0, 2, 4, 6, 8, ... (even numbers)
        for (int i = 0; i < 1000; i++) {
            bigNumbers.push_back(i * 2);
        }
        
        bigSpan.addNumbers(bigNumbers.begin(), bigNumbers.end());
        std::cout << "Added 1000 even numbers [0, 2, 4, 6, ...]" << std::endl;
        std::cout << "Shortest span: " << bigSpan.shortestSpan() << std::endl;  // Should be 2
        std::cout << "Longest span: " << bigSpan.longestSpan() << std::endl;    // Should be 1998 (1998-0)
    }
    catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "=== All tests completed ===" << std::endl;

    return 0;
}
#include "MutantStack.hpp"
#include <iostream>
#include <list>
#include <stack>

int main()
{
    std::cout << "=== MutantStack Tests ===" << std::endl << std::endl;

    // Test 1: Basic stack operations
    std::cout << "Test 1: Basic stack operations" << std::endl;
    MutantStack<int> mstack;
    
    std::cout << "Pushing: 5, 17, 3, 737, 0" << std::endl;
    mstack.push(5);
    mstack.push(17);
    mstack.push(3);
    mstack.push(737);
    mstack.push(0);
    
    std::cout << "Top element: " << mstack.top() << std::endl;        // Should be 0
    std::cout << "Stack size: " << mstack.size() << std::endl;        // Should be 5
    
    mstack.pop();
    std::cout << "After pop - Top: " << mstack.top() << std::endl;    // Should be 737
    std::cout << "After pop - Size: " << mstack.size() << std::endl;  // Should be 4
    
    std::cout << std::endl;

    // Test 2: Iterator functionality (the magic!)
    std::cout << "Test 2: Iterator functionality" << std::endl;
    std::cout << "Stack contents (using iterators):" << std::endl;
    
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    
    int position = 0;
    while (it != ite) {
        std::cout << "Position " << position << ": " << *it << std::endl;
        ++it;
        ++position;
    }
    
    std::cout << std::endl;

    // Test 3: Comparison with std::list (should have same behavior)
    std::cout << "Test 3: Comparison with std::list" << std::endl;
    std::list<int> lst;
    lst.push_back(5);   // Same order as our stack (bottom to top)
    lst.push_back(17);
    lst.push_back(3);
    lst.push_back(737);
    
    std::cout << "List contents (should match stack iteration):" << std::endl;
    std::list<int>::iterator lit = lst.begin();
    position = 0;
    while (lit != lst.end()) {
        std::cout << "Position " << position << ": " << *lit << std::endl;
        ++lit;
        ++position;
    }
    
    std::cout << std::endl;

    // Test 4: Copy constructor and assignment
    std::cout << "Test 4: Copy operations" << std::endl;
    
    MutantStack<int> mstack2(mstack);  // Copy constructor
    std::cout << "Created copy of stack" << std::endl;
    std::cout << "Original stack size: " << mstack.size() << std::endl;
    std::cout << "Copied stack size: " << mstack2.size() << std::endl;
    std::cout << "Original top: " << mstack.top() << std::endl;
    std::cout << "Copied top: " << mstack2.top() << std::endl;
    
    MutantStack<int> mstack3;
    mstack3 = mstack;  // Assignment operator
    std::cout << "Assigned stack size: " << mstack3.size() << std::endl;
    std::cout << "Assigned top: " << mstack3.top() << std::endl;
    
    std::cout << std::endl;

    // Test 5: Different data types
    std::cout << "Test 5: String MutantStack" << std::endl;
    MutantStack<std::string> strStack;
    
    strStack.push("First");
    strStack.push("Second");
    strStack.push("Third");
    
    std::cout << "String stack contents:" << std::endl;
    MutantStack<std::string>::iterator strIt = strStack.begin();
    MutantStack<std::string>::iterator strEnd = strStack.end();
    
    while (strIt != strEnd) {
        std::cout << *strIt << std::endl;
        ++strIt;
    }
    
    std::cout << std::endl;

    // Test 6: Empty stack
    std::cout << "Test 6: Empty stack" << std::endl;
    MutantStack<int> emptyStack;
    
    std::cout << "Empty stack size: " << emptyStack.size() << std::endl;
    std::cout << "Empty stack begin == end? " << (emptyStack.begin() == emptyStack.end() ? "Yes" : "No") << std::endl;
    
    std::cout << std::endl;

    // Test 7: Single element
    std::cout << "Test 7: Single element stack" << std::endl;
    MutantStack<int> singleStack;
    singleStack.push(42);
    
    std::cout << "Single element: " << singleStack.top() << std::endl;
    std::cout << "Iterating single element:" << std::endl;
    for (MutantStack<int>::iterator it = singleStack.begin(); it != singleStack.end(); ++it) {
        std::cout << *it << std::endl;
    }
    
    std::cout << std::endl;

    // Test 8: Demonstrating it's still a stack
    std::cout << "Test 8: LIFO behavior demonstration" << std::endl;
    MutantStack<int> lifoTest;
    
    std::cout << "Pushing in order: 1, 2, 3, 4, 5" << std::endl;
    for (int i = 1; i <= 5; i++) {
        lifoTest.push(i);
    }
    
    std::cout << "Popping elements (LIFO - Last In, First Out):" << std::endl;
    while (!lifoTest.empty()) {
        std::cout << "Popped: " << lifoTest.top() << std::endl;
        lifoTest.pop();
    }
    
    std::cout << std::endl;
    std::cout << "=== All tests completed ===" << std::endl;
    std::cout << "MutantStack works like a stack BUT can also be iterated!" << std::endl;

    return 0;
}

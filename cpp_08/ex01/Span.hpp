#pragma once
#include <vector>
#include <algorithm>
#include <climits>
#include <list>
#include <iterator>
#include <iostream>
#include <stdexcept>

class Span
{
    std::vector<int> numbers;
    unsigned int max_size;
    Span();

public:
    Span(unsigned int N);
    Span(const Span &other);
    Span &operator=(const Span &other);
    ~Span();
    void addNumber(int number);
    void addNumbers(std::vector<int>::iterator first, std::vector<int>::iterator last);

    int shortestSpan();
    int longestSpan();
};

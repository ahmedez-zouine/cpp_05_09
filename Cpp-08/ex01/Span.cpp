#include "Span.hpp"
#include <climits>

Span::Span() {};
Span::Span(unsigned int N)
{
    max_size = N;
}
Span::Span(const Span &other)
{
    if (this != &other)
    {
        numbers = other.numbers;
        max_size = other.max_size;
    }
}
Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        numbers = other.numbers;
        max_size = other.max_size;
    }
    return *this;
};

Span::~Span() {};
void Span::addNumber(int number)
{
    if (numbers.size() < max_size)
        numbers.push_back(number);
    else
        throw std::length_error("Span is full");
}

void Span::addNumbers(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
    unsigned int free_space = max_size - numbers.size();
    unsigned int range_size = std::distance(start, end);
    if (range_size > free_space)
        throw std::length_error("Not enough space to add alll numbers");

    numbers.insert(numbers.end(), start, end);
}

int Span::longestSpan()
{

    if (numbers.size() < 2)
        throw std::length_error("the array doenst have enough numbers");

    int min = *std::min_element(numbers.begin(), numbers.end());
    int max = *std::max_element(numbers.begin(), numbers.end());
    return max - min;
}
int Span::shortestSpan()
{
    if (numbers.size() < 2)
        throw std::length_error("the array doesn't have enough numbers");

    std::vector<int> sorted = numbers;
    std::sort(sorted.begin(),sorted.end());

    int shortest = INT_MAX;
    unsigned int i=1;

    while (i < sorted.size())
    {
        shortest = std::min(shortest,sorted[i]- sorted[i-1]);
        i++;
    }
    
    return shortest;
}
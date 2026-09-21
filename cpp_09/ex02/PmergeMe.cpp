#include "PmergeMe.hpp"
#include <stdexcept>
#include <sstream>
#include <unistd.h>
#include <iomanip>

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

void PmergeMe::sort_and_compare(int argc, char **argv)
{
    std::vector<int> input = parse_input(argc, argv);

    print("Before:", input);

    std::vector<int> vector_data(input);
    std::deque<int> deque_data(input.begin(), input.end());

    double vector_time = calcule_vector_time(vector_data);
    double deque_time = calcule_deque_time(deque_data);

    print("After:", vector_data);

    std::cout << "Time for " << vector_data.size() << " elements with std::vector : " <<vector_time << " us" << std::endl;
    std::cout << "Time for " << deque_data.size() << " elements with std::deque : " << deque_time << " us" << std::endl;
              
}

void PmergeMe::sort(std::vector<int> &vec)
{
    int n = vec.size();
    if (n <= 1)
        return;
    std::vector<int> larger, smaller;

    for (int i = 0; i < n - 1; i += 2)
    {
        if (vec[i] > vec[i + 1])
        {
            larger.push_back(vec[i]);
            smaller.push_back(vec[i + 1]);
        }
        else
        {
            larger.push_back(vec[i + 1]);
            smaller.push_back(vec[i]);
        }
    }

    int odd_element = 0;
    bool has_odd = 0;
    if (n % 2)
        has_odd = 1;
    if (has_odd)
        odd_element = vec[n - 1];

    sort(larger);

    std::vector<int> jacob_array = jacob_order(smaller.size());
    for (size_t i = 0; i < jacob_array.size(); ++i)
    {
        int start = 0;
        if (i != 0)
            start = jacob_array[i - 1];
        int end = jacob_array[i];

        for (int j = end - 1; j >= start; --j)
        {
            if (j < static_cast<int>(smaller.size()) && j >= 0)
            {
                std::vector<int>::iterator pos = std::lower_bound(larger.begin(), larger.end(), smaller[j]);
                larger.insert(pos, smaller[j]);
            }
        }
    }

    if (has_odd)
    {
        std::vector<int>::iterator pos = std::lower_bound(larger.begin(), larger.end(), odd_element);
        larger.insert(pos, odd_element);
    }

    vec = larger;
}

void PmergeMe::sort(std::deque<int> &deq)
{
    int n = deq.size();
    if (n <= 1)
        return;


   // tow vectors to hold larger and smaller elements
    std::deque<int> larger, smaller;

    for (int i = 0; i < n - 1; i += 2)
    {
        if (deq[i] > deq[i + 1])
        {
            larger.push_back(deq[i]);
            smaller.push_back(deq[i + 1]);
        }
        else
        {
            larger.push_back(deq[i + 1]);
            smaller.push_back(deq[i]);
        }
    }

    // this will hold the odd element if exists
    int odd_element = 0;
    bool has_odd = 0;
    if (n % 2)
        has_odd = 1;
    if (has_odd)
        odd_element = deq[n - 1];
// sort the larger elements recursively like merge sort like this value is always half of the original size 
    sort(larger);

    std::vector<int> jacob_array = jacob_order(smaller.size());
    for (size_t i = 0; i < jacob_array.size(); ++i)
    {
        int start = 0;
        if (i != 0)
            start = jacob_array[i - 1];
        int end = jacob_array[i];

        for (int j = end - 1; j >= start; --j)
        {
            if (j < static_cast<int>(smaller.size()) && j >= 0)
            {
                // find the position to insert using binary search
                // lower_bound returns an iterator to the first element not less than the value
                std::deque<int>::iterator pos = std::lower_bound(larger.begin(), larger.end(), smaller[j]);
                larger.insert(pos, smaller[j]);
            }
        }
    }

    if (has_odd)
    {
        std::deque<int>::iterator pos = std::lower_bound(larger.begin(), larger.end(), odd_element);
        larger.insert(pos, odd_element);
    }

    deq = larger;
}

// Generate Jacobsthal numbers up to size 'size'
std::vector<int> PmergeMe::jacob_order(int size)
{
    std::vector<int> jacob;

    // Base cases starting the sequence with J(0) = 0, J(1) = 1 after that J(n) = J(n-1) + 2*J(n-2)
    jacob.push_back(0);
    jacob.push_back(1);
    if (size <= 1)
        return jacob;
    
    int i = 2;
    while (jacob.back() < size)
    {
        // Jacobsthal number: J(n) = J(n-1) + 2*J(n-2) // n - 1 + 2 * (n - 2)
        int next = jacob[i-1] + 2 * jacob[i-2];
        jacob.push_back(next);
        i++;
    }
    return jacob;
}
double PmergeMe::calcule_vector_time(std::vector<int> &vec)
{
    clock_t start = clock();
    sort(vec);
    clock_t end = clock();

    double  microseconds =static_cast<double>(end - start) / CLOCKS_PER_SEC ;
    microseconds *= 1000000;

    return microseconds;
}

double PmergeMe::calcule_deque_time(std::deque<int> &deq)
{
    clock_t start = clock();
    sort(deq);
    clock_t end = clock();

    double  microseconds =static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000 ;

    return microseconds;
}

void PmergeMe::print(const std::string &timeline, const std::vector<int> &data)
{
    std::cout << timeline;
    for (size_t i = 0; i < data.size(); i++)
        std::cout << " " << data[i];
    std::cout << std::endl;
}

std::vector<int> PmergeMe::parse_input(int argc, char **argv)
{
    if (argc < 2)
        throw std::runtime_error("Error: No input ");

    std::vector<int> result;

    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);

        for (size_t j = 0; j < arg.length(); j++)
        {
            if (!std::isdigit(arg[j]))
                throw std::runtime_error("Error: Invalid input");
        }

        int num = atoi(arg.c_str());
        result.push_back(num);
    }

    return result;
}
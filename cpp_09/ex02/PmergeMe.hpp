#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <ctime>
#include <algorithm>

class PmergeMe {
public:
    PmergeMe();
    ~PmergeMe();
    
    void sort_and_compare(int argc, char** argv);

    void sort(std::vector<int>& vec);
    void sort(std::deque<int>& deq);
    std::vector<int> jacob_order(int size);

    double calcule_vector_time(std::vector<int> &vec);
    double calcule_deque_time(std::deque<int> &deq);

    void print(const std::string& timeline, const std::vector<int>& data);
    std::vector<int> parse_input(int argc, char** argv);
};

#endif
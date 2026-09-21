#pragma once

#include <stack>
#include <deque>

template <typename T>
// MutantStack class that inherits from std::stack and provides iterator access
// to the underlying container 
class MutantStack : public std::stack<T>
{
public:
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;

    MutantStack();
    MutantStack(const MutantStack<T> &other);
    MutantStack<T> &operator=(const MutantStack<T> &other);
    ~MutantStack();

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;
};

template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>()
{
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T> &other) : std::stack<T>(other)
{
}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack<T> &other)
{
    if (this != &other)
    {
        std::stack<T>::operator=(other);
    }
    return *this;
}

template <typename T>
MutantStack<T>::~MutantStack()
{
}


template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin()
{
    // Access the underlying container's begin iterator
    // this is possible because std::stack is a protected inheritance
    // of the underlying container
    // Here, c is the underlying container
    // std::stack<T> has a protected member 'c' which is the underlying container its like deque or vector
    // We can access it directly in a derived class like MutantStack
    return this->c.begin();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin() const
{
    return this->c.begin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end()
{
    return this->c.end();
}
template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end() const
{
    return this->c.end();
}
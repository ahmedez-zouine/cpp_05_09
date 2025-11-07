# C++ Module 08: STL (Standard Template Library)

## 📚 Subject Overview

This module introduces the **Standard Template Library (STL)**, one of the most powerful features of C++. The STL provides a collection of template classes and functions that implement common data structures and algorithms, making C++ programming more efficient and standardized.

### What You'll Learn

- **STL Containers**: Pre-built data structures (vector, list, stack, deque, etc.)
- **Iterators**: Objects that provide access to container elements
- **Algorithms**: Pre-written functions for common operations (find, sort, etc.)
- **Templates**: Generic programming to write code that works with any data type

---

## 🎯 Exercises

### Exercise 00: Easy Find

**Objective**: Create a template function that finds a value in any STL container.

#### What It Does

The `easyfind` function is a template function that:
- Takes any STL container (vector, list, deque, etc.) and a value to find
- Uses `std::find` algorithm to search for the value
- Returns the index (position) of the value if found, or `-1` if not found

#### How It Works

```cpp
template<typename T>
int easyfind(T &container, int value_to_find)
{
    // Get an iterator pointing to the found element (or end() if not found)
    typename T::iterator res_it = std::find(container.begin(), container.end(), value_to_find);
    
    // If found, calculate and return the index
    if(res_it != container.end())
        return std::distance(container.begin(), res_it);
    else
        return -1;  // Not found
}
```

#### Key Concepts

1. **Template Function**: Works with any container type (`T`)
2. **Iterator**: `container.begin()` and `container.end()` define the range
3. **STL Algorithm**: `std::find()` searches the container
4. **Distance Calculation**: `std::distance()` calculates the index

#### Example Usage

```cpp
std::vector<int> numbers = {10, 20, 30};
int index = easyfind(numbers, 20);  // Returns 1
int notFound = easyfind(numbers, 99);  // Returns -1
```

#### Why It's Useful

- **Generic**: Works with any STL container (vector, list, deque, etc.)
- **Simple**: One function for all containers instead of writing separate functions
- **Efficient**: Uses optimized STL algorithms

---

### Exercise 01: Span

**Objective**: Create a class that stores numbers and calculates the shortest and longest span (difference) between them.

#### What It Does

The `Span` class:
- Stores a fixed number of integers (set at construction)
- Allows adding numbers one by one or in bulk
- Calculates the **shortest span** (minimum difference between any two numbers)
- Calculates the **longest span** (difference between max and min values)

#### How It Works

**Class Structure:**
```cpp
class Span {
    std::vector<int> numbers;      // Internal storage
    unsigned int max_size;          // Maximum capacity
    
public:
    Span(unsigned int N);           // Constructor with capacity
    void addNumber(int number);     // Add single number
    void addNumbers(iterator first, iterator last);  // Add range of numbers
    int shortestSpan();             // Find minimum difference
    int longestSpan();              // Find max - min
};
```

**Adding Numbers:**
```cpp
void addNumber(int number) {
    if (numbers.size() < max_size)
        numbers.push_back(number);
    else
        throw std::length_error("Span is full");
}
```

**Longest Span (Simple):**
```cpp
int longestSpan() {
    if (numbers.size() < 2)
        throw std::length_error("Need at least 2 numbers");
    
    int min = *std::min_element(numbers.begin(), numbers.end());
    int max = *std::max_element(numbers.max(), numbers.end());
    return max - min;  // Simple: max - min
}
```

**Shortest Span (More Complex):**
```cpp
int shortestSpan() {
    if (numbers.size() < 2)
        throw std::length_error("Need at least 2 numbers");
    
    // Sort the numbers first
    std::vector<int> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());
    
    // Find minimum difference between adjacent elements
    int shortest = INT_MAX;
    for (size_t i = 1; i < sorted.size(); i++) {
        shortest = std::min(shortest, sorted[i] - sorted[i-1]);
    }
    return shortest;
}
```

#### Example Usage

```cpp
Span sp(5);  // Create Span with capacity of 5

sp.addNumber(6);
sp.addNumber(3);
sp.addNumber(17);
sp.addNumber(9);
sp.addNumber(11);

std::cout << sp.shortestSpan() << std::endl;  // 2 (difference between 9 and 11)
std::cout << sp.longestSpan() << std::endl;   // 14 (17 - 3)
```

#### Key Concepts

1. **STL Vector**: Dynamic array used for storage
2. **STL Algorithms**: `std::min_element()`, `std::max_element()`, `std::sort()`
3. **Iterators**: Used in `addNumbers()` to add a range of values
4. **Exception Handling**: Throws exceptions when capacity is exceeded

#### Why It's Useful

- Demonstrates practical use of STL containers and algorithms
- Shows how to work with iterators for bulk operations
- Real-world application: finding ranges in datasets

---

### Exercise 02: MutantStack

**Objective**: Create a stack that can be iterated (normally, `std::stack` doesn't support iteration).

#### What It Does

The `MutantStack` class:
- Inherits from `std::stack<T>`
- Adds iterator functionality (begin/end)
- Can be used like a normal stack (push, pop, top)
- Can also be iterated like a vector or list

#### How It Works

**The Problem:**
`std::stack` doesn't provide iterators because it's designed as a LIFO (Last In, First Out) container. You can only access the top element.

**The Solution:**
`std::stack` internally uses a container (by default, `std::deque`). We can access this underlying container using the protected member `c` and expose iterators.

**Class Structure:**
```cpp
template <typename T>
class MutantStack : public std::stack<T> {
public:
    // Define iterator types from the underlying container
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;
    
    // Iterator methods
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};
```

**Implementation:**
```cpp
template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
    return this->c.begin();  // Access underlying container
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
    return this->c.end();
}
```

#### Example Usage

```cpp
MutantStack<int> mstack;

mstack.push(5);
mstack.push(17);
mstack.push(3);
mstack.push(737);
mstack.push(0);

// Use as normal stack
std::cout << mstack.top() << std::endl;  // 0
mstack.pop();

// Iterate like a container!
MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();

while (it != ite) {
    std::cout << *it << std::endl;  // Print all elements
    ++it;
}
```

#### Key Concepts

1. **Template Class**: Works with any data type
2. **Inheritance**: Extends `std::stack` functionality
3. **Container Adapter**: `std::stack` is an adapter over `std::deque`
4. **Iterator Pattern**: Provides iteration capability
5. **Protected Members**: Accessing `c` (the underlying container)

#### Why It's Useful

- Shows how to extend STL containers
- Demonstrates template inheritance
- Useful when you need stack behavior but also want to iterate

---

## 🛠️ Compilation and Execution

### Compile All Exercises

```bash
# Exercise 00
cd ex00
make

# Exercise 01
cd ../ex01
make

# Exercise 02
cd ../ex02
make
```

### Run Examples

```bash
# Exercise 00
./easyfind

# Exercise 01
./span

# Exercise 02
./mutantstack
```

---

## 📖 Key Takeaways

1. **STL is Powerful**: Pre-built containers and algorithms save time and are optimized
2. **Templates Enable Genericity**: Write once, use with any type
3. **Iterators Provide Uniform Access**: Same interface for different containers
4. **Algorithms Work with Iterators**: Decouple algorithms from specific containers
5. **Container Adapters**: Some containers (like stack) are built on top of others

---

## 🔗 Related Concepts

- **Templates**: Generic programming
- **Iterators**: Accessing container elements
- **STL Containers**: vector, list, deque, stack, etc.
- **STL Algorithms**: find, sort, min_element, max_element, etc.
- **Exception Handling**: Error management

For detailed explanations of these concepts, see [CONCEPTS.md](CONCEPTS.md).

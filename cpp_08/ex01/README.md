# Exercise 01: Span

## Objective
Create a `Span` class that stores N integers and can calculate the shortest and longest "span" (distance) between any two numbers.

---

## Concept: Custom Container with STL Algorithms

### What is a Span?
A **span** is the absolute difference between two numbers.

**Examples**:
- Span between 5 and 10 = |10 - 5| = 5
- Span between 100 and 20 = |100 - 20| = 80

### The Challenge
Given a collection of numbers, find:
- **Shortest span**: Minimum difference between any two numbers
- **Longest span**: Maximum difference between any two numbers

---

## How It Works - Simple Explanation

### Shortest Span Algorithm

**Visual Example**: `[5, 10, 3, 17, 2]`

```
Step 1: Sort the array
[2, 3, 5, 10, 17]

Step 2: Check adjacent pairs (only neighbors matter!)
2 to 3   → span = 1  ⭐ Shortest!
3 to 5   → span = 2
5 to 10  → span = 5
10 to 17 → span = 7

Result: Shortest span = 1
```

**Why sort?** Because the shortest distance between numbers will always be between adjacent numbers when sorted!

### Longest Span Algorithm

**Same Example**: `[5, 10, 3, 17, 2]`

```
Step 1: Find minimum
min = 2

Step 2: Find maximum
max = 17

Step 3: Calculate difference
longest span = 17 - 2 = 15
```

**Why this works?** The longest span is always between the smallest and largest numbers!

---

## Class Structure

```cpp
class Span {
private:
    std::vector<int> numbers;     // Stores the integers
    unsigned int max_size;        // Maximum capacity
    
public:
    Span(unsigned int N);         // Constructor with max size
    
    void addNumber(int number);   // Add one number
    void addNumbers(iterator start, iterator end);  // Add many numbers at once
    
    int shortestSpan();           // Find shortest distance
    int longestSpan();            // Find longest distance
};
```

---

## Method Breakdown

### 1. Constructor
```cpp
Span(unsigned int N);
```
**Purpose**: Create a Span that can hold up to N numbers.

**Example**:
```cpp
Span sp(5);  // Can hold 5 numbers maximum
```

---

### 2. addNumber()
```cpp
void addNumber(int number);
```
**Purpose**: Add a single number to the Span.

**How it works**:
```cpp
void Span::addNumber(int number) {
    if (numbers.size() < max_size)
        numbers.push_back(number);  // Add to vector
    else
        throw std::length_error("Span is full");  // No space!
}
```

**Example**:
```cpp
Span sp(5);
sp.addNumber(10);
sp.addNumber(20);
sp.addNumber(30);
```

---

### 3. addNumbers() - Bulk Insert
```cpp
void addNumbers(std::vector<int>::iterator start, std::vector<int>::iterator end);
```
**Purpose**: Add multiple numbers at once using iterators.

**How it works**:
```cpp
void Span::addNumbers(std::vector<int>::iterator start, std::vector<int>::iterator end) {
    unsigned int free_space = max_size - numbers.size();
    unsigned int range_size = std::distance(start, end);
    
    if (range_size > free_space)
        throw std::length_error("Not enough space");
    
    numbers.insert(numbers.end(), start, end);  // Insert range
}
```

**Example**:
```cpp
Span sp(1000);
std::vector<int> manyNumbers = {1, 2, 3, 4, 5, ...};

// Add all at once!
sp.addNumbers(manyNumbers.begin(), manyNumbers.end());
```

**Why this is useful?** You can add 10,000 numbers in one call instead of calling addNumber() 10,000 times!

---

### 4. shortestSpan()
```cpp
int shortestSpan();
```
**Purpose**: Find the minimum difference between any two numbers.

**Algorithm**:
```cpp
int Span::shortestSpan() {
    if (numbers.size() < 2)
        throw std::length_error("Need at least 2 numbers");
    
    // Make a sorted copy
    std::vector<int> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());
    
    int shortest = INT_MAX;  // Start with maximum possible value
    
    // Check all adjacent pairs
    for (unsigned int i = 1; i < sorted.size(); i++) {
        int span = sorted[i] - sorted[i-1];
        shortest = std::min(shortest, span);
    }
    
    return shortest;
}
```

**Step-by-step with example** `[100, 5, 10, 8]`:
```
1. Sort: [5, 8, 10, 100]
2. Check pairs:
   - 8 - 5 = 3
   - 10 - 8 = 2  ⭐ Shortest!
   - 100 - 10 = 90
3. Return 2
```

---

### 5. longestSpan()
```cpp
int longestSpan();
```
**Purpose**: Find the maximum difference between any two numbers.

**Algorithm**:
```cpp
int Span::longestSpan() {
    if (numbers.size() < 2)
        throw std::length_error("Need at least 2 numbers");
    
    int min = *std::min_element(numbers.begin(), numbers.end());
    int max = *std::max_element(numbers.begin(), numbers.end());
    
    return max - min;
}
```

**Step-by-step with example** `[100, 5, 10, 8]`:
```
1. Find min: 5
2. Find max: 100
3. Return: 100 - 5 = 95
```

---

## Key STL Functions Used

### 1. `std::vector::push_back()`
```cpp
numbers.push_back(42);
```
- Adds element to end of vector
- Vector automatically grows if needed

### 2. `std::vector::insert()`
```cpp
numbers.insert(numbers.end(), start, end);
```
- Inserts a range of elements
- Efficient bulk insertion

### 3. `std::sort()`
```cpp
std::sort(sorted.begin(), sorted.end());
```
- Sorts elements in ascending order
- Very efficient (O(n log n))

### 4. `std::min_element()` / `std::max_element()`
```cpp
int min = *std::min_element(numbers.begin(), numbers.end());
int max = *std::max_element(numbers.begin(), numbers.end());
```
- Returns iterator to min/max element
- Dereference with `*` to get value

### 5. `std::distance()`
```cpp
unsigned int size = std::distance(start, end);
```
- Calculates number of elements between iterators

---

## Complete Usage Example

```cpp
#include "Span.hpp"
#include <iostream>

int main() {
    // Create a Span that can hold 5 numbers
    Span sp(5);
    
    // Add numbers one by one
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);
    
    // Calculate spans
    std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;  // 2 (11-9)
    std::cout << "Longest span: " << sp.longestSpan() << std::endl;    // 14 (17-3)
    
    // Testing with large dataset
    Span bigSpan(10000);
    std::vector<int> numbers;
    for (int i = 0; i < 10000; i++)
        numbers.push_back(i * 2);  // Even numbers
    
    bigSpan.addNumbers(numbers.begin(), numbers.end());
    std::cout << "Shortest span: " << bigSpan.shortestSpan() << std::endl;  // 2
    
    return 0;
}
```

---

## Exception Handling

### Why Exceptions?
Exceptions handle error cases gracefully without checking return values.

### Error Cases:

1. **Span is full**:
```cpp
Span sp(3);
sp.addNumber(1);
sp.addNumber(2);
sp.addNumber(3);
sp.addNumber(4);  // Throws std::length_error("Span is full")
```

2. **Not enough numbers for span**:
```cpp
Span sp(5);
sp.addNumber(42);
int span = sp.shortestSpan();  // Throws std::length_error("Need at least 2 numbers")
```

3. **Too many numbers to add**:
```cpp
Span sp(10);
std::vector<int> nums(100, 1);  // 100 numbers
sp.addNumbers(nums.begin(), nums.end());  // Throws std::length_error
```

---

## Visual Workflow

```
User Creates Span(5)
        ↓
    [ _ _ _ _ _ ]  Empty, max_size = 5
        ↓
    addNumber(10)
        ↓
    [ 10 _ _ _ _ ]  size = 1
        ↓
    addNumber(20)
    addNumber(30)
        ↓
    [ 10 20 30 _ _ ]  size = 3
        ↓
    shortestSpan()
        ↓
    Sort: [10, 20, 30]
    Check: 20-10=10, 30-20=10
    Return: 10
        ↓
    longestSpan()
        ↓
    min=10, max=30
    Return: 30-10=20
```

---

## Performance Considerations

### Time Complexity:
- `addNumber()`: O(1) - constant time
- `addNumbers()`: O(n) - where n is number of elements to add
- `shortestSpan()`: O(n log n) - due to sorting
- `longestSpan()`: O(n) - single pass to find min and max

### Why shortestSpan() is O(n log n)?
Sorting is the most expensive operation. Finding adjacent differences is O(n), but sorting dominates.

---

## Common Mistakes to Avoid

❌ **Not checking if container is empty**:
```cpp
int min = *std::min_element(numbers.begin(), numbers.end());  // Crash if empty!
```

✅ **Always check size first**:
```cpp
if (numbers.size() < 2)
    throw std::length_error("Need at least 2 numbers");
```

---

❌ **Modifying original array**:
```cpp
std::sort(numbers.begin(), numbers.end());  // Changes original order!
```

✅ **Sort a copy**:
```cpp
std::vector<int> sorted = numbers;  // Make a copy
std::sort(sorted.begin(), sorted.end());
```

---

## Build and Test

```bash
# Compile
make

# Run
./span

# Clean
make fclean

# Rebuild
make re
```

---

## Expected Output
```
Adding individual numbers...
Successfully added three numbers individually
Generating 500 random numbers...
Adding 500 numbers at once using addNumbers...
Successfully added all numbers
Shortest span: 1
Longest span: 9999
Trying to add more numbers than capacity...
Expected error: Not enough space to add all numbers
```

---

## What You Learned

✅ Creating custom container classes  
✅ Using `std::vector` as internal storage  
✅ Implementing range-based operations with iterators  
✅ Using STL algorithms (`sort`, `min_element`, `max_element`)  
✅ Exception handling with `std::length_error`  
✅ Efficient bulk operations  
✅ Working with large datasets (10,000+ elements)  

---

## Challenge Yourself

Try these modifications:
1. Add a method to find the median span
2. Make it work with any numeric type (use templates!)
3. Add a method to return all spans in sorted order
4. Optimize to avoid sorting if numbers are already sorted

---

## Next Steps

Move on to **Exercise 02: MutantStack** to learn about:
- Inheriting from STL containers
- Adding iterators to non-iterable containers
- Template class inheritance

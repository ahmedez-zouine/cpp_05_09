# C++ Module 09 - STL Containers and Algorithms

## Overview
C++ Module 09 focuses on **STL (Standard Template Library)** containers and algorithms. This module teaches you how to effectively use different container types, understand their performance characteristics, and implement complex algorithms using STL features.

## Key Concepts Covered

### 1. STL Containers
- **std::map** - Associative container for key-value pairs
- **std::stack** - LIFO (Last In, First Out) container adapter
- **std::vector** - Dynamic array container
- **std::deque** - Double-ended queue container

### 2. Algorithms and Data Processing
- **File parsing and CSV handling**
- **String manipulation and validation**
- **Date validation and processing**
- **Mathematical calculations**
- **Reverse Polish Notation (RPN) evaluation**
- **Advanced sorting algorithms (Ford-Johnson/Merge-Insertion)**

### 3. Performance Analysis
- **Time complexity comparison**
- **Container performance benchmarking**
- **Algorithm optimization**

---

## Exercise 00: Bitcoin Exchange

### Concept: File Processing and std::map

**What it teaches:**
- Reading and parsing CSV files
- Using `std::map` for efficient key-value storage and lookup
- Date validation and string processing
- Binary search with `lower_bound()`

**Core Algorithm:**
```cpp
std::map<std::string, double> prices;  // Date -> Price mapping

// Loading CSV data
std::getline(csv_file, line);
std::stringstream line_stream(line);
std::string date;
double value;
getline(line_stream, date, ',');
line_stream >> value;
prices[date] = value;  // O(log n) insertion
```

**Key Features:**
1. **CSV Parser**: Reads Bitcoin price data from `data.csv`
2. **Date Validation**: Validates year (2009-2025), month (1-12), day (considering leap years)
3. **Price Lookup**: Uses `lower_bound()` for efficient closest-date search
4. **Error Handling**: Comprehensive input validation

**std::map Benefits:**
- **Sorted storage**: Keys automatically sorted
- **O(log n)** search, insertion, deletion
- **lower_bound()**: Finds first element not less than key

**Example Usage:**
```bash
# Input file format:
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1

# Output:
2011-01-03 => 0.9
2011-01-03 => 0.6
2011-01-03 => 0.3
```

**Real-world Application:**
- Financial data processing
- Time-series data analysis
- Historical price lookups

---

## Exercise 01: Reverse Polish Notation (RPN)

### Concept: Stack-based Expression Evaluation

**What it teaches:**
- Using `std::stack` for LIFO operations
- Parsing mathematical expressions
- Postfix notation evaluation
- Error handling for mathematical operations

**Core Algorithm:**
```cpp
std::stack<int> stack;

// For each token in input:
if (isdigit(token)) {
    stack.push(token);              // Push operand
} else {                           // Operator
    int b = stack.top(); stack.pop();
    int a = stack.top(); stack.pop();
    int result = operate(a, b);
    stack.push(result);            // Push result back
}
```

**RPN Explanation:**
- **Infix**: `3 + 4 * 2` → **Postfix**: `3 4 2 * +`
- **Evaluation**: 
  1. Push 3, 4, 2 → Stack: [3, 4, 2]
  2. See `*` → Pop 2,4 → Calculate 4*2=8 → Push 8 → Stack: [3, 8]
  3. See `+` → Pop 8,3 → Calculate 3+8=11 → Push 11 → Stack: [11]
  4. Result: 11

**std::stack Benefits:**
- **LIFO access**: Perfect for expression evaluation
- **O(1)** push/pop operations
- **Memory efficient**: Only stores what's needed

**Example Usage:**
```bash
./rpn "8 9 * 9 - 9 - 9 - 4 - 1 +"
# 8 9 * = 72
# 72 9 - = 63
# 63 9 - = 54
# 54 9 - = 45
# 45 4 - = 41
# 41 1 + = 42
result is 42
```

**Real-world Applications:**
- Calculator implementations
- Compiler expression parsing
- Mathematical formula evaluation

---

## Exercise 02: Ford-Johnson Algorithm (Merge-Insertion Sort)

### Concept: Advanced Sorting with Container Comparison

**What it teaches:**
- **Ford-Johnson Algorithm**: Minimizes comparisons during sorting
- **Container performance**: Comparing `std::vector` vs `std::deque`
- **Jacobsthal numbers**: Mathematical sequence for optimal insertion order
- **Performance measurement**: Timing algorithms

**Algorithm Overview:**
1. **Pair elements** and sort pairs (larger, smaller)
2. **Recursively sort** the larger elements
3. **Insert smaller elements** using Jacobsthal sequence order
4. **Handle odd element** if present

**Jacobsthal Numbers:**
- Sequence: 1, 1, 3, 5, 11, 21, 43, 85...
- Formula: `J(n) = J(n-1) + 2*J(n-2)`
- **Purpose**: Minimizes binary search comparisons during insertion

```cpp
// Jacobsthal generation
std::vector<int> jacob_order(int size) {
    std::vector<int> jacob = {0, 1, 1};
    int i = 2;
    while (jacob.back() < size) {
        int next = jacob[i-1] + 2 * jacob[i-2];
        jacob.push_back(next);
        i++;
    }
    return jacob;
}
```

**Core Sorting Logic:**
```cpp
// 1. Pair and compare
for (int i = 0; i < n - 1; i += 2) {
    if (vec[i] > vec[i + 1]) {
        larger.push_back(vec[i]);
        smaller.push_back(vec[i + 1]);
    } else {
        larger.push_back(vec[i + 1]);
        smaller.push_back(vec[i]);
    }
}

// 2. Recursively sort larger elements
sort(larger);

// 3. Insert smaller elements in Jacobsthal order
for (int j = end - 1; j >= start; --j) {
    auto pos = std::lower_bound(larger.begin(), larger.end(), smaller[j]);
    larger.insert(pos, smaller[j]);
}
```

**Container Comparison:**

| Feature | std::vector | std::deque |
|---------|------------|-----------|
| **Memory** | Contiguous | Segmented blocks |
| **Access** | O(1) random | O(1) random |
| **Insert/Erase** | O(n) middle | O(n) middle |
| **Front operations** | O(n) | O(1) |
| **Cache efficiency** | Better | Worse |

**Performance Analysis:**
```cpp
clock_t start = clock();
sort(container);
clock_t end = clock();
double microseconds = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
```

**Example Output:**
```bash
./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time for 5 elements with std::vector : 8 us
Time for 5 elements with std::deque : 12 us
```

**Why Ford-Johnson?**
- **Theoretical optimality**: Minimizes number of comparisons
- **Complex implementation**: Good for learning advanced algorithms
- **Real-world relevance**: Used in performance-critical applications

---

## Advanced Concepts Demonstrated

### 1. Iterator Usage
```cpp
// lower_bound returns iterator to first element >= value
std::vector<int>::iterator pos = std::lower_bound(
    larger.begin(), larger.end(), smaller[j]
);
larger.insert(pos, smaller[j]);  // Insert at optimal position
```

### 2. Template Functions
```cpp
template<typename Container>
void sort(Container& container) {
    // Works with both vector and deque
}
```

### 3. Time Complexity Analysis
- **BitcoinExchange lookup**: O(log n) with `std::map`
- **RPN evaluation**: O(n) linear scan
- **Ford-Johnson sort**: O(n log n) with minimal comparisons

### 4. Memory Management
- **RAII**: All containers automatically manage memory
- **Copy semantics**: Proper copy constructors implemented
- **Exception safety**: Using STL containers for safety

---

## Practical Applications

### BitcoinExchange
- **Financial systems**: Historical price analysis
- **Time-series databases**: Efficient date-based queries
- **Data analytics**: Processing large datasets

### RPN Calculator
- **Programming languages**: PostScript, Forth
- **Scientific calculators**: HP calculators use RPN
- **Compiler design**: Expression evaluation in parsers

### Ford-Johnson Sorting
- **Database systems**: Optimized sorting for specific data patterns
- **Embedded systems**: When comparisons are expensive
- **Academic research**: Algorithm optimization studies

---

## Key Takeaways

1. **Choose the right container**: Each STL container has specific strengths
2. **Understand complexity**: Know time/space trade-offs
3. **Use STL algorithms**: `lower_bound`, `upper_bound`, etc.
4. **Measure performance**: Always benchmark when optimization matters
5. **Error handling**: Robust input validation is crucial
6. **Mathematical algorithms**: Understanding theory improves implementation

This module demonstrates how C++ STL provides powerful, efficient tools for complex data processing tasks while maintaining type safety and performance.
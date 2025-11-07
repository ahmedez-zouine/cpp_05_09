# Exercise 00: Easy Find

## Objective
Write a template function `easyfind` that searches for the first occurrence of an integer in any STL container.

---

## Concept: Template Functions

### What are Templates?
Templates allow you to write **generic code** that works with any data type. Instead of writing separate functions for different container types (vector, list, deque), you write ONE template function.

### Simple Analogy
Imagine a vending machine that can dispense any product:
- You don't need different machines for chips, drinks, or candy
- One machine template works for all products
- Templates are like that - one function works for all types!

---

## How It Works

### The Function Signature
```cpp
template<typename T>
int easyfind(T &container, int value_to_find);
```

**Breaking it down**:
- `template<typename T>` - "T can be any type"
- `T &container` - A reference to any container type (vector, list, etc.)
- `int value_to_find` - The integer we're searching for
- Returns: Index of the element, or -1 if not found

---

## Step-by-Step Implementation

### Step 1: Use std::find()
```cpp
typename T::iterator res_it;
res_it = std::find(container.begin(), container.end(), value_to_find);
```

**What happens here**:
- `typename T::iterator` - The iterator type for container T
- `std::find()` - STL algorithm that searches from begin to end
- Returns an iterator pointing to the found element (or end if not found)

### Step 2: Check if Found
```cpp
if(res_it != container.end())
    return std::distance(container.begin(), res_it);
else
    return -1;
```

**What happens here**:
- If iterator ≠ end → element was found!
- `std::distance()` calculates the index position
- If iterator = end → element not found, return -1

---

## Visual Example

Let's say we have a vector: `[10, 20, 30, 40, 50]`

```
Searching for 30:

Step 1: std::find() searches
[10] → [20] → [30] ✓ Found!
                ↑
              res_it points here

Step 2: Calculate distance
From begin to res_it = 2 positions
Return 2 (index of value 30)

Searching for 99:

Step 1: std::find() searches
[10] → [20] → [30] → [40] → [50] → end
                                      ↑
                                   res_it = end

Step 2: res_it == end, so return -1
```

---

## Why Use Templates?

### Without Templates (Bad Way):
```cpp
int easyfind_vector(std::vector<int> &v, int value);
int easyfind_list(std::list<int> &l, int value);
int easyfind_deque(std::deque<int> &d, int value);
// ... repeat for every container type!
```

### With Templates (Good Way):
```cpp
template<typename T>
int easyfind(T &container, int value);
// ONE function works for ALL container types!
```

---

## Key STL Functions Used

### 1. `std::find(begin, end, value)`
- **Purpose**: Search for a value in a range
- **Returns**: Iterator to the found element, or end if not found
- **Header**: `<algorithm>`

### 2. `std::distance(first, last)`
- **Purpose**: Calculate number of elements between two iterators
- **Returns**: An integer representing the distance
- **Header**: `<iterator>` (included in `<algorithm>`)

### 3. `container.begin()` and `container.end()`
- **begin()**: Iterator pointing to the first element
- **end()**: Iterator pointing PAST the last element (not AT the last element!)

---

## Usage Example

```cpp
#include "easyfind.hpp"
#include <vector>
#include <list>
#include <iostream>

int main() {
    // Works with vector
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    
    int index = easyfind(vec, 20);  // Returns 1
    
    // Works with list (same function!)
    std::list<int> lst;
    lst.push_back(100);
    lst.push_back(200);
    
    index = easyfind(lst, 200);  // Returns 1
    
    // Element not found
    index = easyfind(vec, 999);  // Returns -1
    
    return 0;
}
```

---

## Important Notes

### 1. **typename Keyword**
```cpp
typename T::iterator res_it;
```
The `typename` keyword is needed because `T::iterator` is a **dependent type** (depends on the template parameter T). Without it, the compiler doesn't know if `T::iterator` is a type or a value.

### 2. **Why return -1?**
We return -1 to indicate "not found" because:
- Valid indices are 0, 1, 2, 3, ...
- -1 is an invalid index, clearly indicating failure
- Common convention in C/C++ programming

### 3. **Container Requirements**
The container must have:
- `begin()` and `end()` methods
- An `iterator` type
- Elements that can be compared with `==`

---

## Common Mistakes to Avoid

❌ **Forgetting typename**:
```cpp
T::iterator it;  // Error! Compiler confused
```

✅ **Correct**:
```cpp
typename T::iterator it;  // OK!
```

---

❌ **Comparing iterator directly to value**:
```cpp
if (*res_it == value)  // Wrong if res_it == end()!
```

✅ **Correct**:
```cpp
if (res_it != container.end())  // Check first!
    return std::distance(container.begin(), res_it);
```

---

## Build and Test

```bash
# Compile
make

# Run
./easyfind

# Clean
make fclean

# Rebuild
make re
```

---

## Expected Output

```
Found value at index: 2
Value 99 not found.
```

---

## What You Learned

✅ How to write template functions  
✅ Using `std::find()` algorithm  
✅ Working with iterators  
✅ Calculating distances between iterators  
✅ Understanding `begin()` and `end()`  
✅ Generic programming principles  

---

## Next Steps

After mastering this exercise:
1. Try using it with different containers (list, deque)
2. Modify it to find ALL occurrences, not just the first
3. Make it throw exceptions instead of returning -1
4. Move on to Exercise 01 to build a more complex container class!

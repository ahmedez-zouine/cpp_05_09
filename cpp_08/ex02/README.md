# Exercise 02: Mutant Stack

## Objective
Create a **MutantStack** class that inherits from `std::stack` and adds **iterator support**, making the stack iterable (something the standard stack cannot do).

---

## Concept: Making the Non-Iterable Iterable

### The Problem with std::stack

Standard `std::stack` is a **container adapter** that provides a LIFO (Last In, First Out) interface:
- You can `push()` (add to top)
- You can `pop()` (remove from top)
- You can `top()` (see top element)

**BUT** you **CANNOT** iterate through it!

```cpp
std::stack<int> s;
s.push(1);
s.push(2);
s.push(3);

// ❌ This won't compile:
for (std::stack<int>::iterator it = s.begin(); it != s.end(); ++it)
    std::cout << *it;  // ERROR! Stack has no begin() or end()!
```

### The Solution: MutantStack

Create a **mutant** (modified) stack that:
- ✅ Works like a normal stack (push, pop, top)
- ✅ **ALSO** can be iterated through (begin, end)

---

## How std::stack Works Internally

### Stack is a Container Adapter

```cpp
template <typename T, typename Container = std::deque<T>>
class std::stack {
protected:
    Container c;  // Internal container (usually deque)
    
public:
    void push(const T& value) { c.push_back(value); }
    void pop() { c.pop_back(); }
    T& top() { return c.back(); }
    size_t size() { return c.size(); }
    // ... but NO iterators!
};
```

**Key insight**: Stack stores data in an internal container called `c` (protected member). By default, this is a `std::deque<T>`.

---

## MutantStack Implementation

### Class Declaration
```cpp
template <typename T>
class MutantStack : public std::stack<T>
{
public:
    // Define iterator types
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;
    
    // Constructors
    MutantStack();
    MutantStack(const MutantStack<T> &other);
    MutantStack<T> &operator=(const MutantStack<T> &other);
    ~MutantStack();
    
    // Iterator methods (the magic!)
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
};
```

---

## Breaking Down the Code

### 1. Typedef for Iterators

```cpp
typedef typename std::stack<T>::container_type::iterator iterator;
```

**What does this mean?**
- `std::stack<T>::container_type` → Type of the internal container (deque)
- `::iterator` → Iterator type of that container
- `typedef ... iterator` → Create an alias called "iterator"

**In simple terms**: "Give me the iterator type of whatever container the stack uses internally"

---

### 2. Accessing the Protected Container

The magic happens here:
```cpp
template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
    return this->c.begin();  // Access protected member 'c'
}
```

**How it works**:
- `this->c` - Access the protected container from parent class
- `.begin()` - Call the container's begin() method
- Return the iterator

**Why we can access `c`**: We inherit from `std::stack`, so we have access to its protected members!

---

## Visual Representation

### Normal Stack (Can't Iterate):
```
std::stack<int> s;

┌───────────────────┐
│   std::stack      │
├───────────────────┤
│ top()    = 30     │  ← Can only see the top
│                   │
│ [Internal deque]  │
│   [10, 20, 30]    │  ← Can't access this!
└───────────────────┘
```

### MutantStack (Can Iterate):
```
MutantStack<int> mstack;

┌───────────────────┐
│   MutantStack     │
├───────────────────┤
│ top()    = 30     │  ← Can see the top
│ begin() ────┐     │  ← NEW! Access first element
│ end()   ────┘     │  ← NEW! Access past-last element
│                   │
│ [Internal deque]  │
│   [10, 20, 30]    │  ← Can iterate through this!
│    ↑   ↑   ↑      │
│   begin  end      │
└───────────────────┘
```

---

## Complete Implementation Explained

### Constructors and Destructor

```cpp
template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>() {
    // Call parent constructor
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T> &other) : std::stack<T>(other) {
    // Copy construction: call parent copy constructor
}

template <typename T>
MutantStack<T> &MutantStack<T>::operator=(const MutantStack<T> &other) {
    if (this != &other) {
        std::stack<T>::operator=(other);  // Call parent assignment
    }
    return *this;
}

template <typename T>
MutantStack<T>::~MutantStack() {
    // Nothing special needed, parent handles cleanup
}
```

**Key points**:
- Use parent class constructors/operators
- No need for special handling since we don't add new data members

---

### Iterator Methods (The Core Feature)

```cpp
template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin() {
    return this->c.begin();  // Access the internal container
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::begin() const {
    return this->c.begin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end() {
    return this->c.end();
}

template <typename T>
typename MutantStack<T>::const_iterator MutantStack<T>::end() const {
    return this->c.end();
}
```

**These methods**:
- Expose the internal container's iterators
- Allow traversal from bottom to top of the stack
- Work exactly like iterators on vector, list, etc.

---

## Usage Example with Explanation

```cpp
#include "MutantStack.hpp"
#include <iostream>

int main() {
    MutantStack<int> mstack;
    
    // Use like a normal stack
    mstack.push(5);
    mstack.push(17);
    
    std::cout << "Top: " << mstack.top() << std::endl;  // Output: 17
    
    mstack.pop();  // Remove 17
    std::cout << "Size: " << mstack.size() << std::endl;  // Output: 1
    
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    
    // Now for the magic - ITERATE through the stack!
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    
    std::cout << "Stack contents (bottom to top):" << std::endl;
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }
    
    return 0;
}
```

### Output:
```
Top: 17
Size: 1
Stack contents (bottom to top):
5
3
5
737
0
```

---

## Visual Execution Flow

```
Step-by-step execution:

1. push(5)           Stack: [5]
2. push(17)          Stack: [5, 17]
3. top() → 17        Stack: [5, 17]
4. pop()             Stack: [5]
5. push(3)           Stack: [5, 3]
6. push(5)           Stack: [5, 3, 5]
7. push(737)         Stack: [5, 3, 5, 737]
8. push(0)           Stack: [5, 3, 5, 737, 0]

9. Iteration:
   begin() → points to 5 (bottom)
   end() → points past 0 (top)
   
   Loop prints: 5, 3, 5, 737, 0 (bottom to top)
```

---

## Comparison with std::list

The exercise asks you to compare with `std::list` to show they work similarly:

```cpp
// MutantStack
MutantStack<int> mstack;
mstack.push(5);
mstack.push(17);

MutantStack<int>::iterator it = mstack.begin();
while (it != mstack.end()) {
    std::cout << *it << std::endl;
    ++it;
}

// std::list (same iteration pattern)
std::list<int> lst;
lst.push_back(5);
lst.push_back(17);

std::list<int>::iterator lit = lst.begin();
while (lit != lst.end()) {
    std::cout << *lit << std::endl;
    ++lit;
}
```

**Both produce the same output!** The iteration interface is identical.

---

## Key Concepts

### 1. Container Adapters
Stack, queue, and priority_queue are **adapters** - they provide a specific interface over an underlying container.

```
Stack Interface          Underlying Container
┌──────────────┐        ┌─────────────────┐
│ push()       │   →    │ push_back()     │
│ pop()        │   →    │ pop_back()      │
│ top()        │   →    │ back()          │
└──────────────┘        └─────────────────┘
```

### 2. Protected Inheritance Access
By inheriting from stack, we gain access to its protected member `c`.

### 3. Template Class Inheritance
```cpp
template <typename T>
class MutantStack : public std::stack<T>
```
We're inheriting from a template class, so our class must also be a template.

---

## Why "Mutant"?

It's called MutantStack because:
- It's a **mutation** of the normal stack
- It has **extra abilities** (iteration) that normal stacks don't have
- It's still a stack at its core, just enhanced

Like a superhero origin story - same person, but with new powers! 🦸‍♂️

---

## Important Template Syntax Notes

### 1. typename Keyword
```cpp
typename MutantStack<T>::iterator begin();
```
Needed because `MutantStack<T>::iterator` is a **dependent type** (depends on template parameter T).

### 2. Nested typedef
```cpp
typedef typename std::stack<T>::container_type::iterator iterator;
```
Creates an alias for a complex nested type.

### 3. this-> for Protected Members
```cpp
return this->c.begin();
```
Required in templates to access members from dependent base class.

---

## Common Mistakes to Avoid

❌ **Forgetting typename**:
```cpp
std::stack<T>::container_type::iterator it;  // Error!
```

✅ **Correct**:
```cpp
typename std::stack<T>::container_type::iterator it;
```

---

❌ **Trying to add new data members**:
```cpp
class MutantStack : public std::stack<T> {
    std::vector<T> myData;  // Don't! Use parent's container
};
```

✅ **Use parent's container**:
```cpp
return this->c.begin();  // Access parent's protected member
```

---

## Build and Test

```bash
# Compile
make

# Run
./mutantstack

# Clean
make fclean

# Rebuild
make re
```

---

## Expected Output
```
Top: 17
Size after pop: 1
MutantStack contents:
5
3
5
737
0

List contents:
5
3
5
737
0
```

---

## What You Learned

✅ How container adapters work  
✅ Inheriting from STL containers  
✅ Accessing protected members from parent class  
✅ Adding functionality to existing classes  
✅ Template class inheritance  
✅ Understanding stack's internal structure  
✅ Creating custom iterators  
✅ Comparing different container interfaces  

---

## Advanced Challenge

Try these modifications:
1. Add reverse iterators (`rbegin()`, `rend()`)
2. Make it work with different underlying containers (vector, list)
3. Add a method to iterate from top to bottom (reverse order)
4. Implement it with const-correctness throughout

---

## Key Takeaway

**MutantStack demonstrates a powerful C++ principle**: You can extend and modify existing classes (even from the standard library) to add new functionality while maintaining backward compatibility.

The stack still works as a stack, but now it's also iterable!

---

## Congratulations! 🎉

You've completed all three exercises and learned:
- Template functions and classes
- STL containers and algorithms
- Iterators and their usage
- Custom container design
- Container adapter modification
- Exception handling
- Generic programming principles

You now have a solid foundation in C++ STL and template programming!

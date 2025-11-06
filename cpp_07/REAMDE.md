# CPP_07 — C++ Templates

This module covers **C++ Templates**, one of the most powerful features of C++ that enables generic programming. Templates allow you to write code that works with any data type, making your programs more flexible, reusable, and type-safe.

---

## Table of Contents
1. [What are Templates?](#what-are-templates)
2. [Function Templates](#function-templates)
3. [Class Templates](#class-templates)
4. [Template Specialization](#template-specialization)
5. [Template Parameters](#template-parameters)
6. [Common Template Patterns](#common-template-patterns)
7. [Exercise Structure](#exercise-structure)
8. [Best Practices](#best-practices)
9. [Common Pitfalls](#common-pitfalls)

---

## What are Templates?

**Templates** are a C++ feature that allows you to write generic code that can work with different data types. Instead of writing separate functions or classes for each type, you write one template that the compiler can instantiate for any type you need.

### **Key Benefits:**
- **Code Reusability**: Write once, use with multiple types
- **Type Safety**: Compile-time type checking
- **Performance**: No runtime overhead (templates are resolved at compile time)
- **Flexibility**: Automatic type deduction in many cases

### **Template Instantiation:**
When you use a template with a specific type, the compiler creates a specialized version of that template for that type. This process is called **template instantiation**.

```cpp
// Template definition
template <typename T>
void printValue(T value) {
    std::cout << value << std::endl;
}

// Template instantiations (created by compiler)
printValue<int>(42);        // Creates printValue(int)
printValue<std::string>("Hello");  // Creates printValue(std::string)
```

---

## Function Templates

Function templates allow you to create generic functions that can work with different parameter types.

### **Basic Syntax:**
```cpp
template <typename T>
return_type function_name(T parameter) {
    // Function body
}
```

### **Example 1: Simple Function Template**
```cpp
#include <iostream>

// Function template to find maximum of two values
template <typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    // Automatic type deduction
    std::cout << max(10, 20) << std::endl;        // int version
    std::cout << max(3.14, 2.71) << std::endl;    // double version
    std::cout << max('a', 'z') << std::endl;      // char version
    
    // Explicit template parameter
    std::cout << max<float>(1.5f, 2.5f) << std::endl;
    
    return 0;
}
```

### **Example 2: Template with Multiple Parameters**
```cpp
template <typename T, typename U>
void printPair(T first, U second) {
    std::cout << "First: " << first << ", Second: " << second << std::endl;
}

int main() {
    printPair(42, "Hello");      // T=int, U=const char*
    printPair(3.14, 'A');       // T=double, U=char
    printPair(true, 100);       // T=bool, U=int
    
    return 0;
}
```

### **Example 3: Template with Return Type Deduction**
```cpp
// C++11 and later: auto return type
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

// C++14 and later: simplified auto
template <typename T, typename U>
auto multiply(T a, U b) {
    return a * b;
}

int main() {
    auto result1 = add(10, 3.5);        // Returns double
    auto result2 = multiply(4, 2.5f);   // Returns float
    
    std::cout << result1 << std::endl;  // 13.5
    std::cout << result2 << std::endl;  // 10
    
    return 0;
}
```

### **Example 4: Template Function with Array**
```cpp
template <typename T>
void printArray(T* arr, size_t size) {
    std::cout << "Array elements: ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Alternative with array reference (size known at compile time)
template <typename T, size_t N>
void printArrayRef(T (&arr)[N]) {
    std::cout << "Array elements: ";
    for (size_t i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    double decimals[] = {1.1, 2.2, 3.3};
    
    printArray(numbers, 5);     // Using pointer version
    printArray(decimals, 3);
    
    printArrayRef(numbers);     // Using reference version (size deduced)
    printArrayRef(decimals);
    
    return 0;
}
```

---

## Class Templates

Class templates allow you to create generic classes that can work with different data types.

### **Basic Syntax:**
```cpp
template <typename T>
class ClassName {
private:
    T member;
public:
    ClassName(T value) : member(value) {}
    T getValue() const { return member; }
};
```

### **Example 1: Simple Container Class**
```cpp
template <typename T>
class Box {
private:
    T value;

public:
    // Constructor
    Box(T val) : value(val) {}
    
    // Getter
    T getValue() const { return value; }
    
    // Setter
    void setValue(T val) { value = val; }
    
    // Method template within class template
    template <typename U>
    void printWithType(U other) const {
        std::cout << "Box value: " << value << ", Other: " << other << std::endl;
    }
};

int main() {
    Box<int> intBox(42);
    Box<std::string> stringBox("Hello");
    Box<double> doubleBox(3.14159);
    
    std::cout << intBox.getValue() << std::endl;     // 42
    std::cout << stringBox.getValue() << std::endl;  // Hello
    std::cout << doubleBox.getValue() << std::endl;  // 3.14159
    
    intBox.printWithType("World");  // Mixed types
    
    return 0;
}
```

### **Example 2: Dynamic Array Template Class**
```cpp
#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    // Constructor
    Array(size_t initialCapacity = 10) 
        : data(new T[initialCapacity]), size(0), capacity(initialCapacity) {}
    
    // Destructor
    ~Array() {
        delete[] data;
    }
    
    // Copy constructor
    Array(const Array& other) 
        : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    
    // Assignment operator
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            data = new T[other.capacity];
            size = other.size;
            capacity = other.capacity;
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Add element
    void push_back(const T& element) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = element;
    }
    
    // Access element
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // Const access
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    // Get size
    size_t getSize() const { return size; }
    
    // Print all elements
    void print() const {
        std::cout << "[";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

private:
    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
};

int main() {
    Array<int> intArray;
    intArray.push_back(1);
    intArray.push_back(2);
    intArray.push_back(3);
    intArray.print();  // [1, 2, 3]
    
    Array<std::string> stringArray;
    stringArray.push_back("Hello");
    stringArray.push_back("World");
    stringArray.print();  // [Hello, World]
    
    return 0;
}
```

### **Example 3: Template Class with Multiple Parameters**
```cpp
template <typename KeyType, typename ValueType>
class KeyValuePair {
private:
    KeyType key;
    ValueType value;

public:
    KeyValuePair(KeyType k, ValueType v) : key(k), value(v) {}
    
    KeyType getKey() const { return key; }
    ValueType getValue() const { return value; }
    
    void setValue(ValueType v) { value = v; }
    
    void print() const {
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }
};

int main() {
    KeyValuePair<int, std::string> pair1(1, "One");
    KeyValuePair<std::string, double> pair2("Pi", 3.14159);
    
    pair1.print();  // Key: 1, Value: One
    pair2.print();  // Key: Pi, Value: 3.14159
    
    return 0;
}
```

---

## Template Specialization

Template specialization allows you to provide specific implementations for certain types.

### **Full Template Specialization**
```cpp
// Generic template
template <typename T>
class Printer {
public:
    void print(T value) {
        std::cout << "Generic: " << value << std::endl;
    }
};

// Full specialization for bool
template <>
class Printer<bool> {
public:
    void print(bool value) {
        std::cout << "Boolean: " << (value ? "true" : "false") << std::endl;
    }
};

// Full specialization for const char*
template <>
class Printer<const char*> {
public:
    void print(const char* value) {
        std::cout << "C-String: \"" << value << "\"" << std::endl;
    }
};

int main() {
    Printer<int> intPrinter;
    Printer<bool> boolPrinter;
    Printer<const char*> stringPrinter;
    
    intPrinter.print(42);        // Generic: 42
    boolPrinter.print(true);     // Boolean: true
    stringPrinter.print("Hello"); // C-String: "Hello"
    
    return 0;
}
```

### **Partial Template Specialization (Class Templates Only)**
```cpp
// Primary template
template <typename T, typename U>
class Pair {
public:
    void info() {
        std::cout << "Generic pair of different types" << std::endl;
    }
};

// Partial specialization for same types
template <typename T>
class Pair<T, T> {
public:
    void info() {
        std::cout << "Pair of same types" << std::endl;
    }
};

// Partial specialization for pointer types
template <typename T>
class Pair<T*, T*> {
public:
    void info() {
        std::cout << "Pair of pointers" << std::endl;
    }
};

int main() {
    Pair<int, double> differentTypes;    // Uses primary template
    Pair<int, int> sameTypes;           // Uses partial specialization
    Pair<int*, int*> pointerTypes;      // Uses pointer specialization
    
    differentTypes.info();  // Generic pair of different types
    sameTypes.info();       // Pair of same types
    pointerTypes.info();    // Pair of pointers
    
    return 0;
}
```

### **Function Template Specialization**
```cpp
// Primary function template
template <typename T>
void processValue(T value) {
    std::cout << "Processing generic value: " << value << std::endl;
}

// Full specialization for const char*
template <>
void processValue<const char*>(const char* value) {
    std::cout << "Processing string: \"" << value << "\" (length: " 
              << strlen(value) << ")" << std::endl;
}

// Full specialization for bool
template <>
void processValue<bool>(bool value) {
    std::cout << "Processing boolean: " << std::boolalpha << value << std::endl;
}

int main() {
    processValue(42);           // Generic version
    processValue("Hello");      // Specialized for const char*
    processValue(true);         // Specialized for bool
    processValue(3.14);         // Generic version
    
    return 0;
}
```

---

## Template Parameters

### **Type Parameters**
```cpp
template <typename T>  // or template <class T>
class Container {
    T data;
};
```

### **Non-Type Parameters**
```cpp
template <typename T, size_t SIZE>
class FixedArray {
private:
    T data[SIZE];
    
public:
    size_t size() const { return SIZE; }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
};

int main() {
    FixedArray<int, 5> intArray;     // Array of 5 integers
    FixedArray<double, 10> doubleArray; // Array of 10 doubles
    
    intArray[0] = 42;
    std::cout << "Size: " << intArray.size() << std::endl;  // Size: 5
    
    return 0;
}
```

### **Template Template Parameters**
```cpp
// Template that takes another template as parameter
template <typename T, template <typename> class Container>
class Wrapper {
private:
    Container<T> container;
    
public:
    void add(const T& item) {
        // Assuming Container has push_back method
        container.push_back(item);
    }
    
    void print() const {
        // Custom print logic here
        std::cout << "Wrapper contains items" << std::endl;
    }
};

// Note: This is an advanced concept rarely used in basic exercises
```

### **Default Template Parameters**
```cpp
template <typename T = int, size_t SIZE = 10>
class DefaultArray {
private:
    T data[SIZE];
    
public:
    size_t size() const { return SIZE; }
};

int main() {
    DefaultArray<> defaultArray;           // T=int, SIZE=10
    DefaultArray<double> doubleArray;      // T=double, SIZE=10
    DefaultArray<char, 20> charArray;      // T=char, SIZE=20
    
    return 0;
}
```

---

## Common Template Patterns

### **1. SFINAE (Substitution Failure Is Not An Error)**
```cpp
#include <type_traits>

// Enable function only for integral types
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
printIfInteger(T value) {
    std::cout << "Integer: " << value << std::endl;
}

// Enable function only for floating-point types
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
printIfFloat(T value) {
    std::cout << "Float: " << value << std::endl;
}

int main() {
    printIfInteger(42);     // Works
    printIfFloat(3.14);     // Works
    // printIfInteger(3.14); // Compilation error
    // printIfFloat(42);     // Compilation error
    
    return 0;
}
```

### **2. Template Metaprogramming - Factorial at Compile Time**
```cpp
// Compile-time factorial calculation
template <int N>
struct Factorial {
    static const int value = N * Factorial<N - 1>::value;
};

// Specialization for base case
template <>
struct Factorial<0> {
    static const int value = 1;
};

int main() {
    const int fact5 = Factorial<5>::value;  // Calculated at compile time
    std::cout << "5! = " << fact5 << std::endl;  // 120
    
    return 0;
}
```

### **3. Iterator Template Pattern**
```cpp
template <typename T>
class SimpleVector {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    // Iterator class
    class Iterator {
    private:
        T* ptr;
        
    public:
        Iterator(T* p) : ptr(p) {}
        
        T& operator*() { return *ptr; }
        Iterator& operator++() { ++ptr; return *this; }
        bool operator!=(const Iterator& other) { return ptr != other.ptr; }
    };
    
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + size); }
    
    // Constructor, destructor, other methods...
    SimpleVector() : data(new T[10]), size(0), capacity(10) {}
    ~SimpleVector() { delete[] data; }
    
    void push_back(const T& item) {
        if (size < capacity) {
            data[size++] = item;
        }
    }
};

int main() {
    SimpleVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    
    // Range-based for loop works with iterators
    for (auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

---

## Exercise Structure

Typically, cpp_07 exercises follow this structure:

### **Exercise 00: Function Templates**
- **Objective**: Implement basic function templates
- **Concepts**: Template syntax, type deduction, template instantiation
- **Common Functions**:
  ```cpp
  template<typename T>
  void swap(T& a, T& b);
  
  template<typename T>
  T min(T a, T b);
  
  template<typename T>
  T max(T a, T b);
  ```

### **Exercise 01: Iter Function**
- **Objective**: Create a template function that applies another function to array elements
- **Concepts**: Function templates with function pointers/functors
- **Example**:
  ```cpp
  template<typename T>
  void iter(T* array, size_t length, void (*func)(T&));
  ```

### **Exercise 02: Array Class Template**
- **Objective**: Implement a template class for arrays with bounds checking
- **Concepts**: Class templates, exception handling, operator overloading
- **Example**:
  ```cpp
  template<typename T>
  class Array {
      // Implementation with operator[], size(), etc.
  };
  ```

---

## Best Practices

### **✅ DO:**

1. **Use Clear Template Parameter Names**
   ```cpp
   template <typename ElementType>  // Better than 'T'
   class Container { /* ... */ };
   ```

2. **Provide Template Specializations When Needed**
   ```cpp
   // Special handling for string types
   template <>
   void process<std::string>(const std::string& str) {
       // String-specific implementation
   }
   ```

3. **Use Concepts (C++20) or SFINAE for Type Constraints**
   ```cpp
   template <typename T>
   typename std::enable_if<std::is_arithmetic<T>::value, T>::type
   add(T a, T b) {
       return a + b;
   }
   ```

4. **Document Template Requirements**
   ```cpp
   // Requires: T must have operator< defined
   template <typename T>
   T min(T a, T b) {
       return (a < b) ? a : b;
   }
   ```

5. **Use Auto for Complex Return Types**
   ```cpp
   template <typename T, typename U>
   auto multiply(T a, U b) -> decltype(a * b) {
       return a * b;
   }
   ```

### **❌ DON'T:**

1. **Overuse Templates**
   - Don't make everything a template if it's not needed
   - Simple functions for specific types don't need templates

2. **Forget Exception Safety**
   ```cpp
   template <typename T>
   class Container {
       T* data;
   public:
       ~Container() { delete[] data; }  // Always clean up
   };
   ```

3. **Ignore Compilation Time**
   - Complex templates can significantly increase compilation time
   - Use forward declarations when possible

4. **Make Templates Too Complex**
   - Keep templates simple and focused
   - Break complex templates into smaller, manageable pieces

---

## Common Pitfalls

### **1. Template Instantiation Issues**
```cpp
// Problem: Template defined in .cpp file
// Solution: Define templates in header files

// header.hpp
template <typename T>
void myFunction(T value);  // Declaration only

// source.cpp
template <typename T>
void myFunction(T value) {  // Definition
    std::cout << value << std::endl;
}
// This won't work! Template definitions must be visible at instantiation
```

### **2. Ambiguous Template Calls**
```cpp
template <typename T>
void func(T value) { std::cout << "Generic" << std::endl; }

void func(int value) { std::cout << "Specific int" << std::endl; }

int main() {
    func(42);        // Calls specific int version (exact match preferred)
    func<int>(42);   // Forces template version
    func(42.0);      // Calls template version (no exact match)
}
```

### **3. Template Argument Deduction Failures**
```cpp
template <typename T>
void process(T* ptr) { /* ... */ }

int main() {
    int arr[10];
    process(arr);     // OK: arr decays to int*
    
    std::vector<int> vec;
    // process(vec);  // Error: std::vector<int> is not a pointer type
}
```

### **4. Const Issues with Templates**
```cpp
template <typename T>
void modify(T& value) {
    value = T{};  // Modify the value
}

int main() {
    const int x = 42;
    // modify(x);  // Error: cannot modify const value
    
    // Solution: Provide const version or use perfect forwarding
}
```

---

## Example Makefile for Templates

```makefile
NAME = template_program

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = src
OBJDIR = obj
INCDIR = include

SOURCES = main.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

---

## Summary

| Concept | Description | Use Case |
|---------|-------------|----------|
| **Function Templates** | Generic functions for any type | Utility functions (max, min, swap) |
| **Class Templates** | Generic classes for any type | Containers, data structures |
| **Template Specialization** | Custom behavior for specific types | Type-specific optimizations |
| **Non-Type Parameters** | Compile-time constants as parameters | Fixed-size arrays, compile-time values |
| **SFINAE** | Enable/disable templates based on type properties | Type-safe generic programming |
| **Template Metaprogramming** | Computation at compile-time | Performance optimizations |

Templates are a powerful feature that enables:
- **Code reuse** across different types
- **Type safety** with compile-time checking  
- **Performance** with zero runtime overhead
- **Flexibility** in API design

Master these concepts to write efficient, reusable C++ code! 🚀
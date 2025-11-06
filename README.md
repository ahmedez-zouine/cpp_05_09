### CPP DAYS 05 - 09

## cpp_06 — Casting in C++

This workspace contains a `cpp_06` directory with small exercises that demonstrate different kinds of casts in C++ and common conversion scenarios. Casting is the process of converting data from one type to another, and C++ provides several mechanisms to do this safely and explicitly.

---

## Table of Contents
1. [What is Casting?](#what-is-casting)
2. [Types of Casts in C++](#types-of-casts-in-c++)
3. [Exercise Breakdown](#exercise-breakdown)
4. [Edge Cases and Best Practices](#edge-cases-and-best-practices)
5. [How to Build and Run](#how-to-build-and-run)

---

## What is Casting?

**Casting** is a type conversion technique used to explicitly convert a value from one data type to another. In C++, there are two main approaches:

### **C-Style Casting (Implicit Conversions)**
```cpp
int i = 10;
double d = (double)i;  // C-style cast
float f = (float)d;    // Another C-style cast
```

**Problems with C-style casts:**
- **Implicit behavior**: Performs multiple conversion types without making intent clear
- **Unsafe**: Can silently perform dangerous conversions
- **Hard to find**: Difficult to search for in code (same syntax as type declarations)
- **No compile-time safety**: Can hide bugs

---

## Types of Casts in C++

C++ provides **four explicit cast operators** for different scenarios:

### **1. `static_cast<T>(value)` — Compile-Time Safe Conversions**

**Purpose**: Performs well-defined, compile-time type conversions without runtime checks.

**Use Cases:**
- Converting between numeric types (int ↔ double ↔ float)
- Upcasting pointers to base classes (safe because no runtime check needed)
- Converting enums to integers

**Characteristics:**
- Checked at compile time
- No runtime overhead
- Cannot be used for downcasting (may cause undefined behavior)
- Cannot remove `const` or `volatile`

**Example:**
```cpp
// Numeric conversions
int intValue = 42;
double doubleValue = static_cast<double>(intValue);  // 42.0

// Pointer upcasting (Derived* → Base*)
class Animal {};
class Dog : public Animal {};

Dog* myDog = new Dog();
Animal* myAnimal = static_cast<Animal*>(myDog);  // Safe upcasting

// Downcasting (DANGEROUS - may cause undefined behavior)
Animal* basePtr = new Dog();
Dog* dogPtr = static_cast<Dog*>(basePtr);  // Compiles but not safe!
// If basePtr doesn't actually point to Dog, this is undefined behavior
```

---

### **2. `dynamic_cast<T>(ptr_or_ref)` — Runtime-Checked Polymorphic Casting**

**Purpose**: Safely casts pointers and references in polymorphic class hierarchies with runtime type checking.

**Use Cases:**
- Downcasting (Base* → Derived*)
- Safe type identification at runtime
- When you need to verify an object's actual type

**Characteristics:**
- Checked at **runtime** (slight performance overhead)
- Returns `nullptr` if pointer cast fails
- Throws `std::bad_cast` exception if reference cast fails
- **Only works with polymorphic types** (classes with virtual functions)
- Cannot be used on non-polymorphic types

**Example:**
```cpp
class Shape {
public:
    virtual ~Shape() {}
    virtual void draw() = 0;
};

class Circle : public Shape {
public:
    void draw() override { std::cout << "Drawing Circle\n"; }
    void rollAround() { std::cout << "Rolling...\n"; }
};

class Square : public Shape {
public:
    void draw() override { std::cout << "Drawing Square\n"; }
};

// Usage
Shape* shape = new Circle();

// Safe downcasting with runtime check
Circle* circle = dynamic_cast<Circle*>(shape);
if (circle != nullptr) {
    circle->rollAround();  // Safe to call Circle-specific method
} else {
    std::cout << "Not a Circle!\n";
}

// With references (throws exception on failure)
try {
    Circle& circleRef = dynamic_cast<Circle&>(*shape);
    circleRef.rollAround();
} catch (const std::bad_cast& e) {
    std::cout << "Cast failed: " << e.what() << "\n";
}
```

---

### **3. `reinterpret_cast<T>(value)` — Low-Level Bit Pattern Reinterpretation**

**Purpose**: Reinterprets the underlying bit pattern of a value (typically for pointer/integer conversions).

**Use Cases:**
- Converting between unrelated pointer types (rarely needed)
- Storing pointers as integers
- Low-level memory manipulation
- Serialization/deserialization of pointers

**Characteristics:**
- **Most dangerous** cast type
- No safety checks whatsoever
- Can easily cause undefined behavior
- Should be avoided unless absolutely necessary
- Use only when you understand the memory layout exactly

**Example:**
```cpp
// Storing a pointer as an integer (for serialization)
class Data {
public:
    int value;
};

Data* originalPtr = new Data{42};

// Convert pointer to integer for storage/transmission
intptr_t ptrAsInt = reinterpret_cast<intptr_t>(originalPtr);
std::cout << "Pointer as integer: " << ptrAsInt << "\n";

// Convert back to pointer
Data* restoredPtr = reinterpret_cast<Data*>(ptrAsInt);
std::cout << "Restored value: " << restoredPtr->value << "\n";  // 42

delete restoredPtr;

// DANGEROUS: Converting between unrelated pointer types
int* intPtr = new int(100);
char* charPtr = reinterpret_cast<char*>(intPtr);  // Unsafe!
// Now charPtr points to an int, treating it as a char
// Accessing it will likely cause crashes or undefined behavior
```

---

### **4. `const_cast<T>(value)` — Adding or Removing Const/Volatile**

**Purpose**: Adds or removes `const` and `volatile` qualifiers.

**Use Cases:**
- Calling non-const functions on const objects (when you're certain it's safe)
- Compatibility with legacy APIs
- Removing `volatile` from variables

**Characteristics:**
- Only cast that can remove `const` and `volatile`
- Still performs type checking (type must be same except for const/volatile)
- **Only safe if the original object wasn't declared `const`**
- Modifying a truly const object leads to undefined behavior

**Example:**
```cpp
class ConfigData {
private:
    mutable int cache;  // Can be modified even in const objects
    int realData;
public:
    void printData() const {
        std::cout << "Data: " << realData << "\n";
    }
    
    void updateCache() const {
        cache = 100;  // OK because cache is mutable
    }
};

int main() {
    const int constValue = 42;
    
    // DANGEROUS: Modifying a true const object
    // int* ptr = const_cast<int*>(&constValue);
    // *ptr = 100;  // Undefined behavior!
    
    // SAFE: The variable wasn't originally const
    int normalValue = 50;
    const int& constRef = normalValue;
    int* ptr = const_cast<int*>(&constRef);
    *ptr = 60;  // OK - modifies the original non-const object
    std::cout << "Normal value: " << normalValue << "\n";  // 60
}
```

---

## Comparison Table

| Cast Type | Compile-Time | Runtime Check | Safe | Use Case |
|-----------|--------------|----------------|------|----------|
| C-style `(T)v` | ✓ | ✗ | ✗ | Legacy code only |
| `static_cast<T>(v)` | ✓ | ✗ | ✓* | Numeric, upcasting |
| `dynamic_cast<T>(v)` | ✓ | ✓ | ✓ | Polymorphic downcasting |
| `reinterpret_cast<T>(v)` | ✓ | ✗ | ✗ | Low-level pointer tricks |
| `const_cast<T>(v)` | ✓ | ✗ | ✓** | Remove const qualifiers |

*`static_cast` safe for upcasting only; downcasting is unsafe
**`const_cast` safe only if original object wasn't truly const

---

## Exercise Breakdown

### **cpp_06/ex00/ — ScalarConverter**

**Objective**: Convert a string input to all scalar types and display the results.

**Concepts Used:**
- Parsing strings to different types
- `static_cast` for numeric conversions
- Handling edge cases (overflow, underflow, special values like NaN and infinity)
- Character display logic (printable vs non-displayable)

**Key Points:**
```
Input: "42"
Output:
  char: '*'
  int: 42
  float: 42.0f
  double: 42.0

Input: "4.5"
Output:
  char: Non displayable
  int: 4
  float: 4.5f
  double: 4.5

Input: "inf"
Output:
  char: impossible
  int: impossible
  float: +inff
  double: +inf
```

---

### **cpp_06/ex01/ — Serializer**

**Objective**: Serialize and deserialize a pointer to an integer.

**Concepts Used:**
- `reinterpret_cast` for pointer-to-integer conversion
- `uintptr_t` type for guaranteed size
- Pointer restoration

**Explanation:**
```cpp
Data* originalPtr = new Data();
// Serialization: Convert pointer to integer for storage
uintptr_t serialized = Serializer::serialize(originalPtr);

// Deserialization: Convert integer back to pointer
Data* restored = Serializer::deserialize(serialized);

// Should be the same object
assert(restored == originalPtr);
```

**Why This is Useful:**
- Transmit object references over networks as integers
- Store pointers in serialized formats
- Save object addresses in files

---

### **cpp_06/ex02/ — Runtime Polymorphism with dynamic_cast**

**Objective**: Create a polymorphic hierarchy and use `dynamic_cast` to identify actual types at runtime.

**Class Hierarchy:**
```
       Base (virtual destructor)
        / | \
       /  |  \
      A   B   C
```

**Concepts Used:**
- Virtual functions for polymorphism
- `dynamic_cast` to determine actual derived type
- Runtime type identification (RTTI - Run-Time Type Information)

**Example Flow:**
```cpp
Base* ptr = generateRandomDerivedObject();  // Could be A, B, or C

// Identify the actual type at runtime
if (dynamic_cast<A*>(ptr)) {
    std::cout << "It's an A!\n";
} else if (dynamic_cast<B*>(ptr)) {
    std::cout << "It's a B!\n";
} else if (dynamic_cast<C*>(ptr)) {
    std::cout << "It's a C!\n";
}
```

---

## Edge Cases and Best Practices

### **Edge Cases to Watch For**

1. **Character Conversion Overflow**
   ```cpp
   int huge = 1000;
   char c = static_cast<char>(huge);  // Wraps around due to overflow
   // Result is undefined/implementation-specific
   ```

2. **Floating-Point Precision Loss**
   ```cpp
   float f = 3.14159265359f;  // Loses precision (float has ~7 digits)
   double d = 3.14159265359;  // More precise
   ```

3. **Dynamic Cast Failures**
   ```cpp
   Base* base = new A();
   B* b = dynamic_cast<B*>(base);  // Returns nullptr (not a B)
   if (b == nullptr) {
       std::cout << "Failed cast, b is not of type B\n";
   }
   ```

4. **Special Float Values**
   ```cpp
   float inf = std::numeric_limits<float>::infinity();
   float nan = std::numeric_limits<float>::quiet_NaN();
   int i1 = static_cast<int>(inf);  // Undefined behavior
   int i2 = static_cast<int>(nan);  // Undefined behavior
   ```

### **Best Practices**

✅ **DO:**
- Use `dynamic_cast` for safe polymorphic downcasting
- Prefer `static_cast` over C-style casts
- Always check if `dynamic_cast` succeeded before using result
- Use `const_cast` sparingly and only when necessary
- Document why you're using dangerous casts
- Add RTTI (`-frtti` flag) support when using `dynamic_cast`

❌ **DON'T:**
- Use `reinterpret_cast` unless absolutely necessary
- Cast away `const` from objects that were originally `const`
- Use C-style casts
- Downcast with `static_cast` when `dynamic_cast` would be safer
- Ignore compiler warnings about unsafe conversions

---

## How to Build and Run

### **Building the Exercises**

From the workspace root, build individual exercises:

```bash
# Build Exercise 00 - ScalarConverter
cd cpp_06/ex00 && make

# Build Exercise 01 - Serializer
cd cpp_06/ex01 && make

# Build Exercise 02 - Base/Derived Classes
cd cpp_06/ex02 && make
```

### **Running the Exercises**

**Exercise 00 - ScalarConverter:**
```bash
cd cpp_06/ex00
./ScalarConverter "0"
./ScalarConverter "42"
./ScalarConverter "3.14"
./ScalarConverter "-99"
./ScalarConverter "inf"
./ScalarConverter "nan"
```

**Exercise 01 - Serializer:**
```bash
cd cpp_06/ex01
./Serializer
# Output shows serialization and deserialization of pointers
```

**Exercise 02 - Base/Derived:**
```bash
cd cpp_06/ex02
./a.out
# Output shows runtime type identification with dynamic_cast
```

### **Compile with RTTI Support**

Most of these exercises require Runtime Type Information (RTTI) for `dynamic_cast` to work. Ensure your Makefile includes:

```makefile
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -frtti
```

The `-frtti` flag enables Run-Time Type Information (RTTI) support.

---

## Complete Example: Polymorphism and Casting

Here's a real-world example demonstrating all casting types:

```cpp
#include <iostream>
#include <typeinfo>
using namespace std;

class Vehicle {
public:
    virtual ~Vehicle() {}
    virtual void describe() const = 0;
};

class Car : public Vehicle {
public:
    void describe() const override {
        cout << "I am a Car with 4 wheels\n";
    }
    void honk() { cout << "Beep beep!\n"; }
};

class Bicycle : public Vehicle {
public:
    void describe() const override {
        cout << "I am a Bicycle with 2 wheels\n";
    }
};

int main() {
    // Create vehicle pointers
    Vehicle* v1 = new Car();
    Vehicle* v2 = new Bicycle();
    
    // 1. Using static_cast (compile-time, upcast is safe)
    // Vehicle* to Car* (downcast - not safe with static_cast!)
    
    // 2. Using dynamic_cast (runtime-checked, safe downcasting)
    Car* car = dynamic_cast<Car*>(v1);
    if (car != nullptr) {
        car->honk();  // Safe - we know it's a Car
    }
    
    // Try downcasting v2 (which is a Bicycle) to Car
    car = dynamic_cast<Car*>(v2);
    if (car == nullptr) {
        cout << "v2 is not a Car\n";
    }
    
    // 3. Using const_cast
    const Vehicle& constVehicle = *v1;
    Vehicle& nonConstVehicle = const_cast<Vehicle&>(constVehicle);
    nonConstVehicle.describe();
    
    // 4. Using reinterpret_cast (dangerous - only for special cases)
    intptr_t vehicleAsInt = reinterpret_cast<intptr_t>(v1);
    cout << "Vehicle address as integer: " << vehicleAsInt << "\n";
    
    delete v1;
    delete v2;
    
    return 0;
}
```

---

## Summary

| Topic | Key Points |
|-------|-----------|
| **C++ Casting** | Four explicit operators for type conversion |
| **static_cast** | Compile-time, safe for numeric and upcasting |
| **dynamic_cast** | Runtime-checked, safe for polymorphic downcasting |
| **reinterpret_cast** | Low-level bit manipulation, use rarely |
| **const_cast** | Remove/add const qualifiers, use carefully |
| **Polymorphism** | Virtual functions enable safe runtime type checking |
| **RTTI** | Run-Time Type Information required for dynamic_cast |

This comprehensive guide covers all major casting concepts in C++. Study each exercise to see these concepts in action!


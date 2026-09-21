# CPP Module 06 — C++ Casts

This module focuses on the four explicit C++ type casting operators (`static_cast`, `dynamic_cast`, `reinterpret_cast`, and `const_cast`), runtime type identification (RTTI), and numeric literal parsing.

---

## Table of Contents
1. [C++ Cast Operators](#c-cast-operators)
2. [Comparison of Cast Types](#comparison-of-cast-types)
3. [Exercise Breakdown](#exercise-breakdown)
4. [How to Build & Run](#how-to-build--run)
5. [Additional Notes & Educational Demos](#additional-notes--educational-demos)

---

## C++ Cast Operators

### 1. `static_cast<T>(value)` — Compile-Time Safe Conversions
- **Purpose**: Performs well-defined, compile-time conversions without runtime overhead.
- **Use Cases**:
  - Conversions between arithmetic types (`int`, `float`, `double`, `char`).
  - Safe upcasting in class hierarchies (`Derived*` to `Base*`).
  - Converting unscoped enums to integers.
- **Limitations**: Cannot remove `const`/`volatile`; downcasting without checks is unsafe.

### 2. `dynamic_cast<T>(ptr_or_ref)` — Runtime-Checked Polymorphic Casts
- **Purpose**: Safely navigates polymorphic inheritance hierarchies (`Base` must have at least one `virtual` function, e.g. virtual destructor).
- **Use Cases**: Safe downcasting from `Base*` to `Derived*`.
- **Behavior**:
  - **Pointers**: Returns `NULL` if the cast fails.
  - **References**: Throws `std::bad_cast` exception if the cast fails.

### 3. `reinterpret_cast<T>(value)` — Low-Level Bit Pattern Reinterpretation
- **Purpose**: Low-level conversion between unrelated pointer types or pointer and integer types (`uintptr_t`).
- **Use Cases**: Serialization/deserialization, memory offsets, interfacing with hardware or C APIs.
- **Behavior**: Does not modify underlying bit patterns; no runtime checks.

### 4. `const_cast<T>(value)` — Adding or Removing Const/Volatile
- **Purpose**: Explicitly casts away `const` or `volatile` qualifiers.
- **Safety**: Only safe when the underlying object was originally instantiated as non-const.

---

## Comparison of Cast Types

| Cast Type | Checked At | Runtime Cost | Primary Use Case |
|---|---|---|---|
| `static_cast<T>` | Compile time | None | Numeric conversions, safe upcasting |
| `dynamic_cast<T>` | Runtime | Low (vtable check) | Polymorphic downcasting & identification |
| `reinterpret_cast<T>` | Compile time | None | Pointer-to-integer (`uintptr_t`), raw bits |
| `const_cast<T>` | Compile time | None | Casting away `const` modifier |

---

## Exercise Breakdown

### [ex00 — Conversion of scalar types](ex00)
- **Goal**: Parse a C++ literal from a string and convert it to its scalar representations: `char`, `int`, `float`, `double`.
- **Key Class**: `ScalarConverter` (Static utility class).
- **Key Details**:
  - Handles pseudo-literals: `-inff`, `+inff`, `nanf`, `-inf`, `+inf`, `nan`.
  - Proper formatting using `std::setprecision(1)` and `std::fixed`.
  - Detects overflows and non-displayable characters (`isprint`).

### [ex01 — Serialization](ex01)
- **Goal**: Convert a pointer to an integer type and back without data loss.
- **Key Class**: `Serializer` (Static class).
  - `uintptr_t serialize(Data* ptr);`
  - `Data* deserialize(uintptr_t raw);`
- **Concept**: Uses `reinterpret_cast` to demonstrate pointer serialization.

### [ex02 — Identify real type](ex02)
- **Goal**: Instantiate a random derived class (`A`, `B`, or `C`) and dynamically determine its true type without storing type tags.
- **Key Class**: `Base` with a virtual destructor.
- **Functions**:
  - `Base * generate(void);`
  - `void identify(Base* p);` (uses `dynamic_cast` pointer check against `NULL`)
  - `void identify(Base& p);` (uses `dynamic_cast` reference check with `try / catch (std::bad_cast &e)`)

---

## How to Build & Run

Every exercise includes a standard Makefile adhering to 42 requirements:
```bash
# Build & run ex00
cd cpp_06/ex00 && make && ./convert 42.0f

# Build & run ex01
cd ../ex01 && make && ./Serialization

# Build & run ex02
cd ../ex02 && make && ./Identify
```

---

## Additional Notes & Educational Demos

Detailed explanations, visual ASCII guides, and isolated demonstration scripts are located in the [notes/](notes/) directory:
- [static_cast explanation](notes/static_cast_explained.cpp) & [visual summary](notes/static_cast_visual_explanation.md)
- [dynamic_cast explanation](notes/dynamic_cast_explanation.cpp) & [visual summary](notes/dynamic_cast_visual_explanation.md)
- [reinterpret_cast explanation](notes/reinterpret_cast_explained.cpp)
- [ScalarConverter analysis](notes/ScalarConverter_Explanation.md) & [visual summary](notes/ScalarConverter_Visual_Summary.md)
- [Special floating point values](notes/special_floating_point_values.md)

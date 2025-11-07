# cpp_06 — Exercises (ex00, ex01, ex02)

Short overview of the three exercises in this folder, how to build and run them, the main concepts used and short examples for tests.

## Project layout
- [cpp_06/ex00](cpp_06/ex00) — Scalar literal conversion
  - [cpp_06/ex00/ScalarConverter.hpp](cpp_06/ex00/ScalarConverter.hpp)
  - [cpp_06/ex00/ScalarConverter.cpp](cpp_06/ex00/ScalarConverter.cpp) — contains [`ScalarConverter::convert`](cpp_06/ex00/ScalarConverter.cpp)
  - [cpp_06/ex00/main.cpp](cpp_06/ex00/main.cpp)
  - [cpp_06/ex00/Makefile](cpp_06/ex00/Makefile)
  - [cpp_06/ex00/readme.md](cpp_06/ex00/readme.md)
- [cpp_06/ex01](cpp_06/ex01) — Pointer <-> integer serialization
  - [cpp_06/ex01/Serializer.hpp](cpp_06/ex01/Serializer.hpp) — defines `Data` struct and `Serializer` interface
  - [cpp_06/ex01/Serializer.cpp](cpp_06/ex01/Serializer.cpp) — implements [`Serializer::serialize`](cpp_06/ex01/Serializer.cpp) and [`Serializer::deserialize`](cpp_06/ex01/Serializer.cpp)
  - [cpp_06/ex01/main.cpp](cpp_06/ex01/main.cpp)
  - [cpp_06/ex01/Makefile](cpp_06/ex01/Makefile)
- [cpp_06/ex02](cpp_06/ex02) — RTTI / identification
  - [cpp_06/ex02/Base.hpp](cpp_06/ex02/Base.hpp), [cpp_06/ex02/Base.cpp](cpp_06/ex02/Base.cpp) — includes [`generate`](cpp_06/ex02/Base.cpp), [`identify(Base *)`](cpp_06/ex02/Base.cpp) and [`identify(Base &)`](cpp_06/ex02/Base.cpp)
  - [cpp_06/ex02/A.hpp](cpp_06/ex02/A.hpp), [cpp_06/ex02/B.hpp](cpp_06/ex02/B.hpp), [cpp_06/ex02/C.hpp](cpp_06/ex02/C.hpp)
  - [cpp_06/ex02/main.cpp](cpp_06/ex02/main.cpp)
  - [cpp_06/ex02/Makefile](cpp_06/ex02/Makefile)

All Makefiles compile with `-std=c++98 -Wall -Wextra -Werror`.

---

## Concepts & Notes

### ex00 — ScalarConverter
- Goal: parse a string literal and print conversions to:
  - char, int, float, double.
- Key behavior implemented in [`ScalarConverter::convert`](cpp_06/ex00/ScalarConverter.cpp).
- Handles special values (`nan`, `inf`, `-inf`, with/without trailing `f`) and single-char literals.
- Demonstrates: string parsing, std::strtod, numeric limits, isprint/isnan and formatted output with iomanip.

Example usage:
- Build:
  - cd cpp_06/ex00 && make
- Run examples:
  - ./convert 42
  - ./convert a
  - ./convert 42.0f
  - ./convert nan
- Expected (sample) outputs:
  - ./convert 42
    - char: '*displayable or numeric*' / int: 42 / float: 42.0f / double: 42.0
  - ./convert a
    - char: 'a' / int: 97 / float: 97.0f / double: 97.0
  - ./convert nan
    - char: impossible / int: impossible / float: nanf / double: nan

Files:
- [`cpp_06/ex00/ScalarConverter.hpp`](cpp_06/ex00/ScalarConverter.hpp)
- [`cpp_06/ex00/ScalarConverter.cpp`](cpp_06/ex00/ScalarConverter.cpp)
- [`cpp_06/ex00/main.cpp`](cpp_06/ex00/main.cpp)

### ex01 — Serializer
- Goal: show how a pointer can be converted to an integer type and back safely using `reinterpret_cast`.
- `Data` struct is defined in [`cpp_06/ex01/Serializer.hpp`](cpp_06/ex01/Serializer.hpp).
- Implementations:
  - [`Serializer::serialize`](cpp_06/ex01/Serializer.cpp)
  - [`Serializer::deserialize`](cpp_06/ex01/Serializer.cpp)
- Demonstrates: use of `uintptr_t`, reinterpret casts, pointer identity verification.

Example usage:
- Build:
  - cd cpp_06/ex01 && make
- Run:
  - ./Serialization
- Expected output pattern (see `main.cpp`):
  - prints original pointer and value, serialized numeric value, deserialized pointer and value, then `SUCCESS` if pointers match, and shows modification via deserialized pointer.

Files:
- [`cpp_06/ex01/Serializer.hpp`](cpp_06/ex01/Serializer.hpp)
- [`cpp_06/ex01/Serializer.cpp`](cpp_06/ex01/Serializer.cpp)
- [`cpp_06/ex01/main.cpp`](cpp_06/ex01/main.cpp)

### ex02 — RTTI and identify
- Goal: generate a random instance of one of three derived classes (`A`, `B`, `C`) and identify which one was created at runtime.
- Functions:
  - [`generate`](cpp_06/ex02/Base.cpp) — constructs `A`, `B` or `C` randomly.
  - [`identify(Base *)`](cpp_06/ex02/Base.cpp) — uses `dynamic_cast` on pointers.
  - [`identify(Base &)`](cpp_06/ex02/Base.cpp) — uses `dynamic_cast` with reference and exceptions.
- Demonstrates: polymorphism, virtual destructor, RTTI via `dynamic_cast`, and random selection.

Example usage:
- Build:
  - cd cpp_06/ex02 && make
- Run:
  - ./Identify
- Expected output:
  - `generate()` prints or returns a random type (implementation prints the generated index in some versions), and `identify` prints `A`, `B`, or `C` twice (once for pointer-based identify and once for reference-based identify).

Files:
- [`cpp_06/ex02/Base.hpp`](cpp_06/ex02/Base.hpp)
- [`cpp_06/ex02/Base.cpp`](cpp_06/ex02/Base.cpp)
- [`cpp_06/ex02/A.hpp`](cpp_06/ex02/A.hpp)
- [`cpp_06/ex02/B.hpp`](cpp_06/ex02/B.hpp)
- [`cpp_06/ex02/C.hpp`](cpp_06/ex02/C.hpp)
- [`cpp_06/ex02/main.cpp`](cpp_06/ex02/main.cpp)

---

## Build & test quickly
One-liners per exercise:
- ex00:
  - cd cpp_06/ex00 && make && ./convert 42
- ex01:
  - cd cpp_06/ex01 && make && ./Serialization
- ex02:
  - cd cpp_06/ex02 && make && ./Identify

If you want I can:
- Add more example inputs and exact sample outputs for each test case.
- Add a small CI script (shell) that builds & runs all three exercises and reports results.

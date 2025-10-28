### CPP DAYS 05 - 09

## cpp_06 — Casting in C++

This workspace contains a `cpp_06` directory with small exercises that demonstrate different kinds of casts in C++ and common conversion scenarios.

Relevant folders and files

- `cpp_06/ex00/` — `ScalarConverter.cpp`, `ScalarConverter.hpp`, `main.cpp`, `Makefile`
  - Converts input strings to scalar types (char, int, float, double). Shows parsing, formatting, and handling edge cases such as non-displayable characters and numeric overflow/underflow.

- `cpp_06/ex01/` — `Serializer.cpp`, `Serializer.hpp`, `main.cpp`, `Makefile`
  - Demonstrates pointer serialization: converting an object pointer to an integer type and back. Typically implemented with `reinterpret_cast` (or `uintptr_t`) to safely store a pointer value in an integer for transmission or storage.

- `cpp_06/ex02/` — `Base.cpp`, `Base.hpp`, `A.hpp`, `B.hpp`, `C.hpp`, `main.cpp`, `Makefile`
  - Shows runtime polymorphism and safe downcasting with `dynamic_cast`. The exercise creates `Base` pointers to derived objects and uses `dynamic_cast` to determine the actual derived type at runtime.

Key C++ cast types explained

- C-style cast: `(T)value` — concise but unsafe because it can perform several cast kinds (const, static, reinterpret) without making the intent explicit. Prefer C++ casts where possible.

- `static_cast<T>(value)` — compile-time cast for well-defined conversions (numeric conversions, related pointer upcasts). Does not perform runtime checks for dangerous downcasts.

- `dynamic_cast<T>(ptr_or_ref)` — runtime-checked cast for polymorphic types. Use for safe downcasting. Returns `nullptr` for failed pointer casts or throws `std::bad_cast` for reference casts.

- `reinterpret_cast<T>(value)` — low-level cast that reinterprets the underlying bit pattern (useful for pointer/integer conversions). Use it rarely and with caution.

- `const_cast<T>(value)` — adds or removes `const`/`volatile`. Only safe if the original object wasn't declared `const`.

Notes and how to run the exercises

- Build: each exercise directory contains a `Makefile`. From the workspace root you can run, for example:

  cd cpp_06/ex00 && make

- Run: after building, run the produced binary from the exercise folder. Typical examples:

  ./ScalarConverter "0"
  ./Serializer
  ./a.out   # for ex02, binary name may vary

Edge cases to watch for

- Converting numbers to `char` may produce non-displayable characters.
- Numeric overflows and precision loss when converting between types.
- `dynamic_cast` returning `nullptr` when the object is not of the requested derived type.
- Misuse of `reinterpret_cast` causing undefined behavior due to aliasing or invalid pointer conversions.

If you want, I can:

- Add example input/output for each exercise to this README.
- Build and run each exercise to capture sample outputs and include them here.
- Add inline comments to the sources explaining where each cast is used and why.


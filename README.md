# 42 School — C++ Modules 05 to 09

A comprehensive implementation of the advanced **C++ Modules (05 to 09)** of the 42 Cursus, focused on Object-Oriented Programming, Exception Handling, Type Casting, Generic Programming (Templates), Container Design, and the Standard Template Library (STL).

All code is strictly compliant with the **C++98 standard**, compiled with `-Wall -Wextra -Werror -std=c++98`, and follows the **Orthodox Canonical Class Form**.

---

## 📚 Curriculum Breakdown

| Module | Core Concepts | Exercises |
|---|---|---|
| [**cpp_05**](cpp_05) | **Repetition & Exceptions**<br>Standard exception classes, try/catch mechanisms, bureaucratic hierarchy, abstract base classes, and factory pattern with member function pointers. | • [ex00](cpp_05/ex00): `Bureaucrat`<br>• [ex01](cpp_05/ex01): `Form` signing<br>• [ex02](cpp_05/ex02): `AForm` & concrete forms<br>• [ex03](cpp_05/ex03): `Intern` factory |
| [**cpp_06**](cpp_06) | **C++ Explicit Type Casts**<br>`static_cast`, `dynamic_cast`, `reinterpret_cast`, and `const_cast`. RTTI, scalar parsing, type detection, and pointer serialization. | • [ex00](cpp_06/ex00): `ScalarConverter`<br>• [ex01](cpp_06/ex01): `Serializer` (`uintptr_t`)<br>• [ex02](cpp_06/ex02): `Base` & type identification |
| [**cpp_07**](cpp_07) | **C++ Templates & Generic Programming**<br>Function templates, type deduction, default template arguments, and generic class templates. | • [ex00](cpp_07/ex00): `swap`, `min`, `max`<br>• [ex01](cpp_07/ex01): `iter` function template<br>• [ex02](cpp_07/ex02): `Array<T>` class template |
| [**cpp_08**](cpp_08) | **Templated Containers & Iterators**<br>STL container wrappers, iterator navigation, range operations, algorithm integration, and container adapters. | • [ex00](cpp_08/ex00): `easyfind`<br>• [ex01](cpp_08/ex01): `Span` range calculator<br>• [ex02](cpp_08/ex02): `MutantStack` (iterable stack) |
| [**cpp_09**](cpp_09) | **Standard Template Library (STL)**<br>Real-world algorithmic problem solving with STL containers (`std::map`, `std::stack`, `std::vector`, `std::deque`), time complexity, and Ford-Johnson algorithm. | • [ex00](cpp_09/ex00): `BitcoinExchange` (CSV lookup)<br>• [ex01](cpp_09/ex01): `RPN` (Reverse Polish Notation)<br>• [ex02](cpp_09/ex02): `PmergeMe` (Ford-Johnson sort) |

---

## 🗂️ Project Structure

```
cpp_05_09/
├── .gitignore              # Ignores build artifacts (*.o, executables, .DS_Store)
├── README.md               # Master curriculum overview and index
│
├── cpp_05/                 # Module 05: Exceptions & Bureaucracy
│   ├── en.subject.pdf      # Official 42 subject
│   ├── README.md           # Module 05 guide & documentation
│   ├── ex00/               # Bureaucrat
│   ├── ex01/               # Form
│   ├── ex02/               # AForm, Shrubbery, Robotomy, Presidential
│   └── ex03/               # Intern factory
│
├── cpp_06/                 # Module 06: C++ Casts
│   ├── en.subject.pdf      # Official 42 subject
│   ├── README.md           # Deep-dive C++ casting guide
│   ├── notes/              # Educational scripts, visual summaries & demos
│   ├── ex00/               # ScalarConverter
│   ├── ex01/               # Serializer
│   └── ex02/               # Base & dynamic identification
│
├── cpp_07/                 # Module 07: Templates
│   ├── en.subject.pdf      # Official 42 subject
│   ├── README.md           # Comprehensive templates guide
│   ├── notes/              # Obsidian reference notes
│   ├── ex00/               # whatever (swap, min, max)
│   ├── ex01/               # iter
│   └── ex02/               # Array<T>
│
├── cpp_08/                 # Module 08: Templated Containers
│   ├── en.subject.pdf      # Official 42 subject
│   ├── README.md           # Module 08 container & iterator guide
│   ├── ex00/               # easyfind
│   ├── ex01/               # Span
│   └── ex02/               # MutantStack
│
└── cpp_09/                 # Module 09: STL Containers & Algorithms
    ├── en.subject.pdf      # Official 42 subject
    ├── README.md           # Module 09 documentation
    ├── notes/              # Technical analysis, diagrams, and usage guides
    ├── ex00/               # BitcoinExchange (btc)
    ├── ex01/               # Reverse Polish Notation (RPN)
    └── ex02/               # Merge-insert sort (PmergeMe)
```

---

## 🛠️ Compilation & Standards

Each exercise is self-contained with its own `Makefile` supporting:
- `all`: Compiles the binary
- `clean`: Removes object files (`*.o`)
- `fclean`: Removes object files and the compiled executable
- `re`: Recompiles from scratch (`fclean` followed by `all`)

### Compilation Flags
```makefile
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
```

### Quick Verification
To build and verify any exercise:
```bash
# Example: Testing cpp_09 ex00 (BitcoinExchange)
cd cpp_09/ex00
make
./btc input.txt
make fclean
```

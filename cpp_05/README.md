# CPP Module 05 — Repetition and Exceptions

This module introduces **exception handling** in C++ and demonstrates object-oriented design using a bureaucratic hierarchy.

---

## Exercises Overview

### [ex00 — Mommy, when I grow up, I want to be a bureaucrat!](ex00)
- **Concept**: Introduction to custom exception classes derived from `std::exception`.
- **Key Class**: `Bureaucrat`
  - Name (constant string), Grade (integer from 1 [highest] to 150 [lowest]).
  - Custom exceptions: `GradeTooHighException`, `GradeTooLowException`.
  - Methods to increment and decrement grade with bounds validation.

### [ex01 — Form up, maggots!](ex01)
- **Concept**: Interactions between classes through member functions and exceptions.
- **Key Class**: `Form`
  - Name, boolean sign status, sign grade, execution grade.
  - Method `beSigned(Bureaucrat &)`: verifies bureaucrat grade and signs form or throws `GradeTooLowException`.
  - Bureaucrat method `signForm(Form &)`.

### [ex02 — No, need for form 28B, not 28C...](ex02)
- **Concept**: Abstract base classes and concrete derived form implementations.
- **Key Class**: `AForm` (Abstract Form)
  - Pure virtual method `execute(Bureaucrat const & executor) const = 0`.
- **Derived Forms**:
  - `ShrubberyCreationForm` (sign 145, exec 137): creates ASCII tree file `<target>_shrubbery`.
  - `RobotomyRequestForm` (sign 72, exec 45): 50% success rate robotomizing target.
  - `PresidentialPardonForm` (sign 25, exec 5): target pardoned by Zaphod Beeblebrox.

### [ex03 — At least this beats coffee-making](ex03)
- **Concept**: Factory pattern using member function pointers.
- **Key Class**: `Intern`
  - Function `makeForm(std::string formName, std::string target)`: dynamically instantiates matching form without using redundant `if/else` chains.

---

## Compilation

All exercises are compiled using:
```bash
c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o <binary_name>
```

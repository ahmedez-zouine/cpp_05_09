#pragma once

#include <string>
#include <iostream>


class AForm;
class Bureaucrat
{
    const std::string name;
    int grade;

public:
    Bureaucrat();
    Bureaucrat(std::string _name, int _grade);
    Bureaucrat(const Bureaucrat &obj);
    Bureaucrat &operator=(const Bureaucrat &obj);
    ~Bureaucrat();

    std::string getName() const;
    int getGrade() const;
    void incrementGrade();
    void decrementGrade();
    void signForm(AForm &form);

    void executeForm(AForm const &form);

    class GradeTooHighException : public std::exception
    {
        public :
            const char *what() const throw();

    };
    class GradeTooLowException : public std::exception
    {
        public:
            const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &cout, const Bureaucrat &obj);
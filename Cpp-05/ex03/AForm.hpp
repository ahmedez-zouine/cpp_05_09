#pragma once

#include <string>
#include <iostream>


class Bureaucrat;

class AForm
{
    const std::string name;
    bool isSigned;
    const int signGrade;
    const int signExecute;

public:
    AForm();
    AForm(std::string _name, int _sign_grade, int _sign_execute);
    AForm(const AForm &obj);
    AForm &operator=(const AForm &obj);
    virtual ~AForm();

    std::string getName() const;
    bool isFormSigned() const;
    int getSignGrade() const;
    int getSignExecute() const;
    void beSigned(Bureaucrat &obj);
    virtual void execute(Bureaucrat const &executor) const = 0;
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
    class FormNotSignedException : public std::exception
    {
        public:
            const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &cout, const AForm &obj);

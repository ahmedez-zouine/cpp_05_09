#pragma once

#include <iostream>
#include <string>

class Bureaucrat;

class Form
{
    const std::string name;
    bool isSigned;
    const int signGrade;
    const int signExecute;

public:
    Form();
    Form(std::string _name, int _sign_grade, int _sign_execute);
    Form(const Form &obj);
    Form &operator=(const Form &obj);
    ~Form();

    std::string getName() const;
    bool isFormSigned() const;
    int getSignGrade() const;
    int getSignExecute() const;
    void beSigned(Bureaucrat &obj);
};

std::ostream &operator<<(std::ostream &cout, const Form &obj);

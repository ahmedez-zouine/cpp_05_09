#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("default"), grade(150) {};
Bureaucrat::Bureaucrat(const Bureaucrat &obj) : name(obj.name)
{
    this->grade = obj.grade;
}

Bureaucrat::Bureaucrat(std::string _name, int _grade) : name(_name)
{
    if (_grade < 1)
        throw Bureaucrat::GradeTooHighException();
    else if (_grade > 150)
        throw Bureaucrat::GradeTooLowException();
    else
        grade = _grade;
};


Bureaucrat &Bureaucrat::operator=(const Bureaucrat &obj)
{
    if (this != &obj)
        grade = obj.grade;
    return *this;
}


void Bureaucrat::incrementGrade() {
    if (grade - 1 < 1)
        throw GradeTooHighException();
    grade--;
}

void Bureaucrat::decrementGrade() {
    if (grade + 1 > 150)
        throw GradeTooLowException();
    grade++;
}

std::string Bureaucrat::getName() const
{
    return name;
}

int Bureaucrat::getGrade() const
{
    return grade;
}

std::ostream &operator<<(std::ostream &cout, const Bureaucrat &obj)
{
    cout << obj.getName() << ", bureaucrat grade " << obj.getGrade() << " .";
    return cout;
}

Bureaucrat::~Bureaucrat()
{
    std::cout << "Bureaucrat destroyed" << std::endl;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Grade too high";
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Grade too low";
}
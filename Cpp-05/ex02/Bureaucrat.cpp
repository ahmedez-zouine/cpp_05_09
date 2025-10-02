#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat() : name("default"), grade(150) {
                           };
Bureaucrat::Bureaucrat(std::string _name, int _grade) : name(_name)
{
    if (_grade < 1)
        throw GradeTooHighException();
    else if (_grade > 150)
        throw GradeTooLowException();
    else
        grade = _grade;
};
Bureaucrat::Bureaucrat(const Bureaucrat &obj) : name(obj.name), grade(obj.grade)
{
}
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &obj)
{
    grade = obj.grade;
    return *this;
}
Bureaucrat::~Bureaucrat()
{
}

std::string Bureaucrat::getName() const
{
    return name;
}
int Bureaucrat::getGrade() const
{
    return grade;
}
void Bureaucrat::incrementGrade()
{
    if (grade - 1 < 1)
        throw GradeTooHighException();
    else
        grade--;
}
void Bureaucrat::decrementGrade()
{
    if (grade + 1 > 150)
        throw GradeTooLowException();
    else
        grade++;
}
void Bureaucrat::signForm(AForm &AForm)
{
    try
    {
        AForm.beSigned(*this);
    std::cout << this->name << " signed " << AForm.getName() << std::endl;
    }
    catch (std::exception &e)
    {
    std::cout << this->name << " couldn't sign " << AForm.getName() << " because " << e.what() << std::endl;
    }
}
void Bureaucrat::executeForm(AForm const &form)
{
    try
    {
        form.execute(*this);
    std::cout << getName() << " executed " << form.getName() << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << " the form is not executed because " << e.what() << std::endl;
    }
}
std::ostream &operator<<(std::ostream &cout, const Bureaucrat &obj)
{
    cout << obj.getName() << ", bureaucrat grade " << obj.getGrade() << ".";
    return cout;
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Grade too high";
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Grade too low";
}

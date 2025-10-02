#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : name("default"), isSigned(false), signGrade(100), signExecute(10) {
               };

Form::Form(std::string _name, int _sign_grade, int _sign_execute)
    : name(_name), isSigned(false), signGrade(_sign_grade), signExecute(_sign_execute)
{
    if (_sign_grade < 1 || _sign_execute < 1)
        throw Bureaucrat::GradeTooHighException();
    else if (_sign_grade > 150 || _sign_execute > 150)
        throw Bureaucrat::GradeTooLowException();
}

Form::Form(const Form &obj)
    : name(obj.name), isSigned(obj.isSigned), signGrade(obj.signGrade), signExecute(obj.signExecute)
{
}

Form &Form::operator=(const Form &obj)
{
    isSigned = obj.isSigned;
    return *this;
}
Form::~Form() {

};

std::string Form::getName() const
{
    return name;
}
bool Form::isFormSigned() const
{
    return isSigned;
}
int Form::getSignGrade() const
{
    return signGrade;
}
int Form::getSignExecute() const
{
    return signExecute;
}
void Form::beSigned(Bureaucrat &obj)
{
    if (obj.getGrade() <= signGrade)
        isSigned = true;
    else
        throw Bureaucrat::GradeTooLowException();
}
std::ostream &operator<<(std::ostream &cout, const Form &obj)
{
    cout << "Form: " << obj.getName() << ", Signed: " << (obj.isFormSigned() ? "Yes" : "No")
         << ", Sign Grade: " << obj.getSignGrade() << ", Execute Grade: " << obj.getSignExecute();
    return cout;
}
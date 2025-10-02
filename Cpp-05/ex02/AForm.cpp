#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : name("default"), isSigned(false), signGrade(100), signExecute(10) {
                 };

AForm::AForm(std::string _name, int _sign_grade, int _sign_execute)
    : name(_name), isSigned(false), signGrade(_sign_grade), signExecute(_sign_execute)
{
    if (_sign_grade < 1 || _sign_execute < 1)
        throw GradeTooHighException();
    else if (_sign_grade > 150 || _sign_execute > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm &obj)
    : name(obj.name), isSigned(obj.isSigned), signGrade(obj.signGrade), signExecute(obj.signExecute)
{
}

AForm &AForm::operator=(const AForm &obj)
{
    isSigned = obj.isSigned;
    return *this;
}
AForm::~AForm() {

};

std::string AForm::getName() const
{
    return name;
}
bool AForm::isFormSigned() const
{
    return isSigned;
}
int AForm::getSignGrade() const
{
    return signGrade;
}
int AForm::getSignExecute() const
{
    return signExecute;
}
void AForm::beSigned(Bureaucrat &obj)
{
    if (obj.getGrade() <= signGrade)
        isSigned = true;
    else
        throw GradeTooLowException();
}
std::ostream &operator<<(std::ostream &cout, const AForm &obj)
{
    cout << "AForm: " << obj.getName() << ", Signed: " << (obj.isFormSigned() ? "Yes" : "No")
         << ", Sign Grade: " << obj.getSignGrade() << ", Execute Grade: " << obj.getSignExecute();
    return cout;
}

const char *AForm::GradeTooHighException::what() const throw()
{
    return "Grade too high.";
}

const char *AForm::GradeTooLowException::what() const throw()
{
    return "Grade too low.";
}

const char *AForm::FormNotSignedException::what() const throw()
{
    return "Form not signed.";
}
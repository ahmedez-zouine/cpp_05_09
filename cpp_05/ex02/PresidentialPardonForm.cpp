#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("Presidential pardon", 25, 5)
{
    target = "default";
}
PresidentialPardonForm::PresidentialPardonForm(std::string _target) : AForm("Presidential pardon", 25, 5)
{
    target = _target;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &obj) : AForm(obj)
{
    target = obj.target;
}
PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &obj)
{
    AForm::operator=(obj);
    target = obj.target;
    return *this;
}
PresidentialPardonForm::~PresidentialPardonForm()
{
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
    if (!isFormSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getSignExecute())
        throw GradeTooLowException();

    std::cout << target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

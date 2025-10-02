#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>
#include <ctime>
RobotomyRequestForm::RobotomyRequestForm() : AForm("robotomy request", 72, 45)
{
    target = "default";
}
RobotomyRequestForm::RobotomyRequestForm(std::string _target) : AForm("robotomy request", 72, 45)
{
    target = _target;
}
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &obj) : AForm(obj)
{
    target = obj.target;
}
RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &obj)
{
    AForm::operator=(obj);
    target = obj.target;
    return *this;
}
RobotomyRequestForm::~RobotomyRequestForm() {

};

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
    if (!isFormSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getSignExecute())
        throw GradeTooLowException();

    srand(time(0));
    int randnum = rand() % 2;

    std::cout << " DRILLING NOISES  " << std::endl;
    if (randnum == 1)
        std::cout << target << " has been robotomized successfully!" << std::endl;
    else
        std::cout << "Robotomy failed for " << target << "." << std::endl;
}

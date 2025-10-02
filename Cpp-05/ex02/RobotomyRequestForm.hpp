#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <string>

class RobotomyRequestForm : public AForm
{
    std::string target;

public:
    RobotomyRequestForm();
    RobotomyRequestForm(std::string _target);
    RobotomyRequestForm(const RobotomyRequestForm &obj);
    RobotomyRequestForm &operator=(const RobotomyRequestForm &obj);
    ~RobotomyRequestForm();

    void execute(Bureaucrat const &executor) const;
};

#endif

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"
#include <string>

class PresidentialPardonForm : public AForm
{
    std::string target;

public:
    PresidentialPardonForm();
    PresidentialPardonForm(std::string _target);
    PresidentialPardonForm(const PresidentialPardonForm &obj);
    PresidentialPardonForm &operator=(const PresidentialPardonForm &obj);
    ~PresidentialPardonForm();
    void execute(Bureaucrat const &executor) const;
};

#endif
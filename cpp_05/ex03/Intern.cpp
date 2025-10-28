#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

Intern::Intern() {}
Intern::~Intern() {}
Intern::Intern(const Intern &obj) { (void)obj; }
Intern &Intern::operator=(const Intern &obj)
{
    (void)obj;
    return *this;
}

AForm *Intern::ShrubberyForm(const std::string &target)
{
    return new ShrubberyCreationForm(target);
}

AForm *Intern::RobotomyForm(const std::string &target)
{
    return new RobotomyRequestForm(target);
}

AForm *Intern::PresidentialForm(const std::string &target)
{
    return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(std::string form_name, std::string target)
{
    std::string form_names[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };
    
    AForm* (Intern::*form_functions[3])(const std::string&) = {
        &Intern::ShrubberyForm,
        &Intern::RobotomyForm,
        &Intern::PresidentialForm
    };
    
    int i = 0;
    while( i < 3)
    {
        if (form_name == form_names[i])
        {
            AForm* form = (this->*form_functions[i])(target);
            std::cout << "Intern creates " << form->getName() << std::endl;
            return form;
        }
        i++;
    }
    
    std::cout << "The form name passed doesn't exist" << std::endl;
    return NULL;
}
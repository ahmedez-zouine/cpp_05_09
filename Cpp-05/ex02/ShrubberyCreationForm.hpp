#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <string>

class ShrubberyCreationForm : public AForm
{
    std::string target;

public:
    ShrubberyCreationForm();
    ShrubberyCreationForm(std::string _target);
    ShrubberyCreationForm(const ShrubberyCreationForm &obj);
    ShrubberyCreationForm &operator=(const ShrubberyCreationForm &obj);
    ~ShrubberyCreationForm();
    void execute(Bureaucrat const &executor) const;
};

#endif
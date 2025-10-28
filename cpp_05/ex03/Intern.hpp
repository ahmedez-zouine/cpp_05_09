#pragma once 

#include "AForm.hpp"

 
class Intern {
public:
    Intern();
    Intern(const Intern &obj);
    Intern &operator=(const Intern &obj);
    ~Intern();
    
    AForm *makeForm(std::string form_name, std::string target);
    
    AForm* ShrubberyForm(const std::string& target) ;
    AForm* RobotomyForm(const std::string& target) ;
    AForm* PresidentialForm(const std::string& target) ;
};
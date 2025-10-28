#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"


int main()
{
    try {
       
        ShrubberyCreationForm shrub("garden");
        RobotomyRequestForm robot("Bender");
        PresidentialPardonForm pardon("prisoner");
        
        
        Bureaucrat intern("Intern", 140);        
        Bureaucrat officer("Officer", 50);       
        Bureaucrat boss("Boss", 5);   
        
        std::cout << "\n--- SHRUBBERY TESTS ---\n";
        intern.signForm(shrub);
        intern.executeForm(shrub);  
        officer.executeForm(shrub); 
        

        std::cout << "\n--- ROBOTOMY TESTS ---\n";
        intern.signForm(robot);   
        officer.signForm(robot);
        officer.executeForm(robot); 
        
        std::cout << "\n--- PRESIDENTIAL TESTS ---\n";
        boss.signForm(pardon);
        boss.executeForm(pardon);
    }
    catch (std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
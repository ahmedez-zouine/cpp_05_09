#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    std::cout << "--- Testing Form Creation ---" << std::endl;
    try
    {
        Form validForm("Tax Form", 50, 25);
        std::cout << validForm << std::endl;


        try
        {
            Form invalidForm("Invalid Form", 0, 25);
        }
        catch (std::exception &e)
        {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }

        try
        {
            Form invalidForm("Invalid Form", 50, 151);
        }
        catch (std::exception &e)
        {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- Testing Form Signing ---" << std::endl;
    try
    {
      
        Form form("Important Contract", 50, 25);

 
        Bureaucrat highGrade("Director", 20); 
        Bureaucrat lowGrade("Intern", 100);   

        std::cout << highGrade << std::endl;
        std::cout << lowGrade << std::endl;
        std::cout << form << std::endl;

    
        highGrade.signForm(form);
        std::cout << form << std::endl;

        Form anotherForm("Another Contract", 50, 25);

        lowGrade.signForm(anotherForm);
        std::cout << anotherForm << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    return 0;
}
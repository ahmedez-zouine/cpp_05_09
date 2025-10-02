
#include"Bureaucrat.hpp"
 

int main()
{
    Bureaucrat *a = nullptr;
    try
    {
        a = new Bureaucrat("jj", 32);
        std::cout << *a << std::endl; 
        
        Bureaucrat b("jj", 150); 
        std::cout << b << std::endl;
        
        delete a; 
        a = nullptr;
    }
    catch(const Bureaucrat::GradeTooHighException &e)
    {
        if (a != nullptr) {
            delete a;
            a = nullptr;
        }
        std::cout << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "i don't know the error here" << std::endl;
    }
    
    return 0;
}
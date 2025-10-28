#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("shrubbery creation", 145, 137)
{
    target = "default";
}
ShrubberyCreationForm::ShrubberyCreationForm(std::string _target) : AForm("shrubbery creation", 145, 137)
{
    target = _target;
}
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &obj) : AForm(obj)
{
    target = obj.target;
}
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &obj)
{
    AForm::operator=(obj);
    target = obj.target;
    return *this;
}
ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
    if (!isFormSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getSignExecute())
        throw GradeTooLowException();
    std::string file_name = target + "_shrubbery";
    std::ofstream myfile(file_name.c_str());
    if (!myfile)
        throw std::runtime_error("Could not create output file");
    myfile << "    ###    " << std::endl;
    myfile << "   #####   " << std::endl;
    myfile << "  #######  " << std::endl;
    myfile << " ######### " << std::endl;
    myfile << "###########" << std::endl;
    myfile << "    |||    " << std::endl;
    myfile << "    |||    " << std::endl;
    myfile << "============" << std::endl;
    myfile.close();
}
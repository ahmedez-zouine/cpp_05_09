#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::~Base()
{
    std::cout << "Base destructor called" << std::endl;
}
Base *generate(void)
{
    srand(time(NULL));
    int random = std::rand() % 3;
 std::cout<<random <<std::endl;
    if (random == 0)
        return new A();
    else if (random == 1)
        return new B();
    else
        return new C();
}

void identify(Base *p)
{
    if (dynamic_cast<A *>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B *>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C *>(p))
        std::cout << "C" << std::endl;
    else 
    std::cout << "Unknown type" << std::endl;
}
void identify(Base &p)
{
    try
    {
        dynamic_cast<A &>(p);
        std::cout << "A" << std::endl;
        return;
    }
    catch (...)
    {
    }
    try
    {
        dynamic_cast<B &>(p);
        std::cout << "B" << std::endl;
        return;
    }
    catch (...)
    {
    }
    try
    {
        dynamic_cast<C &>(p);
        std::cout << "C" << std::endl;
        return;
    }
    catch (...)
    {
    }
    std::cout << "Unknown type" << std::endl;
}
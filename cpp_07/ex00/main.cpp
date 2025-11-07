#include "whatever.hpp"
#include <iostream>
<<<<<<< HEAD

int main()
{
    int a = 42;
    int b = 21;

    ::swap(a, b);
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
    std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

    std::string c = "chaine1";
    std::string d = "chaine2";

    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
    std::cout << "max(c, d) = " << ::max(c, d) << std::endl;

    std::cout << "\nTesting equal function:" << std::endl;
    int x = 10;
    int y = 10;
    std::cout << "Are x and y equal? " << (::equal(x, y) ? "Yes" : "No") << std::endl;

    return 0;
=======
int main( void ) {
int a = 2;
int b = 3;
::swap<int>( a, b );
std::cout << "a = " << a << ", b = " << b << std::endl;
std::cout << "min( a, b ) = " << ::min<int>( a, b ) << std::endl;
std::cout << "max( a, b ) = " << ::max<int>( a, b ) << std::endl;
std::string c = "chaine1";
std::string d = "chaine2";
::swap(c, d);
std::cout << "c = " << c << ", d = " << d << std::endl;
std::cout << "min( c, d ) = " << ::min<std::string>( c, d ) << std::endl;
std::cout << "max( c, d ) = " << ::max<std::string>( c, d ) << std::endl;
return 0;
>>>>>>> 1f99390516a3159bcdd63437145e8ef7708ac85f
}
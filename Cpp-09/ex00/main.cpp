
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "ERROR: wrong number of args\n";
        return 1;
    }

    BitcoinExchange BitcoinExchange;

    BitcoinExchange.upload_csv_file();

    BitcoinExchange.procces_input(av[1]);

    return 0;
}
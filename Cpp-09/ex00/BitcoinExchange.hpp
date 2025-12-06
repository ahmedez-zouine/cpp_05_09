#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>

class BitcoinExchange
{
    std::map<std::string, double> prices;

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    int upload_csv_file();
    int procces_input(const std::string &input);

    int validate_year(std::string year);
    int validate_month(std::string month);
    int validate_day(std::string year,std::string month,std::string day);
    double validate_value(std::string value_part);
    double get_money(std::string date_part);
};
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    prices = other.prices;
};
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        prices = other.prices;
    return *this;
}
BitcoinExchange::~BitcoinExchange()
{
}

int BitcoinExchange::upload_csv_file()
{
    std::fstream csv_file("data.csv");

    if (!csv_file.is_open())
    {
        std::cout << " Cant open the csv file \n";
        return 1;
    }
    std::string line;
    getline(csv_file, line);
    while (std::getline(csv_file, line))
    {
        std::stringstream line_stream(line);
        std::string date;
        double value;

        getline(line_stream, date, ',');
        line_stream >> value;
        prices[date] = value;
    }

    return 0;
}

int BitcoinExchange::procces_input(const std::string &input)
{
    std::ifstream input_file(input.c_str());

    if (!input_file.is_open())
    {
        std::cout << " failed to open input file \n";
        return 1;
    }

    std::string line;
    getline(input_file, line);

    if (line != "date | value")
    {
        std::cout << "Error: invalid header format\n";
        return 1;
    }

    while (getline(input_file, line))
    {
        std::stringstream ss(line);
        std::string date_part;
        std::string value_part;

        if (!getline(ss, date_part, '|'))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (!getline(ss, value_part))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::stringstream date_ss(date_part);
        std::string year, month, day;

        if (!getline(date_ss, year, '-') ||
            !getline(date_ss, month, '-') ||
            !getline(date_ss, day))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (!validate_year(year) ||!validate_month(month) || !validate_day(year, month, day))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        double value = validate_value(value_part);
        if (value == -1)
            continue;
        
        if(day.length() == 2 && day[1] == ' ')
            day = day.substr(0, 1);
        if(day.length() == 1)
            day = "0" + day;
        if(month.length() == 1)
            month = "0" + month;
        
        std::string normalized_date = year + "-" + month + "-" + day;
        double price = get_money(normalized_date);
        if(price == -1)
            continue;
        std::cout << normalized_date << " => " << value * price << std::endl;
    }

    return 0;
}
int BitcoinExchange::validate_year(std::string year)
{

    for (size_t i = 0; i < year.length(); i++)
    {
        if (!isdigit(year[i]))

            return 0;
    }

    int year_int = atoi(year.c_str());

    if (year_int < 2009 || year_int > 2025)
    {
        return 0;
    }

    return 1;
}
int BitcoinExchange::validate_month(std::string month)
{
    for (size_t i = 0; i < month.length(); i++)
    {
        if (!isdigit(month[i]))
            return 0;
    }
    int month_int = atoi(month.c_str());
    if (month_int < 1 || month_int > 12)
    {
        return 0;
    }

    return 1;
}
int BitcoinExchange::validate_day(std::string year, std::string month, std::string day)
{

    int year_int = atoi(year.c_str());
    int month_int = atoi(month.c_str());
    if (day[day.length() - 1] != ' ')
        return 0;
    for (size_t i = 0; i < day.length() - 1; i++)
    {
        if (!isdigit(day[i]))
            return 0;
    }
    int day_int = atoi(day.c_str());
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year_int == 2012 || year_int == 2016 || year_int == 2020 || year_int == 2024) && month_int == 2)
    {
        days_in_month[1] = 29;
    }
    if (day_int > days_in_month[month_int - 1] || day_int < 1)
        return 0;
    return 1;
}
double BitcoinExchange::validate_value(std::string value_part)
{
    if (value_part[0] != ' ')
    {
        std::cout << "Error: should be space after | .\n";
        return -1;
    }

    char *end;
    double value = strtod(value_part.c_str(), &end);
    if (*end != '\0')
    {
        std::cout << "Error: bad value .\n";
        return -1;
    }
    if (value < 0)
    {
        std::cout << "Error: not a positive number.\n";
        return -1;
    }
    if (value > 1000) 
    {
        std::cout << "Error: too large a number.\n";
        return -1;
    }
    return value;
}

double BitcoinExchange::get_money(std::string date_part)
{
    std::map<std::string,double>::iterator it=prices.lower_bound(date_part);
    if(it!=prices.end() && it->first == date_part)
        return it->second;
    if(it==prices.begin())
    {
        std::cout << "Error: date should be after 2009-01-02 => " << date_part << std::endl;
        return -1;
    }

    --it;
    return it->second;
}
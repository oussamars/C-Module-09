#include "BitcoinExchange.hpp"//check if you write all the errors in the stdandard error and not std output

bitcoinExchange::bitcoinExchange()
{

}
bitcoinExchange::~bitcoinExchange()
{

}

static std::string trim(const std::string &s)
{
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

void bitcoinExchange::loadData(const std::string& filename)
{
    std::ifstream file;
    file.open(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    
    while (std::getline(file, line))
    {
        std::size_t comapos = line.find(',');
        if (comapos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string key = line.substr(0, comapos);
        std::string stringValue = line.substr(comapos + 1);
        key = trim(key);
        stringValue = trim(stringValue);

        //we want to convert the string value from a string to a double
        std::stringstream ss(stringValue); //stringstream is a fake input stream that reads from a string instead of a file or keyboard
        double value;
        if (!(ss >> value))//reads the numiric part only
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        char c;
        if (ss >> c)//Is there still something left that I can read? => If yes, that means the input was not a clean number
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        data[key] = value;
         
    }
}

void bitcoinExchange::processInput(const std::string& filename)
{
    std::ifstream input_file(filename.c_str());
    if (!input_file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(input_file, line);

    while (getline(input_file, line))
    {
        if (line.empty())
            continue;

        size_t seperatorpos = line.find('|');
        if (seperatorpos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string key = line.substr(0, seperatorpos);
        std::string stringValue = line.substr(seperatorpos + 1);
        key = trim(key);
        stringValue = trim(stringValue);

        std::stringstream ss(stringValue);
        double value;
        if (!(ss >> value))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        char c;
        if (ss >> c)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }
        if (!validate_date_format(key))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        if (data.empty())//mloadinach data donc m3ndnach bach ncompariw
        {
            std::cerr << "Error: no data available" << std::endl;
            return;
        }
        //Since std::map is ordered by keys, lower_bound(key) finds the first position where this key could be inserted without breaking the order.
        std::map<std::string, double>::const_iterator it = data.lower_bound(key);//why did we use a const iterator
        if (it == data.begin() && it->first != key)
        {
            std::cerr << "Error: no data available" << std::endl;
            continue;
        }
        if (it == data.end() || it->first != key)//input after all database dates
        {
            --it;
        }
        double result = value * it->second;
        std::cout << key << " => " << value << " = " << result << std::endl;
    }
}

bool bitcoinExchange::validate_date_format(const std::string& date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.length(); i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }
    int month = std::atoi(date.substr(5, 2).c_str());
    if (month < 1 || month > 12)
        return false;
    int day = std::atoi(date.substr(8, 2).c_str());
    if (day < 1 || day > 31)
        return false;

    return true;
}

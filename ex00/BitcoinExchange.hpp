#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>  
#include <sstream>
#include <map>
#include <cstdlib>


class bitcoinExchange
{
    private:
        std::map<std::string, double> data;

    public:
        bitcoinExchange();
        ~bitcoinExchange();
        void loadData(const std::string& filename);
        void processInput(const std::string& filename);
        bool validate_date_format(const std::string& date);
};


#endif
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    bitcoinExchange btc;
    btc.loadData("data.csv");

    if (ac != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    btc.processInput(av[1]);
    return 0;
}

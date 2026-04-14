#include "RPN.hpp"

int main(int ac, char **av) //check if you write all the errors in the stdandard error and not std output
{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " <RPN expression>" << std::endl;
        return 1;
    }

    RPN rpn;

    try
    {
        rpn.process(av[1]);
    }

    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
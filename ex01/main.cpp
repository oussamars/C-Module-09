#include "RPN.hpp"

int main(int ac, char **av)// reread the subject to confirm that the error should be in the standard error or standard output, i think it should be in the standard error but the subject is not clear about that, so i will put it in the standard output for now
{
    if (ac != 2)
    {
        std::cout << "Usage: " << av[0] << " <RPN expression>" << std::endl;
        return 1;
    }
    RPN rpn;
    try
    {
        rpn.process(av[1]);
    }

    catch (const RPNException &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
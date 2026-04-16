#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    PmergeMe pmerge;

    if (!pmerge.parseInput(ac, av))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < pmerge.getVector().size(); i++)
        std::cout << pmerge.getVector()[i] << " ";
    std::cout << std::endl;

    clock_t startVect = clock();
    pmerge.sortVector();
    clock_t endVect = clock();
    double vecUs = (double)(endVect - startVect) * 1000000.0 / CLOCKS_PER_SEC;

    clock_t startDeq = clock();
    pmerge.sortDeque();
    clock_t endDeq = clock();
    double deqUs = (double)(endDeq - startDeq) * 1000000.0 / CLOCKS_PER_SEC;

    std::cout << "After: ";
    for (size_t i = 0; i < pmerge.getVector().size(); i++)
        std::cout << pmerge.getVector()[i] << " ";
    std::cout << std::endl;

    //maybe we should check if the vector and the deque have the same output or the same sorted numbers

    std::cout << "Time to process a range of " << pmerge.getVector().size()
              << " elements with std::vector : " << vecUs << " us" << std::endl;

    std::cout << "Time to process a range of " << pmerge.getDeque().size()
              << " elements with std::deque : " << deqUs << " us" << std::endl;

    return 0;
}
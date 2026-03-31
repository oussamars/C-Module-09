#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <climits>
#include <ctime>


class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();
        std::vector<int> getVector() const { return _vector; }
        std::deque<int> getDeque() const { return _deque; }
        bool parseInput(int ac, char **av);
        void sortVector();
        void mergeInsertSortVector(std::vector<int> &values);
        void sortDeque();
        void mergeInsertSortDeque(std::deque<int> &values);
};

#endif
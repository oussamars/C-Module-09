#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vector(other._vector), _deque(other._deque)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
}

bool isValidNumber(const std::string &s)
{
    if (s.empty())
        return false;

    for (size_t i = 0; i < s.size(); i++)
        if (!std::isdigit(s[i]))
            return false;

    return true;
}

bool PmergeMe::parseInput(int ac, char **av)
{
    _vector.clear();
    _deque.clear();
    for (int i = 1; i < ac; i++)
    {
        std::stringstream line(av[i]);
        std::string word;
        while (line >> word)
        {
            if (!isValidNumber(word))
                return false;
            long value;
            std::stringstream ss(word);
            ss >> value;
            if (ss.fail() || !ss.eof())
                return false;
            if (value <= 0 || value > INT_MAX)
                return false;
            _vector.push_back(value);
            _deque.push_back(value);
        }
    }
    if (_vector.empty())
        return false;
    return true;
}

void PmergeMe::mergeInsertSortVector(std::vector<int> &values)
{

    if (values.size() <= 1)
        return;
    
    std::vector<std::pair<int, int> > pairs;
    std::vector<int > min_values;
    std::vector<int > max_values;

    bool isodd = false;
    int remainnumber = 0;

    for (size_t i = 0; i + 1 < values.size(); i += 2) //i + 1 so it wont go out of bounds and add a random number to the pairs vector
    {
        int a = values[i];
        int b = values[i + 1];
        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    if (values.size() % 2 != 0)
    {
        isodd = true;
        remainnumber = values.back();
    }
    
    for (size_t i = 0; i < pairs.size(); i++)
    {
        min_values.push_back(pairs[i].first);
        max_values.push_back(pairs[i].second);
    }
    
    mergeInsertSortVector(max_values);

    for (size_t i = 0; i < min_values.size(); i++)
    {
        std::vector<int>::iterator it;
        it = std::lower_bound(max_values.begin(), max_values.end(), min_values[i]);
        max_values.insert(it, min_values[i]);
    }
    if (isodd)
    {
        std::vector<int>::iterator it;
        it = std::lower_bound(max_values.begin(), max_values.end(), remainnumber);
        max_values.insert(it, remainnumber);
    }

    values = max_values;

}

void PmergeMe::sortVector()
{
    mergeInsertSortVector(_vector);
}


void PmergeMe::mergeInsertSortDeque(std::deque<int> &values)
{
    if (values.size() <= 1)
        return;

    std::deque<std::pair<int, int> > pairs;
    std::deque<int > min_values;
    std::deque<int > max_values;

    bool isodd = false;
    int remainnumber = 0;

    for (size_t i = 0; i + 1 < values.size(); i += 2)
    {
        int a = values[i];
        int b = values[i + 1];
        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    if (values.size() % 2 != 0)
    {
        isodd = true;
        remainnumber = values.back();
    }

    for (size_t i = 0; i < pairs.size(); i++)
    {
        min_values.push_back(pairs[i].first);
        max_values.push_back(pairs[i].second);
    }

    mergeInsertSortDeque(max_values);

    for (size_t i = 0; i < min_values.size(); i++)
    {
        std::deque<int>::iterator it;
        it = std::lower_bound(max_values.begin(), max_values.end(), min_values[i]);
        max_values.insert(it, min_values[i]);
    }

    if (isodd)
    {
        std::deque<int>::iterator it;
        it = std::lower_bound(max_values.begin(), max_values.end(), remainnumber);
        max_values.insert(it, remainnumber);
    }

    values = max_values;

}

void PmergeMe::sortDeque()
{
    mergeInsertSortDeque(_deque);
}

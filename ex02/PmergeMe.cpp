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
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return false;

    return true;
}

bool PmergeMe::parseInput(int ac, char **av)
{
    _vector.clear();
    _deque.clear();

    std::set<int> seen;

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

            int v = static_cast<int>(value);
            if (!seen.insert(v).second) // already present
                return false;

            _vector.push_back(v);
            _deque.push_back(v);
        }
    }

    return !_vector.empty();
}

static std::vector<size_t> buildJacobOrder(size_t n)
{
    std::vector<size_t> order;
    if (n == 0)
        return order;

    std::vector<bool> used(n, false);

    order.push_back(0);
    used[0] = true;

    size_t jPrev = 1;
    size_t jCurr = 3;

    while (order.size() < n)
    {
        size_t upper = (jCurr < n) ? jCurr : n;
        for (size_t k = upper; k > jPrev; --k)
        {
            size_t idx = k - 1;
            if (!used[idx])
            {
                used[idx] = true;
                order.push_back(idx);
            }
        }
        size_t jNext = jCurr + 2 * jPrev;
        jPrev = jCurr;
        jCurr = jNext;
    }

    for (size_t i = 0; i < n; ++i)
    {
        if (!used[i])
            order.push_back(i);
    }

    return order;
}

struct VNode
{
    int value;
    int id;
    int partnerWinnerId;
    VNode() : value(0), id(-1), partnerWinnerId(-1) {}
    VNode(int v, int i) : value(v), id(i), partnerWinnerId(-1) {}
};

static size_t findWinnerPosV(const std::vector<VNode> &chain, int winnerId)
{
    for (size_t i = 0; i < chain.size(); ++i)
        if (chain[i].id == winnerId)
            return i;
    return chain.size();
}

static size_t lowerBoundV(const std::vector<VNode> &chain, size_t right, int value)
{
    size_t left = 0;
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        if (chain[mid].value < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void PmergeMe::mergeInsertSortVector(std::vector<int> &values)
{
    if (values.size() <= 1)
        return;

    std::vector<VNode> nodes;
    nodes.reserve(values.size());
    for (size_t i = 0; i < values.size(); ++i)
        nodes.push_back(VNode(values[i], static_cast<int>(i)));

    std::vector< std::pair<VNode, VNode> > pairs;
    bool hasOdd = false;
    VNode odd;

    for (size_t i = 0; i + 1 < nodes.size(); i += 2)
    {
        VNode a = nodes[i];
        VNode b = nodes[i + 1];
        if (a.value > b.value)
            std::swap(a, b);
        a.partnerWinnerId = b.id;
        pairs.push_back(std::make_pair(a, b));
    }

    if (nodes.size() % 2 != 0)
    {
        hasOdd = true;
        odd = nodes.back();
    }

    std::vector<int> winnerValues;
    winnerValues.reserve(pairs.size());
    for (size_t i = 0; i < pairs.size(); ++i)
        winnerValues.push_back(pairs[i].second.value);

    mergeInsertSortVector(winnerValues);

    // rebuild winner chain with ids in sorted winner order
    std::vector<VNode> winners;
    winners.reserve(winnerValues.size());
    std::vector<bool> usedPair(pairs.size(), false);

    for (size_t i = 0; i < winnerValues.size(); ++i)
    {
        int v = winnerValues[i];
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (!usedPair[j] && pairs[j].second.value == v)
            {
                winners.push_back(pairs[j].second);
                usedPair[j] = true;
                break;
            }
        }
    }

    // pend aligned with sorted winners
    std::vector<VNode> pend;
    pend.reserve(winners.size());
    for (size_t i = 0; i < winners.size(); ++i)
    {
        int wid = winners[i].id;
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].second.id == wid)
            {
                pend.push_back(pairs[j].first);
                break;
            }
        }
    }

    std::vector<VNode> chain = winners;
    std::vector<size_t> order = buildJacobOrder(pend.size());

    for (size_t k = 0; k < order.size(); ++k)
    {
        VNode x = pend[order[k]];
        size_t winnerPos = findWinnerPosV(chain, x.partnerWinnerId);
        size_t bound = winnerPos + 1;
        size_t insertPos = lowerBoundV(chain, bound, x.value);
        chain.insert(chain.begin() + insertPos, x);
    }

    if (hasOdd)
    {
        size_t insertPos = lowerBoundV(chain, chain.size(), odd.value);
        chain.insert(chain.begin() + insertPos, odd);
    }

    values.clear();
    values.reserve(chain.size());
    for (size_t i = 0; i < chain.size(); ++i)
        values.push_back(chain[i].value);
}

void PmergeMe::sortVector()
{
    mergeInsertSortVector(_vector);
}

struct DNode
{
    int value;
    int id;
    int partnerWinnerId;
    DNode() : value(0), id(-1), partnerWinnerId(-1) {}
    DNode(int v, int i) : value(v), id(i), partnerWinnerId(-1) {}
};

static size_t findWinnerPosD(const std::deque<DNode> &chain, int winnerId)
{
    for (size_t i = 0; i < chain.size(); ++i)
        if (chain[i].id == winnerId)
            return i;
    return chain.size();
}

static size_t lowerBoundD(const std::deque<DNode> &chain, size_t right, int value)
{
    size_t left = 0;
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        if (chain[mid].value < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &values)
{
    if (values.size() <= 1)
        return;

    std::deque<DNode> nodes;
    for (size_t i = 0; i < values.size(); ++i)
        nodes.push_back(DNode(values[i], static_cast<int>(i)));

    std::deque< std::pair<DNode, DNode> > pairs;
    bool hasOdd = false;
    DNode odd;

    for (size_t i = 0; i + 1 < nodes.size(); i += 2)
    {
        DNode a = nodes[i];
        DNode b = nodes[i + 1];
        if (a.value > b.value)
            std::swap(a, b);
        a.partnerWinnerId = b.id;
        pairs.push_back(std::make_pair(a, b));
    }

    if (nodes.size() % 2 != 0)
    {
        hasOdd = true;
        odd = nodes.back();
    }

    std::deque<int> winnerValues;
    for (size_t i = 0; i < pairs.size(); ++i)
        winnerValues.push_back(pairs[i].second.value);

    mergeInsertSortDeque(winnerValues);

    // rebuild winner chain with ids in sorted winner order
    std::deque<DNode> winners;
    std::vector<bool> usedPair(pairs.size(), false);

    for (size_t i = 0; i < winnerValues.size(); ++i)
    {
        int v = winnerValues[i];
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (!usedPair[j] && pairs[j].second.value == v)
            {
                winners.push_back(pairs[j].second);
                usedPair[j] = true;
                break;
            }
        }
    }

    // pend aligned with sorted winners
    std::deque<DNode> pend;
    for (size_t i = 0; i < winners.size(); ++i)
    {
        int wid = winners[i].id;
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].second.id == wid)
            {
                pend.push_back(pairs[j].first);
                break;
            }
        }
    }

    std::deque<DNode> chain = winners;
    std::vector<size_t> order = buildJacobOrder(pend.size());

    for (size_t k = 0; k < order.size(); ++k)
    {
        DNode x = pend[order[k]];
        size_t winnerPos = findWinnerPosD(chain, x.partnerWinnerId);
        size_t bound = winnerPos + 1;
        size_t insertPos = lowerBoundD(chain, bound, x.value);
        chain.insert(chain.begin() + insertPos, x);
    }

    if (hasOdd)
    {
        size_t insertPos = lowerBoundD(chain, chain.size(), odd.value);
        chain.insert(chain.begin() + insertPos, odd);
    }

    values.clear();
    for (size_t i = 0; i < chain.size(); ++i)
        values.push_back(chain[i].value);
}

void PmergeMe::sortDeque()
{
    mergeInsertSortDeque(_deque);
}

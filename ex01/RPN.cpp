#include "RPN.hpp"

RPN::RPN()
{
}
RPN::RPN(const RPN &other) : _stack(other._stack)
{
    
}
RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
    
}
RPN::~RPN()
{
}

void RPN::process(const std::string& input)
{
    while (!_stack.empty())
        _stack.pop();
    
    if (input.empty())
        throw std::runtime_error("Error");

    for (size_t i = 0; i < input.size(); i++)
    {
        if (input[i] == ' ')
            continue;
        else if (input[i] >= '0' && input[i] <= '9')
        {
            _stack.push(input[i] - '0');
        }
        else if (input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '*')
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error");

            int result;
            int y = _stack.top();
            _stack.pop();
            int x = _stack.top();
            _stack.pop();
            if (input[i] == '+')
                result = x + y;
            if (input[i] == '-')
                result = x - y;
            if (input[i] == '*')
                result = x * y;
            if (input[i] == '/')
            {
                if (y == 0)
                    throw std::runtime_error("Error");

                result = x / y;
            }
            _stack.push(result);
        }
        else
            throw std::runtime_error("Error");

    }

    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    std::cout << _stack.top() << std::endl;  

}
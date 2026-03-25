#include "RPN.hpp"

//why did we use stack as a container for this exercise ?
// because stack is a data structure that follows the Last In First Out (LIFO) principle
// and it is used to store the operands and the operators in the RPN expression
// and it allows us to easily access the top element of the stack which is the last operand
// and it allows us to easily push and pop elements from the stack which is necessary for the 
// evaluation of the RPN expression

//we need to handle:
    //1. Not enough numbers
    //2. Invalid token
    //3. Division by zero
    //4. Too many numbers
    //5. Empty expression

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
        throw RPNException("Error");

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
                throw RPNException("Error");

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
                    throw RPNException("Error");

                result = x / y;
            }
            _stack.push(result);
        }
        else
            throw RPNException("Error");

    }
    if (_stack.empty())
        throw RPNException("Error");

    if (_stack.size() != 1)
        throw RPNException("Error");

    std::cout << _stack.top() << std::endl;  

}
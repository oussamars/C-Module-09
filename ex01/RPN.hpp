#ifndef RPN_HPP
#define RPN_HPP


#include <iostream>
#include <stack>
#include <exception>
#include <string>

class RPN
{
    private:
        std::stack<int> _stack;
    public:
        RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);
        ~RPN();
        void process(const std::string& input);

};

#endif
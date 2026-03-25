#ifndef RPN_HPP
#define RPN_HPP


#include <iostream>
#include <stack>
#include <exception>
#include <string>


//lets create the exception class for the RPN calculator
class RPNException : public std::exception
{
    private:
        std::string message;
    public:
        RPNException(const std::string &msg) : message(msg) {}
        virtual ~RPNException() throw() {}  //why did we add this, i had an error so i had to add it why ??
        virtual const char* what() const throw() {
            return message.c_str();
        }
};

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
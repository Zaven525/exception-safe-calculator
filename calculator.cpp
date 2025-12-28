#include <iostream>
#include <stdexcept>
#include <cmath>

class MathException : public std::domain_error
{
public:
    MathException(std::string str) : std::domain_error(str) {}
};

class ZeroDivisionError : public MathException { public: ZeroDivisionError() : MathException("Cant divide number to a 0") {} };
class NegativeNumber : public MathException { public: NegativeNumber() : MathException("Negative number for sqrt") {} };
class LogError : public MathException { public: LogError() : MathException("x is less or equal to 0") {} };

class Exit : public std::exception { public: const char* what() const noexcept override { return "exit"; }};
class OperandInputError : public std::invalid_argument { public: OperandInputError(const std::string s) : std::invalid_argument(s) {} };

double my_plus(double lhs, double rhs)
{   
    return lhs + rhs;
}

double my_minus(double lhs, double rhs)
{
    return lhs - rhs;
}

double my_multiply(double lhs, double rhs)
{
    return lhs * rhs;
}

double my_division(double lhs, double rhs)
{
    if (rhs == 0) throw ZeroDivisionError(); 
    return lhs / rhs;
}

double my_pow(double x, double n)
{
    return std::pow(x, n);
}

double my_sqrt(double x)
{
    if (x < 0) throw NegativeNumber();
    return std::sqrt(x);
}

double my_log(double x)
{
    if (x <= 0) throw LogError();
    return std::log(x);
}

void calculator()
{
    std::string operation;
    double a, b;
    while (true)
    {
        
        std::cout << "Choose the operatoin:" << std::endl; std::cin >> operation;
        if ( operation == "/exit") throw Exit();
        std::cout << "Choose the 1st number: "; if(!(std::cin >> a)) throw OperandInputError("Can't have string operand"); 
    
        if ( operation == "log" ) 
        {
            double tmp = my_log(a);
            std::cout << "log(" << a << ") = " << tmp << std::endl;
            continue; 
        }
        else if (operation == "sqrt")
        {
            double tmp = my_sqrt(a);
            std::cout << "sqrt(" << a << ") = " << tmp << std::endl;
            continue; 
        }

        std::cout << "Choose the 2nd number: "; if(!(std::cin >> b)) throw OperandInputError("Can't have string operand"); 
        if (operation == "+") 
        {
            std::cout << a << " + " << b << " = " << my_plus(a, b) << std::endl; continue;
        }
        else if (operation == "-") 
        {
            std::cout << a << " - " << b << " = " << my_minus(a, b) << std::endl; continue;
        }
        else if (operation == "*") 
        {
            std::cout << a << " * " << b << " = " << my_multiply(a, b) << std::endl; continue;
        }
        else if (operation == "/")
        {
            double tmp = my_division(a, b);
            std::cout << a << " / " << b << " = " << tmp << std::endl; continue;
            continue; 
        }
        else if (operation == "pow")
        {
            double tmp = my_pow(a, b);
            std::cout << a << "^" << b << " = " << tmp << std::endl; continue;
            continue; 
        }
        
        else
        {
            throw std::invalid_argument("The operation is not implemented or does not exist");
        }
    }
}
int main()
{
    while (true)
    {
    try
        {
            calculator();
        }
        catch(const OperandInputError& e)
        {
            std::cout << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        catch(const Exit& e)
        {
            break;
        }
        catch(const MathException& e)
        {
            std::cout << e.what() << std::endl;
        }
        catch(const std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
#include "calc.hpp"

double Calculator::OperatorCalc(char op, double num1, double num2) {
    switch (op)
    {
    case '+':
        return num1 + num2;
        break;
    case '-':
        return num1 - num2;
        break;
    case '*':
        return num1 * num2;
        break;
    case '/':
        if (num2 == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return num1 / num2;
        break;
    default:
        throw std::invalid_argument("Invalid operator");
    }
}

void Calculator::PrintStack(std::stack<double> running_stack) {
    std::stack<double> temp = running_stack;
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}

double Calculator::Calculate(std::string expression) {
    std::stack<double> running_stack;
    bool isNum = false;
    bool isNeg = false;
    for(size_t i = 0; i < expression.length(); ++i) {
        // Operator
        if (expression[i] == '+' ||
        (expression[i] == '-' && (i == expression.length() - 1 || expression[i + 1] == ' ')) || 
         expression[i] == '*' || 
         expression[i] == '/') {
            isNum = false;
            if(running_stack.size() < 2) {
                throw std::invalid_argument("Invalid expression");
            }
            double num2 = running_stack.top();
            running_stack.pop();
            double num1 = running_stack.top();
            running_stack.pop();
            double result = OperatorCalc(expression[i], num1, num2);
            running_stack.push(result);
        } else if (expression[i] == '-' && expression[i + 1] != ' ')
        {
            isNeg = true;
        } else if (expression[i] == ' ') {
            // Space
            isNum = false;
        } else if(expression[i] == '.') {
            throw std::invalid_argument("Invalid expression");
        } else {
            // Number including decimal, negative
            isNum = true;
            double num = 0;
            int decimalCount = 1;
            bool isDecimal = false;
            while (i < expression.length()) {
                if(expression[i] >= '0' && expression[i] <= '9' && !isDecimal) {
                    num = num * 10 + (expression[i] - '0');
                    i++;
                } else if(expression[i] == '.') {
                    isDecimal = true;
                    i++;
                } else if(expression[i] >= '0' && expression[i] <= '9' && isDecimal) {
                    num = num + ((expression[i] - '0') / pow(10, decimalCount++));
                    i++;
                } else {
                    break;
                }
            }
            running_stack.push((isNeg ? -1. : 1.) * num);
            isNeg = false;
            i--;
        }
    }
    if(running_stack.size() == 0) {
        return 0;
    }
    if (running_stack.size() != 1) {
        throw std::invalid_argument("Invalid expression");
    }

    return running_stack.top();
}

Calculator::Calculator() {}
Calculator::~Calculator() {}
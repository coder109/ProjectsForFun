#ifndef CALC_HPP_
#define CALC_HPP_

#include <string>
#include <stack>
#include <stdexcept>
#include <iostream>

class Calculator {
    public:
        double OperatorCalc(char op, double num1, double num2);
        double Calculate(std::string expression);
        void PrintStack(std::stack<double> running_stack);
        Calculator();
        ~Calculator();
};

#endif
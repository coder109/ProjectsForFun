#include "calc.hpp"
#include <vector>
#include <iostream>

int main(int argc, char **argv) {
    Calculator calc = Calculator();
    // Test
    std::vector<std::string> valid_easy_examples = {"2 3 +", "5 3 -", "2 3 *", "6 2 /"};
    std::vector<double> valid_easy_results = {5, 2, 6, 3};
    std::vector<std::string> valid_complex_examples = {"2 3 + 4 *", "5 1 2 + 4 * + 3 -"};
    std::vector<double> valid_complex_results = {20, 14};
    std::vector<std::string> valid_edge_examples = {"    42    ", "    ", "", "   42   2    +", "1 3+"};
    std::vector<double> valid_edge_results = {42, 0, 0, 44, 4};
    
    std::vector<std::string> invalid_examples = {"2 3 + 4 * +", "5 1 2 + 4 * + - - 3 -", "3 0 /", "3 1 - 0 /", "   42    2   "};
    std::vector<std::invalid_argument> invalid_results = {std::invalid_argument("Invalid expression"), std::invalid_argument("Invalid expression"), std::invalid_argument("Division by zero"), std::invalid_argument("Division by zero")};
    
    int correct_num = 0;
    std::cout << "Valid easy examples" << std::endl;
    for(size_t i = 0; i < valid_easy_examples.size(); ++i) {
        if(calc.Calculate(valid_easy_examples[i]) == valid_easy_results[i]) {
            std::cout << valid_easy_examples[i] << " = " << valid_easy_results[i] << std::endl;
            correct_num += 1;
        } else {
            std::cout << valid_easy_examples[i] << " = " << calc.Calculate(valid_easy_examples[i]) << " != " << valid_easy_results[i] << std::endl;
        }
    }
    std::cout << "Correct num: " << correct_num << std::endl;
    std::cout << "Total num: " << valid_easy_examples.size() << std::endl;

    std::cout << "Valid complex examples" << std::endl;
    correct_num = 0;
    for(size_t i = 0; i < valid_complex_examples.size(); ++i) {
        if(calc.Calculate(valid_complex_examples[i]) == valid_complex_results[i]) {
            std::cout << valid_complex_examples[i] << " = " << valid_complex_results[i] << std::endl;
            correct_num += 1;
        } else {
            std::cout << valid_complex_examples[i] << " = " << calc.Calculate(valid_complex_examples[i]) << " != " << valid_complex_results[i] << std::endl;
        }
    }
    std::cout << "Correct num: " << correct_num << std::endl;
    std::cout << "Total num: " << valid_complex_examples.size() << std::endl;

    std::cout << "Valid edge examples" << std::endl;
    correct_num = 0;
    for(size_t i = 0; i < valid_edge_examples.size(); ++i) {
        if(calc.Calculate(valid_edge_examples[i]) == valid_edge_results[i]) {
            std::cout << valid_edge_examples[i] << " = " << valid_edge_results[i] << std::endl;
            correct_num += 1;
        } else {
            std::cout << valid_edge_examples[i] << " = " << calc.Calculate(valid_edge_examples[i]) << " != " << valid_edge_results[i] << std::endl;
        }
    }
    std::cout << "Correct num: " << correct_num << std::endl;
    std::cout << "Total num: " << valid_edge_examples.size() << std::endl;

    
    std::cout << "Invalid examples" << std::endl;
    correct_num = 0;
    for(size_t i = 0; i < invalid_examples.size(); ++i) {
        try {
            calc.Calculate(invalid_examples[i]);
        } catch (std::invalid_argument) {
            correct_num += 1;
        }
    }
    std::cout << "Correct num: " << correct_num << std::endl;
    std::cout << "Total num: " << invalid_examples.size() << std::endl;
    
    return 0;
}
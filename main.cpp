#include "calculator.h"
#include "tests.h"

int main() {

    //tests_calculator();

    Calculator calculator;
    const int MAX_SIZE = 1000;
    char input[MAX_SIZE];

    std::cout << "Input: ";

    std::cin.getline(input, MAX_SIZE);

    try {
        double result = calculator.calc(input);
        double part = result - (int)result;
        if (part != 0.0) {
            std::cout << "Result: " << result << std::endl;
        }
        else {
            std::cout << "Result: " << result << ".0" << std::endl;
        }
    }
    catch (const std::runtime_error& e) {
       std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
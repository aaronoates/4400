#include <iostream>
#include <stack>
#include <string>
#include <vector>

int evaluate_rpn(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end) {
    std::stack<int> stack;

    for (auto it = begin; it != end; ++it) {
        const std::string& token = *it;

        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Invalid RPN expression");
            }

            int operand2 = stack.top();
            stack.pop();

            int operand1 = stack.top();
            stack.pop();

            int result;
            if (token == "+") {
                result = operand1 + operand2;
            } else if (token == "-") {
                result = operand1 - operand2;
            } else if (token == "*") {
                result = operand1 * operand2;
            } else if (token == "/") {
                result = operand1 / operand2;
            }

            stack.push(result);
        } else {
            int value = std::stoi(token);
            stack.push(value);
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid RPN expression");
    }

    return stack.top();
}

int main() {
    std::vector<std::string> tokens = {"1", "2", "+", "3", "*"};
    int result = evaluate_rpn(tokens.begin(), tokens.end());
    std::cout << "Result: " << result << std::endl;

    return 0;
}
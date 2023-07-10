#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
int evaluateRPN(vector<string>::const_iterator begin, vector<string>::const_iterator end) { //creates constant vectors of strings that are used as iterators through the stack
    stack<int> stack; // initializes a stack called stack

    for (auto it = begin; it != end; ++it) {
        const string& token = *it; //creates a constant reference to the value pointed to by it

        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2) {
                cerr << "Invalid RPN expression: Insufficient operands." << endl; //
                return 0;
            }

            int operand2 = stack.top(); // takes the top value of the downwards-growing stack
            stack.pop(); //removes it from the stack

            int operand1 = stack.top(); //same thing
            stack.pop();

            int result;
            // chooses an operation
            if (token == "+")
                result = operand1 + operand2;
            else if (token == "-")
                result = operand1 - operand2;
            else if (token == "*")
                result = operand1 * operand2;
            else if (token == "/")
                result = operand1 / operand2;

            stack.push(result);
        } else {
            int operand = stoi(token);
            stack.push(operand);
        }
    }

    if (stack.size() != 1) {
        cerr << "Invalid RPN expression: Too many operands." << endl;
        return 0;
    }

    return stack.top();
}

int main() {
    vector<string> tokens = { "1", "2", "+", "3", "*" }; //initializes the vector of tokens
    int result = evaluateRPN(tokens.begin(), tokens.end());
    cout << "Result: " << result << endl;

    return 0;
}
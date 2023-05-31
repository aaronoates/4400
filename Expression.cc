#include <iostream>
#include <sstream> 
#include "expression.h"
#include <stdexcept>



using namespace std;
using namespace calc; 

calc::BinaryExpression::BinaryExpression(calc::ExpPtr lhs, calc::ExpPtr rhs) 
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) { // moves the lhs and rhs values to their private counterparts

    }

class classAdd : public calc::BinaryExpression {
    public:
    classAdd(ExpPtr lhs, ExpPtr rhs) : BinaryExpression (std::move(lhs), std::move(rhs)) {} // takes the memory from the inputted left and right hand pointers
    double evaluate() const override { //to access the evaluate method, it must be overriden with this lhs and this rhs. This allows the pointers to be evaluated as numerical values.
        
        return this->lhs_->evaluate() + this->rhs_->evaluate();

        }
    
};

class classSubtract : public calc::BinaryExpression {
    public:
    classSubtract(ExpPtr lhs, ExpPtr rhs) : BinaryExpression (std::move(lhs), std::move(rhs)) {} //same process for the below 
    double evaluate() const override {
        
        return this->lhs_->evaluate() - this->rhs_->evaluate();

        }

};

class classMultiply : public calc::BinaryExpression {
    public:
    classMultiply(ExpPtr lhs, ExpPtr rhs) : BinaryExpression (std::move(lhs), std::move(rhs)) {}
    double evaluate() const override {
        
        return this->lhs_->evaluate() * this->rhs_->evaluate();

        }

};

class classDivide : public calc::BinaryExpression {
    public:
        classDivide(ExpPtr lhs, ExpPtr rhs) : BinaryExpression (std::move(lhs), std::move(rhs)) {}
        double evaluate() const override {
        if (this->rhs_ != 0) { //ensures that you can't divide by 0.
             return this->lhs_->evaluate() / this->rhs_->evaluate(); 
        } else {
            return 0;
        }
        }
    private:


};

class classLiteral : public calc::Expression {
    public:
        classLiteral(double ExpLit) : ExpLit_(ExpLit){


        }
        double evaluate() const override {
            return this->ExpLit_;
            }
    
    private:
        const double ExpLit_;
    
};

ExpPtr BinaryExpression::Add(ExpPtr lhs, ExpPtr rhs) {
    return std::make_unique<classAdd>(std::move(lhs), std::move(rhs)); //creates a unique pointer that holds the value of the sum of the pointer values of the left and right hand sides of the expression
}

ExpPtr BinaryExpression::Subtract(ExpPtr lhs, ExpPtr rhs){
    return std::make_unique<classSubtract>(std::move(lhs), std::move(rhs));
}

ExpPtr BinaryExpression::Multiply(ExpPtr lhs, ExpPtr rhs){
    return std::make_unique<classMultiply>(std::move(lhs), std::move(rhs));
}

ExpPtr BinaryExpression::Divide(ExpPtr lhs, ExpPtr rhs){
    return std::make_unique<classDivide>(std::move(lhs), std::move(rhs));
}

ExpPtr Expression::Parse(std::string ExpStr) {
    // Helper function to parse integer literals
    //change literal to ExpStr if literal doesnt work (this is a note for Aaron to himself in the process of debugging :D)
    auto parseLiteral = [](const std::string& ExpStr) -> ExpPtr {  //ensures that this function does not access the string literal within the scope.
        try {
            //return std::stoi(ExpStr); //converts the literal value to an integer
            return Expression::Literal(std::stod(ExpStr));
        } catch (const std::invalid_argument&) { //if the input is not pointing to a string, it won't run.
            throw std::runtime_error("Not pointing to a string. " + ExpStr);
        } 
    };

    // Check if the input string is empty
    if (ExpStr.empty()) {
        throw std::runtime_error("Nothing's Here.");
    }

    std::istringstream iss(ExpStr);
    std::string token;
    std::getline(iss, token, ' '); // lets the user input the operator in the terminal, which is assigned to the value token and spaced apart

    // Parse the first literal
    ExpPtr exp = parseLiteral(token);

    // Parse the remaining tokens
    while (std::getline(iss, token, ' ')) { // every time you input something, this code repeats.
        if (token == "+") {
            // Addition operation
            std::getline(iss, token, ' '); // Get the next literal
            exp = BinaryExpression::Add(std::move(exp), parseLiteral(token));
            //exp = std::make_unique<classAdd>(std::move(exp), parseLiteral(token));
        } else if (token == "*") {
            // Multiplication operation
            std::getline(iss, token, ' '); // Get the next literal
            exp = BinaryExpression::Multiply(std::move(exp), parseLiteral(token));
        } else if (token == "-") {
            std::getline(iss, token, ' '); // Get the next literal
            exp = BinaryExpression::Subtract(std::move(exp), parseLiteral(token));
            
        } else if (token == "/") {
            std::getline(iss, token, ' '); // Get the next literal
            exp = BinaryExpression::Divide(std::move(exp), parseLiteral(token));
        } else {
            throw std::runtime_error("Invalid token: " + token);
        }
    }

    return exp;
}
ExpPtr Expression::Literal(double x){
    ExpPtr ptr = std::make_unique<classLiteral>(x);
    return ptr;
}









   

    

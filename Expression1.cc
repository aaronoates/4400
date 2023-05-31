#include <iostream>
#include <sstream>
#include "expression.h"


using namespace std;
using namespace calc; 

calc::BinaryExpression::BinaryExpression(calc::ExpPtr lhs, calc::ExpPtr rhs) 
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) { // moves the lhs and rhs values to their private counterparts

    }

class classAdd : public calc::BinaryExpression {
    classAdd(ExpPtr lhs, ExpPtr rhs) : BinaryExpression (std::move(lhs), std::move(rhs)) {} // takes the memory from the inputted left and right hand pointers
    double evaluate() const override { //to access the evaluate method, it must be overriden with this lhs and this rhs. This allows the pointers to be evaluated as numerical values.
        
        return this->lhs_->evaluate() + this->rhs_->evaluate();

        }
    
};

class classSubtract : public calc::BinaryExpression {
    classSubtract(ExpPtr lhs, ExpPtr rhs) : BinaryExpression (std::move(lhs), std::move(rhs)) {} //same process for the below 
    double evaluate() const override {
        
        return this->lhs_->evaluate() - this->rhs_->evaluate();

        }

};

class classMultiply : public calc::BinaryExpression {
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
    return std::make_unique<Add>(std::move(lhs), std::move(rhs));
}

ExpPtr BinaryExpression::Subtract(ExpPtr lhs, ExpPtr rhs){
    return std::make_unique<Subtract>(std::move(lhs), std::move(rhs));
}

ExpPtr BinaryExpression::Multiply(ExpPtr lhs, ExpPtr rhs){
    return std::make_unique<Multiply>(std::move(lhs), std::move(rhs));
}

ExpPtr BinaryExpression::Divide(ExpPtr lhs, ExpPtr rhs){
    return std::make_unique<Divide>(std::move(lhs), std::move(rhs));
}

ExpPtr Expression::Parse(std::string expStr) {
    char op;
    double operand = 0.0;
    
    std::istringstream iss(expStr);

    while (iss >> operand) {
        if (op == '+'){
            BinaryExpression::Add(lhs, rhs);
        } else if (op == '-'){
            BinaryExpression::Subtract(lhs, rhs);
        } else if (op == '*'){
            BinaryExpression::Multiply(lhs, rhs);  
        } else if (op == '/'){
            BinaryExpression::Divide(lhs, rhs);
        } else {
            cout << "nice try Jon." << endl;
        }
    }
}

ExpPtr Expression::Literal(double x){
    ExpPtr ptr = std::make_unique<Literal>(x);
    return ptr;
}









   

    

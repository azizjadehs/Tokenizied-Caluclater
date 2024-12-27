#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <stdexcept>
#include "DList.h"

class Token {
public:
    // Constructor for a number
    Token(float number) : _number(number), _isOperator(false) {}

    // Constructor for an operator
    Token(const std::string& op) : _operator(op), _isOperator(true) {}

    // Check if the token is an operator
    bool isOperator() const { return _isOperator; }

    // Get the number (valid only if it's not an operator)
    float getNumber() const {
        if (_isOperator) throw std::logic_error("Token is not a number");
        return _number;
    }

    // Get the operator (valid only if it's an operator)
    std::string getOperator() const {
        if (!_isOperator) throw std::logic_error("Token is not an operator");
        return _operator;
    }

private:
    float _number;             // Stores the number if the token is a number
    std::string _operator;     // Stores the operator if the token is an operator
    bool _isOperator;          // True if this token is an operator, false if it’s a number
};

// Function declaration
void parse(std::string& str, Queue<Token>& queue);


#endif
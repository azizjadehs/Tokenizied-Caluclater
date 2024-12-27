#include <stdexcept> // For exception handling
#include <cmath>     // For pow()

#include "TwoStackAlgo.h"
#include "Token.h"

using namespace std;

double performOperation(double a, double b, const std::string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    if (op == "^") return pow(a, b);
    throw std::invalid_argument("Unsupported operator: " + op);
}

int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0; // Invalid operator
}

void processStacks(Stack<double>& operands, Stack<std::string>& operators) {
    double b = operands.pop();
    double a = operands.pop();
    std::string op = operators.pop();
    double result = performOperation(a, b, op);
    operands.push(result);
}

double calc(std::string& expression) { // Pass by value so it's modifiable
    Queue<Token> tokenQueue;
    parse(expression, tokenQueue); // Tokenize the input (modifies the local copy)
    
    Stack<double> operands;       // Stack for numbers
    Stack<std::string> operators; // Stack for operators

    while (!tokenQueue.isEmpty()) {
        Token token = tokenQueue.dequeue();

        if (!token.isOperator()) {
            operands.push(token.getNumber());
        } else {
            std::string op = token.getOperator();

            while (!operators.isEmpty() && 
                   precedence(op) <= precedence(operators.peek())) {
                processStacks(operands, operators);
            }
            operators.push(op);
        }
    }

    while (!operators.isEmpty()) {
        processStacks(operands, operators);
    }

    if (operands.isEmpty()) throw std::runtime_error("Invalid expression");
    return operands.pop();
}
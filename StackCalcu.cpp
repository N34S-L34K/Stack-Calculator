#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

int calculate(int num1, int num2, char op) {
    if (op == '+') return num1 + num2;
    if (op == '-') return num1 - num2;
    if (op == '*') return num1 * num2;
    if (op == '/') return num1 / num2;
    return 0;
}

string convertToPostfix(string infix) {
    stack<char> operators;
    stringstream postfix;

    for (char token : infix) {
        if (isspace(token)) continue; 
        if (isdigit(token)) {
            postfix << token; 
        } else if (token == '(') {
            operators.push(token); 
        } else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix << ' ' << operators.top();
                operators.pop();
            }
            operators.pop(); 
        } else { 
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(token)) {
                postfix << ' ' << operators.top();
                operators.pop();
            }
            postfix << ' '; 
            operators.push(token); 
        }
    }

   
    while (!operators.empty()) {
        postfix << ' ' << operators.top();
        operators.pop();
    }

    return postfix.str();
}


int evaluatePostfix(string postfix) {
    stack<int> operands;
    stringstream tokens(postfix);
    string token;

    while (tokens >> token) {
        if (isdigit(token[0])) {
            operands.push(stoi(token)); 
        } else { 
            int num2 = operands.top(); operands.pop(); 
            int num1 = operands.top(); operands.pop();
            operands.push(calculate(num1, num2, token[0])); 
        }
    }

    return operands.top();
}


void runCalculator() {
    string infix;

    while (true) {
        cout << "Enter Operation or type 'exit' to quit: ";
        getline(cin, infix);

       
        if (infix == "exit") {
            cout << "Exiting the calculator" << endl;
            break; 
        }

        string postfix = convertToPostfix(infix);
        int result = evaluatePostfix(postfix);

        cout << "The result is: " << result << endl; 
    }
}

int main() {
    runCalculator(); 
    return 0;
}

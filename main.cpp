// Name: Amer Yono
// Student ID: 200711334
// Email: yono004@cougars.csusm.edu
#include <iostream>
#define SIZE 10
using namespace std;

// Template stack class
template <class Template>
class Stack {
    private:
        Template array[SIZE];
        int top;
    public:
        Stack();
        Template push(Template);
        Template pop();
        Template getTop();
        int isEmpty();
        int isFull();
};

template <class Template>
Stack<Template>::Stack() {
    // Set top to -1
    top = -1;
}

template <class Template>
Template Stack<Template>::push(Template n) {
    if (isFull()) return 0;
    ++top;
    array[top] = n;
    return n;
}

template <class Template>
Template Stack<Template>::pop() {
    Template temp;
    if(isEmpty()) return 0;
    temp = array[top];
    --top;
    return temp;
}

template <class Template>
Template Stack<Template>::getTop() {
    return array[top];
}

template <class Template>
int Stack<Template>::isEmpty() {
    if (top == -1) return 1;
    else return 0;   
}
 
template <class Template>
int Stack<Template>::isFull() {
    if (top == SIZE - 1) return 1;
    else return 0;
}

int orderOfOperations(char operation) {
    if (operation == '+' || operation == '-') return 1;
    if (operation == '*' || operation == '/') return 2;
    return 0;
}

int operationCase(int numOne, int numTwo, char operation) {
    switch (operation) {
        case '+': return numOne + numTwo;
        case '-': return numOne - numTwo;
        case '*': return numOne * numTwo;
        case '/': return numOne / numTwo;
    }
}

double evalExpression(const char* exp) {
    // Convert to string to easily get length
    const char* tempExp = exp;
    std::string tempExpString = tempExp;

    // Converts letters to decimal value
    if (isdigit(*exp)) {
        cout << "Problem: " << tempExpString << endl;

        Stack<int> values;
        Stack<char> operations;

        for (int i = 0; i < tempExpString.length(); i++) {
            // Check for spaces, division by 0, and parenthesis
            if (exp[i] == ' ') continue;
            if (exp[i] == '/' && (exp[i + 2]  == '0' || exp[i + 1]  == '0')) cout << "You cannot divide by 0." << endl;
            
            else if (exp[i] == '(') operations.push(exp[i]);
            else if (isdigit(exp[i])) {
                int value = 0;
                while (i < tempExpString.length() && isdigit(exp[i])) {
                    value = (value * 10) + (exp[i] - '0');
                    i++;
                }

                values.push(value);
                i--;
            } else if (exp[i] == ')') {
                while (!operations.isEmpty() && operations.getTop() != '(') {
                    int valueTwo = values.getTop();
                    values.pop();

                    int valueOne = values.getTop();
                    values.pop();

                    char operation = operations.getTop();
                    operations.pop();

                    values.push(operationCase(valueOne, valueTwo, operation));
                }

                if (!operations.isEmpty()) operations.pop();
            } else {
                while (!operations.isEmpty() && orderOfOperations(operations.getTop()) >= orderOfOperations(exp[i])) {
                    int valueTwo = values.getTop();
                    values.pop();

                    int valueOne = values.getTop();
                    values.pop();

                    char operation = operations.getTop();
                    operations.pop();

                    values.push(operationCase(valueOne, valueTwo, operation));
                }
                operations.push(exp[i]);
            }
        }

        while (!operations.isEmpty()) {
            int valueTwo = values.getTop();
            values.pop();

            int valueOne = values.getTop();
            values.pop();

            char operation = operations.getTop();
            operations.pop();

            values.push(operationCase(valueOne, valueTwo, operation));
        }

        cout << "Answer: " << values.getTop() << endl << endl;
    } else cout << "Invalid Problem: " << tempExpString << endl << endl;
}

int main() {
    // Test error cases as well as normal cases
    evalExpression("10 * ( 10 + 1 + 3 ) /0");
    evalExpression("10 * ( 10 + 1 + 3 ) / 0");
    evalExpression("- - /2 ");
    evalExpression("empty");
    evalExpression("");
    evalExpression("1 + 200");
    evalExpression("1+200");
    evalExpression("400/         200");
    evalExpression("100 * ( 2 + 13 ) / 11");
    return 0;
}
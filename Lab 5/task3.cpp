#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// char node for infix to postfix stack
struct CharNode {
    char data;
    CharNode* next;
};

// int node for evaluation stack
struct IntNode {
    int data;
    IntNode* next;
};

// stack for characters
class CharStack {
private:
    CharNode* topNode;
public:
    CharStack() {
        topNode = NULL;
    }

    bool isEmpty() {
        return topNode == NULL;
    }

    void push(char c) {
        CharNode* newNode = new CharNode();
        newNode->data = c;
        newNode->next = topNode;
        topNode = newNode;
    }

    char pop() {
        if (isEmpty()) return '\0';
        CharNode* temp = topNode;
        char val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    char top() {
        if (isEmpty()) return '\0';
        return topNode->data;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    ~CharStack() {
        clear();
    }
};

// stack for int evaluation
class IntStack {
private:
    IntNode* topNode;
public:
    IntStack() {
        topNode = NULL;
    }

    bool isEmpty() {
        return topNode == NULL;
    }

    void push(int val) {
        IntNode* newNode = new IntNode();
        newNode->data = val;
        newNode->next = topNode;
        topNode = newNode;
    }

    int pop() {
        if (isEmpty()) return 0;
        IntNode* temp = topNode;
        int val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    int top() {
        if (isEmpty()) return 0;
        return topNode->data;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    ~IntStack() {
        clear();
    }
};


// precedence function
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

// check if char is operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

// convert infix to postfix
bool infixToPostfix(string infix, string &postfix, string &errorMsg) {
    postfix = "";
    CharStack s;

    if (infix.length() == 0) {
        errorMsg = "Empty expression!";
        return false;
    }

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if (ch == ' ') continue;

        // if operand (number)
        if (isdigit(ch)) {
            while (i < infix.length() && isdigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += ' ';
            i--; // adjust loop index
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            bool foundOpen = false;
            while (!s.isEmpty()) {
                if (s.top() == '(') {
                    s.pop();
                    foundOpen = true;
                    break;
                }
                postfix += s.pop();
                postfix += ' ';
            }
            if (!foundOpen) {
                errorMsg = "Mismatched parentheses (extra closing bracket)";
                return false;
            }
        }
        else if (isOperator(ch)) {
            while (!s.isEmpty() && s.top() != '(' && getPrecedence(s.top()) >= getPrecedence(ch)) {
                postfix += s.pop();
                postfix += ' ';
            }
            s.push(ch);
        }
        else {
            errorMsg = "Invalid character in expression";
            return false;
        }
    }

    // pop remaining operators from stak
    while (!s.isEmpty()) {
        if (s.top() == '(') {
            errorMsg = "Mismatched parentheses (unclosed opening bracket)";
            return false;
        }
        postfix += s.pop();
        postfix += ' ';
    }

    return true;
}

// evaluate postfix expression
bool evaluatePostfix(string postfix, int &result, string &errorMsg) {
    IntStack s;

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        if (ch == ' ') continue;

        if (isdigit(ch)) {
            int num = 0;
            while (i < postfix.length() && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            s.push(num);
            i--;
        }
        else if (isOperator(ch)) {
            if (s.isEmpty()) {
                errorMsg = "Invalid postfix expression";
                return false;
            }
            int val2 = s.pop();

            if (s.isEmpty()) {
                errorMsg = "Invalid postfix expression";
                return false;
            }
            int val1 = s.pop();

            if (ch == '+') s.push(val1 + val2);
            else if (ch == '-') s.push(val1 - val2);
            else if (ch == '*') s.push(val1 * val2);
            else if (ch == '/') {
                if (val2 == 0) {
                    errorMsg = "Error: Division by zero!";
                    return false;
                }
                s.push(val1 / val2);
            }
            else if (ch == '%') {
                if (val2 == 0) {
                    errorMsg = "Error: Modulo by zero!";
                    return false;
                }
                s.push(val1 % val2);
            }
        }
    }

    if (s.isEmpty()) {
        errorMsg = "Evaluation error";
        return false;
    }

    result = s.pop();
    if (!s.isEmpty()) {
        errorMsg = "Malformed expression error";
        return false;
    }

    return true;
}

void testExpression(string expr) {
    cout << "Infix Expression: " << expr << endl;
    string postfix = "";
    string errorMsg = "";

    if (!infixToPostfix(expr, postfix, errorMsg)) {
        cout << "Error in conversion: " << errorMsg << endl;
        cout << "----------------------------------------" << endl;
        return;
    }

    cout << "Postfix Expression: " << postfix << endl;

    int result = 0;
    if (!evaluatePostfix(postfix, result, errorMsg)) {
        cout << "Error in evaluation: " << errorMsg << endl;
    } else {
        cout << "Evaluated Result: " << result << endl;
    }
    cout << "----------------------------------------" << endl;
}

int main() {
    cout << "Task 3: Infix to Postfix & Expression Evaluation\n\n";

    cout << "--- Standard Required Tests ---" << endl;
    testExpression("2 + 3 * 4");
    testExpression("(2 + 3) * 4");
    testExpression("10 + 2 * 6");
    testExpression("(10 + 2) * (6 - 3)");
    testExpression("20 / 5 + 3");

    cout << endl << "--- Additional Edge Cases ---" << endl;
    testExpression("((2 + 3) * (4 + 2))");      // Nested parentheses
    testExpression("10 + 5 * 2 - 8 / 4");      // Multiple operators
    testExpression("");                        // Empty expression
    testExpression("(2 + 3 * 4");              // Mismatched parentheses
    testExpression("10 / 0");                  // Division by zero

    return 0;
}

#include <iostream>
#include <string>

using namespace std;

// node struct for stack
struct Node {
    char data;
    Node* next;
};

// stack clas using linked list
class Stack {
private:
    Node* topNode;

public:
    Stack() {
        topNode = NULL;
    }

    // check if stak is emty
    bool isEmpty() {
        return topNode == NULL;
    }

    // push char onto top
    void push(char val) {
        Node* newNode = new Node();
        newNode->data = val;
        newNode->next = topNode;
        topNode = newNode;
    }

    // pop char from top
    char pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return '\0';
        }
        Node* temp = topNode;
        char poppedVal = temp->data;
        topNode = topNode->next;
        delete temp;
        return poppedVal;
    }

    // get top char
    char top() {
        if (isEmpty()) {
            return '\0';
        }
        return topNode->data;
    }

    // display current stack
    void displayStack() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }
        Node* curr = topNode;
        cout << "Stack content: ";
        while (curr != NULL) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    // clear all nodes to avoid leak
    void clearStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    ~Stack() {
        clearStack();
    }
};

// helper to check if brackets matches
bool isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '[' && close == ']') return true;
    if (open == '{' && close == '}') return true;
    return false;
}

// chek balance function
bool checkBalance(string expr) {
    Stack s;

    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        // if opening bracket push to stak
        if (ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);
        }
        // if closing bracket
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.isEmpty()) {
                // extra closing bracket
                return false;
            }
            char topChar = s.pop();
            if (!isMatchingPair(topChar, ch)) {
                // mismatched bracket
                return false;
            }
        }
    }

    // if stack is emty then balanced
    bool balanced = s.isEmpty();
    s.clearStack();
    return balanced;
}

int main() {
    cout << "Task 1: Expression Parentheses Checker\n\n";

    string testCases[] = {
        "(A+B)",
        "{A+[B*C]}",
        "(A+B]",
        "((A+B)",
        "{[()]}",
        "A+B*C",
        "([A+B])"
    };

    int numTests = 7;

    for (int i = 0; i < numTests; i++) {
        string expr = testCases[i];
        cout << "Expression " << (i + 1) << ": " << expr << endl;
        
        if (checkBalance(expr)) {
            cout << "Result: Balanced" << endl;
        } else {
            cout << "Result: Not Balanced" << endl;
        }
        cout << "----------------------------------------" << endl;
    }

    return 0;
}

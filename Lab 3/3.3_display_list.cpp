#include <iostream>

using namespace std;


struct Node {

    int data;

    Node* next;

    Node(int val) : data(val), next(nullptr) {}

};


void displayList(Node* head) {
    if (head == nullptr) {

        cout << "List is empty: NULL\n";

        return;
    }

    Node* current = head;
    while (current != nullptr) {

        cout << current->data << " -> ";

        current = current->next;
    }
    cout << "NULL\n";
}

// Deallocates all nodes in the list and resets head pointer
void freeList(Node*& head) {
    Node* current = head;

    while (current != nullptr) {

        Node* nextNode = current->next;

        delete current;
        current = nextNode;
    }
    head = nullptr;
}

int main() {

    // Test 1: Empty list
    cout << "Test 1: Empty List\n";
    Node* emptyList = nullptr;

    displayList(emptyList);
    cout << "\n";

    // Test 2: Single-node list
    cout << "Test 2: Single-Node List\n";
    Node* singleList = new Node(10);

    displayList(singleList);
    cout << "\n";

    // Test 3: Multi-node list
    cout << "Test 3: Multi-Node List\n";

    Node* multiList = new Node(10);
    multiList->next = new Node(20);

    multiList->next->next = new Node(30);
    multiList->next->next->next = new Node(40);

    displayList(multiList);
    cout << "\n";

    // Clean up :)
    freeList(emptyList);
    freeList(singleList);
    freeList(multiList);

    return 0;
}

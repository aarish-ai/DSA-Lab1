#include <iostream>

using namespace std;

// Node structure
struct Node {

    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// New Node at the beginning of the list
void insertAtHead(Node*& head, int val) {

    Node* newNode = new Node(val);

    newNode->next = head;
    head = newNode;
}

// Displays
void displayList(const Node* head) {

    const Node* curr = head;

    while (curr != nullptr) {
        cout << curr->data << " -> ";

        curr = curr->next;
    }
    cout << "NULL\n";
}

// Frees all allocated nodes
void freeList(Node*& head) {

    while (head != nullptr) {

        Node* temp = head;

        head = head->next;

        delete temp;
    }
}

int main() {
    Node* head = nullptr;

    cout << "Inserting 10 at head...\n";
    insertAtHead(head, 10);

    cout << "Current List: ";
    displayList(head);

    cout << "\nInserting 20 at head...\n";

    insertAtHead(head, 20);

    cout << "Current List: ";
    displayList(head);

    cout << "\nInserting 30 at head...\n";

    insertAtHead(head, 30);

    cout << "Current List: ";
    displayList(head);

    cout << "\nResult: The most recently inserted value (30) is at the head of the list.\n";

    // Clean up
    freeList(head);

}

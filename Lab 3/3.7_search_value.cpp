#include <iostream>

using namespace std;

struct Node {

    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}

};

void displayList(const Node* head) {
    if (head == nullptr) {

        cout << "List is empty: NULL\n";
        
        return;
    }

    const Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL\n";
}

// Searches for a value in the list
int searchValue(Node* head, int val) {

    Node* current = head;
    int position = 1;


    while (current != nullptr) {

        if (current->data == val) {

            cout << "Value " << val << " found at position " << position << ".\n";

            return position;
        }
        current = current->next;

        position++;
    }

    cout << "Value " << val << " not found in the list.\n";

    return -1; // not found
}

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

    Node* head = new Node(10);

    head->next = new Node(25);
    head->next->next = new Node(40);

    head->next->next->next = new Node(55);

    cout << "Linked List: ";

    displayList(head);
    cout << "\n";

    cout << "Test 1: Search for value at head (10)\n";

    int pos1 = searchValue(head, 10);

    cout << "Result: position = " << pos1 << "\n\n";

    cout << "Test 2: Search for value in middle (40)\n";

    int pos2 = searchValue(head, 40);
    cout << "Result: position = " << pos2 << "\n\n";

    cout << "Test 3: Search for value at end (55)\n";

    int pos3 = searchValue(head, 55);

    cout << "Result: position = " << pos3 << "\n\n";

    cout << "Test 4: Search for non-existent value (99)\n";
    int pos4 = searchValue(head, 99);

    cout << "Result: position = " << pos4 << "\n\n";

    // Yes, indeed cleaning up again :)
    freeList(head);

}

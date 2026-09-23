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

// Removes the final node in the list and deletes its memory
void deleteLast(Node*& head) {
    if (head == nullptr) {

        cout << "List is empty. Cannot delete last node.\n";

        return;
    }

    // Single-node case
    if (head->next == nullptr) {

        delete head;

        head = nullptr;

        return;
    }

    // Multi-node case
    Node* current = head;
    while (current->next->next != nullptr) {

        current = current->next;

    }

    delete current->next;

    current->next = nullptr;
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

    
    cout << "--- Test 1: Delete from Empty List ---\n";
    Node* list1 = nullptr;
    cout << "Initial list: ";

    displayList(list1);

    cout << "Calling deleteLast()...\n";

    deleteLast(list1);

    cout << "Updated list: ";


    displayList(list1);
    cout << "\n";

    cout << "--- Test 2: Delete from 1-Node List ---\n";

    Node* list2 = new Node(10);

    cout << "Initial list: ";
    displayList(list2);

    cout << "Calling deleteLast()...\n";

    deleteLast(list2);

    cout << "Updated list: ";
    displayList(list2);

    cout << "\n";

    cout << "--- Test 3: Delete from Multi-Node List ---\n";
    Node* list3 = new Node(10);
    list3->next = new Node(20);

    list3->next->next = new Node(30);

    cout << "Initial list: ";
    displayList(list3);

    cout << "Calling deleteLast()...\n";
    deleteLast(list3);

    cout << "Updated list: ";

    displayList(list3);
    cout << "\n";

//Cleanup :)
    freeList(list1);
    freeList(list2);
    freeList(list3);

}

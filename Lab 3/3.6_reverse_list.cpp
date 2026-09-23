#include <iostream>

using namespace std;

struct Node {
    int data;

    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Reverses a singly linked list iteratively using three pointers
void reverseList(Node*& head) {
    Node* prev = nullptr;
    Node* curr = head;

    Node* next = nullptr;

    while (curr != nullptr) {

        next = curr->next;

        curr->next = prev;
        prev = curr;

        curr = next;
    }

    head = prev;
}


void displayList(const Node* head) {

    const Node* curr = head;

    while (curr != nullptr) {

        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << "NULL\n";
}

void freeList(Node*& head) {

    while (head != nullptr) {
        Node* temp = head;

        head = head->next;

        delete temp;
    }
}

int main() {

    cout << "--- Test 1: Reverse Empty List ---\n";
    Node* list1 = nullptr;
    cout << "Before: ";

    displayList(list1);
    reverseList(list1);

    cout << "After:  ";
    displayList(list1);
    cout << "\n";


    cout << "--- Test 2: Reverse Single-Node List ---\n";
    Node* list2 = new Node(10);
    cout << "Before: ";

    displayList(list2);
    reverseList(list2);

    cout << "After:  ";
    displayList(list2);
    cout << "\n";

    cout << "--- Test 3: Reverse Multi-Node List ---\n";
    Node* list3 = new Node(10);
    list3->next = new Node(20);

    list3->next->next = new Node(30);

    list3->next->next->next = new Node(40);
    cout << "Before: ";


    displayList(list3);

    reverseList(list3);

    cout << "After:  ";
    displayList(list3);

    cout << "\n";

    //CLEEEEANING UPPP :)
    freeList(list1);
    freeList(list2);
    freeList(list3);

    return 0;
}

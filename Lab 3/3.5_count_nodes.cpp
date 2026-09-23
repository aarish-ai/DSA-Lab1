#include <iostream>

using namespace std;


struct Node {
    int data;

    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

void displayList(Node* head) {

    if (head == nullptr) {

        cout << "List: NULL\n";

        return;
    }

    Node* current = head;

    cout << "List: ";

    while (current != nullptr) {

        cout << current->data << " -> ";
        current = current->next;

    }
    cout << "NULL\n";
}

// Traverses the linked list and returns the total number of nodes
int countNodes(Node* head) {
    int count = 0;

    Node* current = head;

    while (current != nullptr) {

        count++;
        current = current->next;
    }
    return count;
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

    cout << "--- Test 1: Empty List ---\n";
    Node* list1 = nullptr;
    displayList(list1);
    cout << "Node count: " << countNodes(list1) << "\n\n";

    cout << "--- Test 2: Single-Node List ---\n";
    Node* list2 = new Node(10);
    displayList(list2);
    cout << "Node count: " << countNodes(list2) << "\n\n";

    cout << "--- Test 3: Multi-Node List ---\n";
    Node* list3 = new Node(10);
    list3->next = new Node(20);
    list3->next->next = new Node(30);
    list3->next->next->next = new Node(40);
    displayList(list3);
    cout << "Node count: " << countNodes(list3) << "\n\n";

    // Yeah . . . Cleaning Up Again :)
    freeList(list1);
    freeList(list2);
    freeList(list3);

}

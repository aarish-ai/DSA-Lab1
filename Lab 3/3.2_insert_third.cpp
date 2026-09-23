#include <iostream>

using namespace std;

struct Node {
    int data;

    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Traverses and prints the linked list
void displayList(const Node* head) {

    if (head == nullptr) {

        cout << "Empty list (NULL)\n";

        return;
    }

    const Node* curr = head;

    while (curr != nullptr) {
        cout << curr->data << " -> ";

        curr = curr->next;
    }
    cout << "NULL\n";
}

// Appends a node to the end of the list
void insertAtEnd(Node*& head, int val) {

    Node* newNode = new Node(val);

    if (head == nullptr) {
        head = newNode;
        return;

    }

    Node* curr = head;

    while (curr->next != nullptr) {

        curr = curr->next;
    }


    curr->next = newNode;
}

// Inserts a node specifically at the 3rd position (1-based)
void insertAtThird(Node*& head, int val) {

    Node* newNode = new Node(val);

    // If list is empty insert as the first node
    if (head == nullptr) {

        cout << "List has fewer than 2 nodes. Inserting at end...\n";

        head = newNode;
        return;
    }

    // If list has only 1 node insert as the second node
    if (head->next == nullptr) {

        cout << "List has fewer than 2 nodes. Inserting at end...\n";

        head->next = newNode;
        return;
    }

    // List has at least 2 nodes; traverse to the 2nd node
    Node* curr = head;

    for (int i = 1; i < 2 && curr->next != nullptr; i++) {

        curr = curr->next;
    }

    // Insert newNode after the 2nd node (at 3rd position)
    newNode->next = curr->next;

    curr->next = newNode;

    cout << "Successfully inserted " << val << " at 3rd position.\n";
}

// Deallocates all nodes in the list
void freeList(Node*& head) {

    while (head != nullptr) {

        Node* temp = head;

        head = head->next;
        delete temp;
    }
}

int main() {

    // Test 1: Empty list
    cout << "--- Test 1: Insert into Empty List ---\n";

    Node* list1 = nullptr;
    cout << "Before insertion:\n";

    displayList(list1);
    cout << "Action: insertAtThird(list1, 10)\n";

    insertAtThird(list1, 10);

    cout << "After insertion:\n";

    displayList(list1);
    cout << "\n";

    // Test 2: 1-node list
    cout << "--- Test 2: Insert into 1-Node List ---\n";

    cout << "Before insertion:\n";

    displayList(list1);

    cout << "Action: insertAtThird(list1, 20)\n";

    insertAtThird(list1, 20);

    cout << "After insertion:\n";

    displayList(list1);
    cout << "\n";

    cout << "--- Test 3: Insert into List with 3+ Nodes ---\n";
    Node* list2 = nullptr;

    insertAtEnd(list2, 10);
    insertAtEnd(list2, 20);
    insertAtEnd(list2, 30);

    cout << "Before insertion:\n";

    displayList(list2);
    cout << "Action: insertAtThird(list2, 99)\n";

    insertAtThird(list2, 99);

    cout << "After insertion:\n";

    displayList(list2);
    cout << "\n";



    // Clean up
    freeList(list1);
    freeList(list2);

}

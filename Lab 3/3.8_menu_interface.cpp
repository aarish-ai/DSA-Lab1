#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Inserts a new node at the beginning of the list
void insertAtHead(Node*& head, int val) {

    Node* newNode = new Node(val);

    newNode->next = head;
    head = newNode;
}

// Inserts a node specifically at the 3rd position (1-based index)
void insertAtThird(Node*& head, int val) {

    Node* newNode = new Node(val);

    if (head == nullptr) {

        cout << "List has fewer than 2 nodes. Inserting at end...\n";

        head = newNode;
        return;
    }

    if (head->next == nullptr) {

        cout << "List has fewer than 2 nodes. Inserting at end...\n";

        head->next = newNode;
        return;
    }

    Node* curr = head;

    for (int i = 1; i < 2 && curr->next != nullptr; i++) {

        curr = curr->next;
    }

    newNode->next = curr->next;

    curr->next = newNode;
    cout << "Successfully inserted " << val << " at 3rd position.\n";
}

// Traverses and prints all nodes in the linked list
void displayList(Node* head) {

    if (head == nullptr) {

        cout << "Empty list (NULL)\n";
        return;
    }

    Node* current = head;
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

    if (head->next == nullptr) {

        cout << "Deleted last node with value: " << head->data << "\n";

        delete head;

        head = nullptr;
        return;
    }

    Node* current = head;
    while (current->next->next != nullptr) {

        current = current->next;
    }

    cout << "Deleted last node with value: " << current->next->data << "\n";

    delete current->next;

    current->next = nullptr;
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

// Reverses the linked list iteratively using three pointers
void reverseList(Node*& head) {
    Node* prev = nullptr;

    Node* current = head;

    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;

        prev = current;
        current = next;
    }

    head = prev;
}

// Searches for a value in the list; returns 1-based position if found, else -1
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
    return -1;
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
    Node* head = nullptr;
    int choice = 0;

    while (true) {
        cout << "       SINGLY LINKED LIST MENU          \n";
        cout << "1. Insert at Head\n";
        cout << "2. Insert at 3rd Position\n";
        cout << "3. Display List\n";
        cout << "4. Delete Last Node\n";
        cout << "5. Count Nodes\n";
        cout << "6. Reverse List\n";
        cout << "7. Search Value\n";
        cout << "8. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Enter your choice (1-8): ";

        if (!(cin >> choice)) {
            if (cin.eof()) {

                cout << "\nEnd of input reached. Exiting...\n";
                break;
            }
            cout << "Invalid input. Please enter a valid number.\n";

            cin.clear();

            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 8) {
            cout << "Exiting...\n";

            break;
        }

        switch (choice) {
            case 1: {
                int val;
                cout << "Enter value to insert at head: ";

                if (cin >> val) {
                    insertAtHead(head, val);

                    cout << "Successfully inserted " << val << " at head.\n";

                    cout << "Current List: ";
                    displayList(head);
                } else {
                    cout << "Invalid input for value.\n";

                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                break;
            }
            case 2: {
                int val;
                cout << "Enter value to insert at 3rd position: ";

                if (cin >> val) {
                    insertAtThird(head, val);

                    cout << "Current List: ";
                    displayList(head);
                } else {
                    cout << "Invalid input for value.\n";

                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                break;
            }
            case 3: {
                cout << "Current List: ";

                displayList(head);
                break;
            }
            case 4: {
                deleteLast(head);

                cout << "Current List: ";
                displayList(head);
                break;
            }
            case 5: {

                int count = countNodes(head);

                cout << "Total number of nodes: " << count << "\n";

                break;
            }
            case 6: {

                reverseList(head);
                cout << "List reversed successfully.\n";

                cout << "Current List: ";
                displayList(head);
                break;

            }
            case 7: {
                int val;
                cout << "Enter value to search: ";

                if (cin >> val) {
                    searchValue(head, val);

                } else {
                    cout << "Invalid input for value.\n";
                    cin.clear();

                    cin.ignore(10000, '\n');
                }
                break;
            }
            default: {
                cout << "Invalid choice! Please select an option from 1 to 8.\n";

                break;
            }
        }
    }

    // Cleaning Up for the last time . . .  :)
    freeList(head);
    cout << "Dynamic memory successfully deallocated.\n";

}

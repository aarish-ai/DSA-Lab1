#include <iostream>

using namespace std;

// Node for circular linked list
struct PersonNode {
    int personID;

    PersonNode* next;
};

class JosephusCircle {
private:
    PersonNode* head;
    int totalPeople;

public:
    JosephusCircle() {
        head = NULL;
        totalPeople = 0;
    }

    // 1. Create Circle of N people (IDs 1 to N)
    void createCircle(int n) {
        if (n <= 0) {
            cout << "Invalid number of people." << endl;
            return;
        }

        totalPeople = n;
        head = new PersonNode();
        head->personID = 1;
        head->next = head;

        PersonNode* current = head;

        for (int i = 2; i <= n; i++) {

            PersonNode* newNode = new PersonNode();
            newNode->personID = i;

            newNode->next = head; // circular link
            current->next = newNode;

            current = newNode;
        }

        cout << "Circular list created with " << n << " people (IDs: 1 to " << n << ")." << endl;
    }

    // Display all people currently in circle
    void displayCircle() {
        if (head == NULL) {
            cout << "Circle is empty." << endl;
            return;
        }

        PersonNode* temp = head;
        cout << "Current circle: ";
        do {
            cout << temp->personID << " -> ";
            temp = temp->next;
        } while (temp != head);

        cout << "(back to " << head->personID << ")" << endl;
    }

    // 2. Elimination Process and Display
    void runSimulation(int k) {
        if (head == NULL) {
            cout << "Circle not created yet." << endl;
            return;
        }

        if (k <= 0) {
            cout << "Step count k must be positive." << endl;
            return;
        }

        cout << "\nStarting Josephus elimination with step k = " << k << ":\n" << endl;

        PersonNode* curr = head;
        PersonNode* prev = NULL;

        // locate last node to initialize prev
        PersonNode* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        prev = tail;

        int stepRound = 1;
        cout << "Elimination Sequence:" << endl;

        // Loop until only one person remains
        while (curr->next != curr) {

            // count k steps
            for (int count = 1; count < k; count++) {
                prev = curr;
                curr = curr->next;
            }

            // eliminate the k-th person
            cout << "Round " << stepRound << ": Person " << curr->personID << " is eliminated." << endl;
            
            prev->next = curr->next;
            
            // free eliminated person node
            PersonNode* toDelete = curr;
            curr = curr->next;

            if (toDelete == head) {
                head = curr;
            }

            delete toDelete;
            stepRound++;
        }

        head = curr;

        // 3. Display Survivor
        cout << "\nSurvivor: Person ID " << head->personID << endl;
    }
};

int main() {
    cout << "Josephus Problem Simulation (Circular Linked List)" << endl;

    int N = 7;
    int k = 3;

    cout << "\nTest Case: N = " << N << " people, Step k = " << k << endl;

    JosephusCircle circle;
    circle.createCircle(N);
    circle.displayCircle();

    circle.runSimulation(k);

    return 0;
}

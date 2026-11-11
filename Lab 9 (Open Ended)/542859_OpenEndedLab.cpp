/*
 * Department of Computing - Data Structures and Algorithms
 * Open Ended Lab: Student Help Desk
 * Name: Aarish Muhammad
 * Reg No: 542859
 * Section: BSAI-2A
 * 
 * Design Choices & Rationale:
 * 1. Storage Structure (std::vector<Student>):
 *    We use std::vector to store student records dynamically. Unlike a fixed-size
 *    array, a vector grows dynamically as new students are admitted without
 *    requiring manual reallocation. It stores records contiguously in memory,
 *    providing cache locality, fast sequential iteration for display, and
 *    amortized O(1) push_back insertion time.
 * 
 * 2. Search History Tracking (std::stack<int>):
 *    We use std::stack to track the roll numbers of recently searched students.
 *    A stack adheres to Last-In, First-Out (LIFO) semantics, which perfectly matches
 *    the requirement to review and inspect the most recently searched student first.
 *    Popping from the stack retrieves and removes the most recent search entry
 *    while leaving the original student record intact in the storage vector.
 * 
 * Worst-Case Time Complexity Analysis:
 * 1. Adding a Student:
 *    - Duplicate Check: O(n) linear scan across existing student records.
 *    - Insertion: Amortized O(1) for std::vector push_back.
 *    - Overall Worst-Case Time Complexity: O(n).
 * 
 * 2. Searching for a Student by Roll Number:
 *    - Linear Search: O(n) to find the matching roll number in the vector.
 *    - History Push: O(1) to push the roll number onto the std::stack.
 *    - Overall Worst-Case Time Complexity: O(n).
 * 
 * 3. Displaying All Students:
 *    - Iterating through all n students in the vector: O(n).
 * 
 * 4. Viewing and Popping Recent Search History:
 *    - Stack top and pop: O(1).
 *    - Finding student details for the popped roll number: O(n) linear search.
 *    - Overall Worst-Case Time Complexity: O(n).
 */

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

// Student structure storing individual student records
struct Student {
    int id;
    string name;
    double marks;
};

// Function to add a new student after verifying roll number uniqueness
bool addStudent(vector<Student>& sv, int id, string name, double marks) {
    for (const auto& s : sv) {
        if (s.id == id) {
            cout << "\n[Error] Duplicate Roll Number " << id
                 << " detected! Registration rejected.\n";
            return false;
        }
    }
    sv.push_back({id, name, marks});
    cout << "\n[Success] Student added: Roll No " << id
         << " (" << name << ", Marks: " << fixed << setprecision(1) << marks << ")\n";
    return true;
}

// Function to search a student by roll number and log search in stack history
const Student* searchStudent(const vector<Student>& sv, stack<int>& history, int id) {
    for (const auto& s : sv) {
        if (s.id == id) {
            history.push(id);
            cout << "\n[Match Found] Student details:\n";
            cout << "  Roll No : " << s.id << "\n";
            cout << "  Name    : " << s.name << "\n";
            cout << "  Marks   : " << fixed << setprecision(1) << s.marks << "\n";
            cout << "-> Roll No " << id << " pushed to recent search history stack.\n";
            return &s;
        }
    }
    cout << "\n[Not Found] Student with Roll No " << id
         << " does not exist in records.\n";
    return nullptr;
}

// Function to display all registered students
void displayAll(const vector<Student>& sv) {
    if (sv.empty()) {
        cout << "\n[Notice] No student records available in the system.\n";
        return;
    }

    cout << "\n----------------------------------------\n";
    cout << left << setw(10) << "Roll No"
         << setw(20) << "Name"
         << setw(10) << "Marks" << "\n";
    cout << "----------------------------------------\n";
    for (const auto& s : sv) {
        cout << left << setw(10) << s.id
             << setw(20) << s.name
             << fixed << setprecision(1) << s.marks << "\n";
    }
    cout << "----------------------------------------\n";
    cout << "Total Students: " << sv.size() << "\n";
}

// Function to view and pop the most recent search history (LIFO stack behavior)
void viewAndPopRecentHistory(stack<int>& history, const vector<Student>& sv) {
    if (history.empty()) {
        cout << "\n[Notice] Search history stack is empty. No recent searches to display.\n";
        return;
    }

    int poppedId = history.top();
    history.pop();

    cout << "\n--- Recent Search History (LIFO) ---\n";
    cout << "Popped Roll No from stack: " << poppedId << "\n";

    // Lookup corresponding student details in the vector
    bool found = false;
    for (const auto& s : sv) {
        if (s.id == poppedId) {
            cout << "  Name  : " << s.name << "\n";
            cout << "  Marks : " << fixed << setprecision(1) << s.marks << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "  (Student record is no longer present in storage vector)\n";
    }
    cout << "Status: Student record remains safely intact in the storage vector.\n";
}

int main() {
    vector<Student> students;
    stack<int> searchHistory;
    int choice = 0;

    do {
        cout << "\n--- Student Help Desk Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student by Roll No\n";
        cout << "3. Display All Students\n";
        cout << "4. View & Pop Recent Search History\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";

        if (!(cin >> choice)) {
            break;
        }

        switch (choice) {
            case 1: {
                int id;
                string name;
                double marks;

                cout << "\nEnter Roll Number: ";
                if (!(cin >> id)) break;

                cout << "Enter Name: ";
                cin >> ws;
                getline(cin, name);

                cout << "Enter Marks: ";
                if (!(cin >> marks)) break;

                addStudent(students, id, name, marks);
                break;
            }
            case 2: {
                int id;
                cout << "\nEnter Roll Number to Search: ";
                if (!(cin >> id)) break;

                searchStudent(students, searchHistory, id);
                break;
            }
            case 3: {
                displayAll(students);
                break;
            }
            case 4: {
                viewAndPopRecentHistory(searchHistory, students);
                break;
            }
            case 5: {
                cout << "\nExiting Student Help Desk. Thank you!\n";
                break;
            }
            default: {
                cout << "\n[Error] Invalid choice! Please select between 1 and 5.\n";
                break;
            }
        }
    } while (choice != 5);

    return 0;
}

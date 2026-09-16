#include <iostream>

using namespace std;


// Lab 2 - Task 7: Dynamic Array Resizing Using Pointer Notation

int main() {
    int n = 0;

    // Input and validate input for n (range: 1 to 10)
    cout << "Enter the number of marks (1-10): ";
    while (!(cin >> n) || n < 1 || n > 10) {
        cout << "Invalid input. Please enter an integer between 1 and 10: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    // Allocate dynamic array for original n marks
    int* marks = new int[n];

    // Read n marks into the dynamic array using pointer notation
    cout << "Enter " << n << " mark(s): ";
    for (int i = 0; i < n; i++) {
        cin >> *(marks + i);
    }

    // Display original marks using pointer notation
    cout << "Original marks: ";
    for (int i = 0; i < n; i++) {
        cout << *(marks + i) << " ";
    }
    cout << endl;

    // Read one additional mark
    int newMark = 0;
    cout << "Enter additional mark: ";
    cin >> newMark;


    // Step 1: Allocate a second block of (n + 1) integers.
    //         Copy original n values into it using pointer notation.
    //         Store the new mark at the final position.

    int* newMarks = new int[n + 1];

    // Copy original n elements using pointer notation
    for (int i = 0; i < n; i++) {
        *(newMarks + i) = *(marks + i);
    }

    // Append the new mark at the final position
    *(newMarks + n) = newMark;


    // Step 2: Release the old block.
    //         Make the original pointer refer to the new block.
    //         Update the stored size, and display all values using pointer notation.
 
    delete[] marks;         // Release the old block of n integers
    marks = newMarks;       // Make original pointer refer to the new block
    newMarks = nullptr;     // Reset temporary pointer 
    n = n + 1;              // Update stored size

    // Display all n values using pointer notation
    cout << "Updated marks (" << n << " elements): ";
    for (int i = 0; i < n; i++) {
        cout << *(marks + i) << " ";
    }
    cout << endl;

    // Step 3: Release the final block exactly once and reset pointer.

    delete[] marks;
    marks = nullptr;

    return 0;
}

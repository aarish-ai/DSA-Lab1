#include <iostream>

using namespace std;


// Lab 2 - Task 8: Dynamic Memory Errors, Analysis, and Safe Management

// PART 2: Corrected Complete Program

int main() {
    // Step 1: Define the size of the array
    int n = 3;

    // Step 2: Dynamically allocate an array of 3 integers on the heap
    int* values = new int[n];

    // Step 3: Read exactly 3 integers using a correct loop bound (0 to n - 1)
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    // Step 4: Display all 3 integers properly from the allocated array
    cout << "The " << n << " integers entered are: ";
    for (int i = 0; i < n; i++) {
        cout << values[i] << (i + 1 < n ? " " : "");
    }
    cout << endl;

    // Step 5: Properly deallocate array memory using the array delete operator
    delete[] values;

    // Step 6: Reset the pointer to nullptr to eliminate the dangling pointer
    values = nullptr;

    // Confirmation demonstrating safe pointer state
    if (values == nullptr) {
        cout << "Memory successfully freed and pointer safely reset to nullptr." << endl;
    }

    return 0;
}

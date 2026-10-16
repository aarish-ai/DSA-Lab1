#include <iostream>

using namespace std;

// function to input student IDs
void inputIDs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

// linear search function checking elements one by one
int linearSearch(const int arr[], int n, int target) {
    // return immediately when target is found
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i; // returns first occurrence
        }
    }
    // return -1 if not found or array is empty
    return -1;
}

// display search result
void displayResult(int index, int target) {
    if (index != -1) {
        cout << "Target " << target << " -> Found at index " << index << endl;
    } else {
        cout << "Target " << target << " -> Not found (ID is not registered)" << endl;
    }
}

// helper to display array
void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    cout << "Task 1: Student ID Search Using Linear Search\n\n";

    // Test case 1: Target at beginning (Best Case)
    int arr1[] = {10, 20, 30, 40};
    int n1 = 4;
    cout << "Test Case 1:\nInput array: ";
    printArray(arr1, n1);
    cout << "\n";
    int idx1 = linearSearch(arr1, n1, 10);
    displayResult(idx1, 10);
    cout << endl;

    // Test case 2: Target in middle
    cout << "Test Case 2:\nInput array: ";
    printArray(arr1, n1);
    cout << "\n";
    int idx2 = linearSearch(arr1, n1, 30);
    displayResult(idx2, 30);
    cout << endl;

    // Test case 3: Target not present (Worst Case)
    cout << "Test Case 3:\nInput array: ";
    printArray(arr1, n1);
    cout << "\n";
    int idx3 = linearSearch(arr1, n1, 50);
    displayResult(idx3, 50);
    cout << endl;

    // Test case 4: Single element array
    int arr4[] = {7};
    int n4 = 1;
    cout << "Test Case 4:\nInput array: ";
    printArray(arr4, n4);
    cout << "\n";
    int idx4 = linearSearch(arr4, n4, 7);
    displayResult(idx4, 7);
    cout << endl;

    // Test case 5: Empty array
    int* arr5 = NULL;
    int n5 = 0;
    cout << "Test Case 5:\nInput array: ";
    printArray(arr5, n5);
    cout << "\n";
    int idx5 = linearSearch(arr5, n5, 5);
    displayResult(idx5, 5);
    cout << endl;

    return 0;
}

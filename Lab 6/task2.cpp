#include <iostream>

using namespace std;

// verify if registration IDs are in non-decreasing order
bool isSorted(const int arr[], int n) {
    if (n <= 1) return true;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// read sorted IDs
void inputSortedIDs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
}

// binary search implementation (iterative approach chosen for O(1) space)
int binarySearch(const int arr[], int low, int high, int target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid; // match found
        }
        else if (arr[mid] < target) {
            low = mid + 1; // search right half
        }
        else {
            high = mid - 1; // search left half
        }
    }
    return -1; // absent
}

// helper to display result
void displayResult(int index, int target) {
    if (index != -1) {
        cout << "Target " << target << " -> Found at index " << index << endl;
    } else {
        cout << "Target " << target << " -> Not found" << endl;
    }
}

void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    cout << "Task 2: Student Registration Search Using Binary Search\n\n";

    int arr[] = {10, 20, 30, 40, 50};
    int n = 5;

    if (!isSorted(arr, n)) {
        cout << "Error: Input array is not sorted! Binary search requires sorted data.\n";
        return 1;
    }

    // Test case 1: Target = 30 (Middle element -> Best Case)
    cout << "Test Case 1:\nSorted array: ";
    printArray(arr, n);
    cout << "\n";
    int idx1 = binarySearch(arr, 0, n - 1, 30);
    displayResult(idx1, 30);
    cout << endl;

    // Test case 2: Target = 10 (First element)
    cout << "Test Case 2:\nSorted array: ";
    printArray(arr, n);
    cout << "\n";
    int idx2 = binarySearch(arr, 0, n - 1, 10);
    displayResult(idx2, 10);
    cout << endl;

    // Test case 3: Target = 50 (Last element)
    cout << "Test Case 3:\nSorted array: ";
    printArray(arr, n);
    cout << "\n";
    int idx3 = binarySearch(arr, 0, n - 1, 50);
    displayResult(idx3, 50);
    cout << endl;

    // Test case 4: Target = 25 (Missing element)
    cout << "Test Case 4:\nSorted array: ";
    printArray(arr, n);
    cout << "\n";
    int idx4 = binarySearch(arr, 0, n - 1, 25);
    displayResult(idx4, 25);
    cout << endl;

    // Test case 5: Single element array [7], target 7
    int singleArr[] = {7};
    cout << "Test Case 5:\nSorted array: ";
    printArray(singleArr, 1);
    cout << "\n";
    int idx5 = binarySearch(singleArr, 0, 0, 7);
    displayResult(idx5, 7);
    cout << endl;

    // Test case 6: Empty array, target 5
    int* emptyArr = NULL;
    cout << "Test Case 6:\nSorted array: ";
    printArray(emptyArr, 0);
    cout << "\n";
    int idx6 = binarySearch(emptyArr, 0, -1, 5);
    displayResult(idx6, 5);
    cout << endl;

    return 0;
}

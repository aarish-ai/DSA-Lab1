#include <iostream>

using namespace std;

// display array contents
void displayArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

// merges two sorted subarrays: arr[left..mid] and arr[mid+1..right]
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // dynamically allocate temporary arrays using raw pointers
    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    // copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    // merge the two sorted halves
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // copy remaining elements of leftArr if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // copy remaining elements of rightArr if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    // release dynamically allocated memory
    delete[] leftArr;
    delete[] rightArr;
}

// recursive mergeSort
void mergeSort(int arr[], int left, int right) {
    // base case: 0 or 1 element
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    // recursively divide and sort halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // merge sorted halves
    merge(arr, left, mid, right);
}

void runTestCase(int arr[], int n, const char* testLabel) {
    cout << testLabel << ":\n";
    cout << "Input:  ";
    displayArray(arr, n);
    cout << "\n";

    if (n > 1) {
        mergeSort(arr, 0, n - 1);
    }

    cout << "Output: ";
    displayArray(arr, n);
    cout << "\n\n";
}

int main() {
    cout << "Task 3: Sort Student Marks Using Merge Sort\n\n";

    // Test case 1: Standard unsorted marks
    int t1[] = {45, 12, 78, 33, 20, 60};
    runTestCase(t1, 6, "Test Case 1 (Standard Marks)");

    // Test case 2: Already sorted
    int t2[] = {1, 2, 3, 4};
    runTestCase(t2, 4, "Test Case 2 (Already Sorted)");

    // Test case 3: Reverse sorted
    int t3[] = {9, 7, 5, 3, 1};
    runTestCase(t3, 5, "Test Case 3 (Reverse Sorted)");

    // Test case 4: Array with duplicates
    int t4[] = {5, 2, 5, 1, 2};
    runTestCase(t4, 5, "Test Case 4 (Duplicates)");

    // Test case 5: Single element
    int t5[] = {8};
    runTestCase(t5, 1, "Test Case 5 (Single Element)");

    // Test case 6: Empty array
    int* t6 = NULL;
    runTestCase(t6, 0, "Test Case 6 (Empty Array)");

    return 0;
}

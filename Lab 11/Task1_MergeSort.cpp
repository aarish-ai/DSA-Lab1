#include <iostream>
using namespace std;

// helper to print array elements
void printArr(int arr[], int n) {
    if (n <= 0) {
        cout << "[] (emty)";
        return;
    }
    cout << "{ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << " }";
}

// merges two sorted subarrays arr[low..mid] and arr[mid+1..high]
void merge(int arr[], int low, int mid, int high, int totalSize, bool showTrace) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = low;

    // <= keeps equal elements in original order (stable)
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // copy leftovers if any
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    delete[] L;
    delete[] R;

    if (showTrace) {
        cout << "Merged [" << low << ".." << high << "] -> ";
        printArr(arr, totalSize);
        cout << "\n";
    }
}

void mergeSort(int arr[], int low, int high, int totalSize, bool showTrace) {
    if (low >= high) {
        return; // base case: 0 or 1 element
    }

    int mid = low + (high - low) / 2;
    mergeSort(arr, low, mid, totalSize, showTrace);
    mergeSort(arr, mid + 1, high, totalSize, showTrace);
    merge(arr, low, mid, high, totalSize, showTrace);
}

void runTest(const char* label, int input[], int n, bool trace) {
    int* arr = (n > 0) ? new int[n] : nullptr;
    for (int i = 0; i < n; i++) arr[i] = input[i];

    cout << label << "\n";
    cout << "Before: ";
    printArr(arr, n);
    cout << "\n";

    if (n > 0) {
        mergeSort(arr, 0, n - 1, n, trace);
    } else {
        mergeSort(arr, 0, -1, 0, trace);
    }

    cout << "After:  ";
    printArr(arr, n);
    cout << "\n\n";

    if (arr != nullptr) delete[] arr;
}

int main() {
    cout << "Task 1: Merge Sort\n\n";

    int a1[] = {35, 12, 43, 8, 51, 27, 19};
    runTest("Test 1 - Main Trace Array (n = 7):", a1, 7, true);

    int a2[] = {1, 2, 4, 5, 8};
    runTest("Test 2 - Already Sorted:", a2, 5, false);

    int a3[] = {8, 5, 4, 2, 1};
    runTest("Test 3 - Reverse Sorted:", a3, 5, false);

    int a4[] = {5, 2, 5, 1, 2};
    runTest("Test 4 - Repeated Values:", a4, 5, false);

    int a5[] = {42};
    runTest("Test 5 - Single Element (n = 1):", a5, 1, false);

    int dummy[1] = {0};
    runTest("Test 6 - Empty Array (n = 0):", dummy, 0, false);

    return 0;
}

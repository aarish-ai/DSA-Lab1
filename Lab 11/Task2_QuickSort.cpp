#include <iostream>
using namespace std;

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

void swapVals(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// Lomuto partition using last element as pivot
int partition(int arr[], int low, int high, int totalSize, bool showTrace, long long& comps) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        comps++; // counting element comparsion arr[j] <= pivot
        if (arr[j] <= pivot) {
            i++;
            swapVals(arr[i], arr[j]);
        }
    }

    swapVals(arr[i + 1], arr[high]);
    int pi = i + 1;

    if (showTrace) {
        cout << "Partition [" << low << ".." << high << "] | pivot = " << pivot
             << " | pi = " << pi << " | arr = ";
        printArr(arr, totalSize);
        cout << "\n";
    }

    return pi;
}

void quickSort(int arr[], int low, int high, int totalSize, bool showTrace, long long& comps) {
    if (low < high) {
        int pi = partition(arr, low, high, totalSize, showTrace, comps);
        quickSort(arr, low, pi - 1, totalSize, showTrace, comps);
        quickSort(arr, pi + 1, high, totalSize, showTrace, comps);
    }
}

void runQuickTest(const char* label, int input[], int n, bool showTrace) {
    int* arr = (n > 0) ? new int[n] : nullptr;
    for (int i = 0; i < n; i++) arr[i] = input[i];

    long long comps = 0;
    cout << label << "\n";
    cout << "Before: ";
    printArr(arr, n);
    cout << "\n";

    if (n > 0) {
        quickSort(arr, 0, n - 1, n, showTrace, comps);
    } else {
        quickSort(arr, 0, -1, 0, showTrace, comps);
    }

    cout << "After:  ";
    printArr(arr, n);
    cout << " | Comparisons: " << comps << "\n\n";

    if (arr != nullptr) delete[] arr;
}

int main() {
    cout << "Task 2: Quick Sort (Last Element Pivot)\n\n";

    int t1[] = {2, 1, 5, 4, 6, 3};
    runQuickTest("Trace 1 - {2, 1, 5, 4, 6, 3}:", t1, 6, true);

    int t2[] = {35, 12, 43, 8, 51, 27, 19};
    runQuickTest("Trace 2 - {35, 12, 43, 8, 51, 27, 19}:", t2, 7, true);

    int c1[] = {5, 1, 4, 2, 8};
    runQuickTest("Case 1 - Random Order {5, 1, 4, 2, 8}:", c1, 5, false);

    int c2[] = {1, 2, 4, 5, 8};
    runQuickTest("Case 2 - Already Sorted {1, 2, 4, 5, 8}:", c2, 5, false);

    int c3[] = {8, 5, 4, 2, 1};
    runQuickTest("Case 3 - Reverse Sorted {8, 5, 4, 2, 1}:", c3, 5, false);

    int c4[] = {7, 7, 7, 7, 7};
    runQuickTest("Case 4 - Repeated Values {7, 7, 7, 7, 7}:", c4, 5, false);

    int c5[] = {9};
    runQuickTest("Case 5 - Single Element (n = 1):", c5, 1, false);

    int dummy[1] = {0};
    runQuickTest("Case 6 - Empty Array (n = 0):", dummy, 0, false);

    return 0;
}

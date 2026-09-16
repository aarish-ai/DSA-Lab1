#include <iostream>

using namespace std;

// Lab 2 - Task 3: Array Traversal Using Pointer Variable Only

int main() {
    int list[5] = {3, 6, 9, 12, 15};
    int *pArr = list;

    // Traverse and print all elements using only pointer variable pArr
    for (int i = 0; i < 5; i++) {
        cout << *(pArr + i) << " ";
    }
    cout << endl;

    return 0;
}

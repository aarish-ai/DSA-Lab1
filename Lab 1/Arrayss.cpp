#include <iostream>
#include <vector>
using namespace std;

vector<int> findAllIndices(const vector<int>& arr, int key) {
    vector<int> indices; // the vector array of all the indices

    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == key) {
            indices.push_back(i); // wherever the key is found, that index is appended to the array
        }
    }

    return indices;
}

int main() {
    // Test Case 1: Multiple occurrences
    vector<int> arr1 = {1, 2, 3, 2, 4, 2};
    int key1 = 2;

    vector<int> result1 = findAllIndices(arr1, key1);

    cout << "Test 1: ";
    for (int index : result1) {
        cout << index << " ";
    }
    cout << endl;

    // Test Case 2: Key not present
    vector<int> arr2 = {1, 3, 5, 7};
    int key2 = 2;

    vector<int> result2 = findAllIndices(arr2, key2);

    cout << "Test 2: ";
    for (int index : result2) {
        cout << index << " ";
    }
    cout << endl;

    // Test Case 3: Empty array
    vector<int> arr3;
    int key3 = 5;

    vector<int> result3 = findAllIndices(arr3, key3);

    cout << "Test 3: ";
    for (int index : result3) {
        cout << index << " ";
    }
    cout << endl;

}
#include <iostream>

using namespace std;

// MaxHeap class implementation using dynamic array
class MaxHeap {
private:
    int* arr;       // dynamic array pointer
    int sz;         // current number of elements
    int cap;        // total allocated capacity

    // double the array capacity when full - takes O(n) time
    void resize() {
        int new_cap = cap * 2;
        int* new_arr = new int[new_cap];
        
        // copy old elements to new buffer
        for (int i = 0; i < sz; i++) {
            new_arr[i] = arr[i];
        }
        
        delete[] arr;
        arr = new_arr;
        cap = new_cap;
    }

    // sift down helper for heap sort - takes O(log n) time
    void siftDown(int idx, int heapBound) {
        int cur = idx;
        while (cur < heapBound) {
            int l_child = 2 * cur + 1;
            int r_child = 2 * cur + 2;
            int big_idx = cur;

            if (l_child < heapBound && arr[l_child] > arr[big_idx]) {
                big_idx = l_child;
            }
            if (r_child < heapBound && arr[r_child] > arr[big_idx]) {
                big_idx = r_child;
            }

            // if largest is not current node, swap and keep sifting down
            if (big_idx != cur) {
                int temp_val = arr[cur];
                arr[cur] = arr[big_idx];
                arr[big_idx] = temp_val;
                cur = big_idx;
            } else {
                break;
            }
        }
    }

public:
    // constructor to allocate initial array - takes O(1) time
    MaxHeap(int initialCap = 10) {
        sz = 0;
        cap = initialCap;
        arr = new int[cap];
    }

    // destructor to free dynamically allocated memory - takes O(1) time
    ~MaxHeap() {
        delete[] arr;
        arr = nullptr;
    }

    // insert value into max heap with sift up and count swaps - takes O(log n) time
    void insert(int value) {
        if (sz == cap) {
            resize();
        }

        // place new value at the end of the heap
        arr[sz] = value;
        int cur_idx = sz;
        sz++;

        int swp_cnt = 0;

        // sift up while element is greater than its parent
        while (cur_idx > 0) {
            int par_idx = (cur_idx - 1) / 2;
            // cheking if parent is smaller than child
            if (arr[cur_idx] > arr[par_idx]) {
                int temp_val = arr[cur_idx];
                arr[cur_idx] = arr[par_idx];
                arr[par_idx] = temp_val;
                swp_cnt++;
                cur_idx = par_idx;
            } else {
                break; // heap condition satisfied
            }
        }

        // print table row matching expected output
        cout << value << "\t" << swp_cnt << "\t";
        for (int i = 0; i < sz; i++) {
            cout << arr[i] << (i + 1 == sz ? "" : " ");
        }
        cout << "\n";
    }

    // print heap elements - takes O(n) time
    void printHeap() const {
        for (int i = 0; i < sz; i++) {
            cout << arr[i] << (i + 1 == sz ? "" : " ");
        }
        cout << "\n";
    }

    // in-place heap sort using sift down - takes O(n log n) time
    void heapSort() {
        // repeatedly extract max root to the back of array
        for (int i = sz - 1; i > 0; i--) {
            // swaped root with current end element
            int temp_val = arr[0];
            arr[0] = arr[i];
            arr[i] = temp_val;

            // restore max heap property on remaining sub-heap of size i
            siftDown(0, i);
        }
    }

    // print sorted elements - takes O(n) time
    void printSorted() const {
        cout << "Sorted output: ";
        for (int i = 0; i < sz; i++) {
            cout << arr[i] << (i + 1 == sz ? "" : " ");
        }
        cout << "\n";
    }
};

int main() {
    MaxHeap myHeap;

    cout << "Insert\tSwaps\tHeap after insertion\n";

    int sample_input[] = {25, 40, 15, 60, 35, 10, 70, 50};
    int n = sizeof(sample_input) / sizeof(sample_input[0]);

    for (int i = 0; i < n; i++) {
        myHeap.insert(sample_input[i]);
    }

    // perform in-place heap sort
    myHeap.heapSort();

    // print sorted array
    myHeap.printSorted();

    return 0;
}
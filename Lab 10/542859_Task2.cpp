#include <iostream>

using namespace std;

// MaxHeap class implementation using dynamic array
class MaxHeap {
private:
    int* arr;       // dynamic array pointer
    int sz;         // current element count
    int cap;        // allocated capacity

    // double the array capacity when full - takes O(n) time
    void resize() {
        int new_cap = cap * 2;
        int* new_arr = new int[new_cap];

        // copying elements to new allocated memory
        for (int i = 0; i < sz; i++) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
        cap = new_cap;
    }

    // sift up helper when element inserted - takes O(log n) time
    void siftUp(int idx) {
        int cur_idx = idx;
        while (cur_idx > 0) {
            int par_idx = (cur_idx - 1) / 2;
            // if child is greater than parent, swap them
            if (arr[cur_idx] > arr[par_idx]) {
                int temp_val = arr[cur_idx];
                arr[cur_idx] = arr[par_idx];
                arr[par_idx] = temp_val;
                cur_idx = par_idx;
            } else {
                break;
            }
        }
    }

    // sift down helper after root deletion - takes O(log n) time
    void siftDown(int idx) {
        int cur = idx;
        while (cur < sz) {
            int l_child = 2 * cur + 1;
            int r_child = 2 * cur + 2;
            int max_idx = cur;

            if (l_child < sz && arr[l_child] > arr[max_idx]) {
                max_idx = l_child;
            }
            if (r_child < sz && arr[r_child] > arr[max_idx]) {
                max_idx = r_child;
            }

            if (max_idx != cur) {
                int temp_val = arr[cur];
                arr[cur] = arr[max_idx];
                arr[max_idx] = temp_val;
                cur = max_idx;
            } else {
                break;
            }
        }
    }

public:
    // constructor allocating default capacity - takes O(1) time
    MaxHeap(int initialCap = 10) {
        sz = 0;
        cap = initialCap;
        arr = new int[cap];
    }

    // destructor to free heap memory - takes O(1) time
    ~MaxHeap() {
        delete[] arr;
        arr = nullptr;
    }

    // push new value into max heap - takes O(log n) time
    void push(int val) {
        if (sz == cap) {
            resize();
        }
        arr[sz] = val;
        sz++;
        siftUp(sz - 1);
    }

    // extract and return maximum root value - takes O(log n) time
    int pop() {
        if (sz == 0) {
            return -1; // heap is empty
        }
        int max_val = arr[0];
        arr[0] = arr[sz - 1];
        sz--;
        siftDown(0);
        return max_val;
    }

    // return maximum element without removing - takes O(1) time
    int peek() const {
        if (sz == 0) return -1;
        return arr[0];
    }

    // return current number of elements - takes O(1) time
    int getSize() const {
        return sz;
    }

    // check if heap has no elements - takes O(1) time
    bool isEmpty() const {
        return sz == 0;
    }
};

// MinHeap class implementation using dynamic array
class MinHeap {
private:
    int* arr;       // dynamic array pointer
    int sz;         // current element count
    int cap;        // allocated capacity

    // double the array capacity when full - takes O(n) time
    void resize() {
        int new_cap = cap * 2;
        int* new_arr = new int[new_cap];

        // copying elements over
        for (int i = 0; i < sz; i++) {
            new_arr[i] = arr[i];
        }

        delete[] arr;
        arr = new_arr;
        cap = new_cap;
    }

    // sift up helper for min heap - takes O(log n) time
    void siftUp(int idx) {
        int cur_idx = idx;
        while (cur_idx > 0) {
            int par_idx = (cur_idx - 1) / 2;
            // if child is smaller than parent, swap
            if (arr[cur_idx] < arr[par_idx]) {
                int temp_val = arr[cur_idx];
                arr[cur_idx] = arr[par_idx];
                arr[par_idx] = temp_val;
                cur_idx = par_idx;
            } else {
                break;
            }
        }
    }

    // sift down helper for min heap - takes O(log n) time
    void siftDown(int idx) {
        int cur = idx;
        while (cur < sz) {
            int l_child = 2 * cur + 1;
            int r_child = 2 * cur + 2;
            int min_idx = cur;

            if (l_child < sz && arr[l_child] < arr[min_idx]) {
                min_idx = l_child;
            }
            if (r_child < sz && arr[r_child] < arr[min_idx]) {
                min_idx = r_child;
            }

            if (min_idx != cur) {
                int temp_val = arr[cur];
                arr[cur] = arr[min_idx];
                arr[min_idx] = temp_val;
                cur = min_idx;
            } else {
                break;
            }
        }
    }

public:
    // constructor allocating default capacity - takes O(1) time
    MinHeap(int initialCap = 10) {
        sz = 0;
        cap = initialCap;
        arr = new int[cap];
    }

    // destructor to free memory - takes O(1) time
    ~MinHeap() {
        delete[] arr;
        arr = nullptr;
    }

    // push new value into min heap - takes O(log n) time
    void push(int val) {
        if (sz == cap) {
            resize();
        }
        arr[sz] = val;
        sz++;
        siftUp(sz - 1);
    }

    // extract and return minimum root value - takes O(log n) time
    int pop() {
        if (sz == 0) {
            return -1; // heap is empty
        }
        int min_val = arr[0];
        arr[0] = arr[sz - 1];
        sz--;
        siftDown(0);
        return min_val;
    }

    // return minimum element without removing - takes O(1) time
    int peek() const {
        if (sz == 0) return -1;
        return arr[0];
    }

    // return current count of elements - takes O(1) time
    int getSize() const {
        return sz;
    }

    // check if min heap is empty - takes O(1) time
    bool isEmpty() const {
        return sz == 0;
    }
};

// Hospital ER Wait-Time Monitor using two heaps
class ERWaitMonitor {
private:
    MaxHeap lower_half;     // keeps smaller half of wait times
    MinHeap upper_half;     // keeps larger half of wait times
    double alert_threshold; // threshold in minutes (35)

public:
    // constructor initializing alert threshold - takes O(1) time
    ERWaitMonitor(double threshold = 35.0) {
        alert_threshold = threshold;
    }

    // add new patient waiting time and rebalance - takes O(log n) time
    void addWait(int x) {
        // insert into correct heap
        if (lower_half.isEmpty() || x <= lower_half.peek()) {
            lower_half.push(x);
        } else {
            upper_half.push(x);
        }

        // rebalncing heaps so lower_half has equal or 1 more element
        if (lower_half.getSize() > upper_half.getSize() + 1) {
            int top_val = lower_half.pop();
            upper_half.push(top_val);
        } else if (lower_half.getSize() < upper_half.getSize()) {
            int top_val = upper_half.pop();
            lower_half.push(top_val);
        }
    }

    // calculate current median wait time - takes O(1) time
    double getMedian() const {
        if (lower_half.getSize() > upper_half.getSize()) {
            return (double)lower_half.peek();
        } else {
            return (lower_half.peek() + upper_half.peek()) / 2.0;
        }
    }

    // process an incoming arrival and print status row - takes O(log n) time
    void processArrival(int arrival_num, int wait_time) {
        addWait(wait_time);

        // retrieve roots for table display
        int low_root = lower_half.peek();
        bool has_high = !upper_half.isEmpty();
        int high_root = has_high ? upper_half.peek() : -1;

        double med_val = getMedian();

        cout << arrival_num << "\t" << wait_time << "\t" << low_root << "\t";
        if (has_high) {
            cout << high_root << "\t";
        } else {
            cout << "none\t";
        }

        // formatting median: whole numbers without decimal, fractions with .5
        if (med_val == (int)med_val) {
            cout << (int)med_val << "\t";
        } else {
            cout << med_val << "\t";
        }

        // cheking if median exceeds threshold
        if (med_val > alert_threshold) {
            cout << "ALERT\n";
        } else {
            cout << "Normal\n";
        }
    }
};

int main() {
    ERWaitMonitor monitor(35.0);

    cout << "Arrival\tWait\tMax heap root\tMin heap root\tMedian\tStatus\n";

    int sample_input[] = {45, 20, 60, 15, 30, 90, 10, 55};
    int total_arrivals = sizeof(sample_input) / sizeof(sample_input[0]);

    for (int i = 0; i < total_arrivals; i++) {
        monitor.processArrival(i + 1, sample_input[i]);
    }

    return 0;
}
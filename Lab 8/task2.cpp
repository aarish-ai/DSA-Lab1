// DSA Lab 08 - Task 2: Merging K Sorted Linked Lists using Binary Min-Heap

#include <iostream>

using namespace std;

// Singly linked list node
struct ListNode {
    int val;            // Data value stored in the node
    ListNode* next;     // Pointer to next node
};

// Min-heap storing pointers to ListNode
struct MinHeap {
    ListNode** heapArr; // Dynamic array of pointers to ListNode
    int capacity;       // Maximum capacity of the heap (k)
    int size;           // Current number of active list heads in the heap
};

// Helper function to create a new linked list node
ListNode* createListNode(int val) {
    ListNode* newNode = new ListNode();
    newNode->val = val;
    newNode->next = nullptr;
    return newNode;
}

// Helper function to create and initialize a MinHeap
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = new MinHeap();
    heap->capacity = capacity;
    heap->size = 0;
    heap->heapArr = new ListNode*[capacity];
    return heap;
}

// Helper function to swap two ListNode pointers in heap array
void swapNodes(ListNode*& a, ListNode*& b) {
    ListNode* temp = a;
    a = b;
    b = temp;
}

// Min-heapify helper based on ListNode value
void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int leftChild = 2 * idx + 1;
    int rightChild = 2 * idx + 2;

    // Check if left child has a smaller node value
    if (leftChild < heap->size && heap->heapArr[leftChild]->val < heap->heapArr[smallest]->val) {
        smallest = leftChild;
    }

    // Check if right child has a smaller node value
    if (rightChild < heap->size && heap->heapArr[rightChild]->val < heap->heapArr[smallest]->val) {
        smallest = rightChild;
    }

    // If smallest is not current index, swap and recursively heapify subtree
    if (smallest != idx) {
        swapNodes(heap->heapArr[idx], heap->heapArr[smallest]);
        minHeapify(heap, smallest);
    }
}

// Extract minimum node pointer from the heap
ListNode* extractMin(MinHeap* heap) {
    if (heap->size <= 0) {
        return nullptr;
    }

    // The root of the min-heap holds the smallest value node
    ListNode* minNode = heap->heapArr[0];

    // Replace root with the last node in heap array
    heap->heapArr[0] = heap->heapArr[heap->size - 1];
    heap->size--;

    // Restore min-heap ordering starting from root
    minHeapify(heap, 0);

    return minNode;
}

// Insert ListNode pointer into min-heap
void insertMinHeap(MinHeap* heap, ListNode* node) {
    if (heap->size == heap->capacity) {
        cout << "Heap overflow: cannot insert more nodes." << endl;
        return;
    }

    // Place new node pointer at the end of the heap
    int currIdx = heap->size;
    heap->heapArr[currIdx] = node;
    heap->size++;

    // Bubble up while current node's value is smaller than its parent's value
    while (currIdx > 0) {
        int parentIdx = (currIdx - 1) / 2;
        if (heap->heapArr[currIdx]->val < heap->heapArr[parentIdx]->val) {
            swapNodes(heap->heapArr[currIdx], heap->heapArr[parentIdx]);
            currIdx = parentIdx;
        } else {
            break;
        }
    }
}

// Merge k sorted linked lists using a min-heap
ListNode* mergeKLists(ListNode* lists[], int k) {
    if (k <= 0) {
        return nullptr;
    }

    // Step 1: Create a min heap of capacity k
    MinHeap* heap = createMinHeap(k);

    // Step 2: Insert the head of each non-empty linked list into the min-heap
    for (int i = 0; i < k; i++) {
        if (lists[i] != nullptr) {
            insertMinHeap(heap, lists[i]);
        }
    }

    // Dummy head to simplify list construction
    ListNode dummy;
    dummy.next = nullptr;
    ListNode* tail = &dummy;

    // Step 3: Repeatedly extract the minimum node and push its next node into heap
    while (heap->size > 0) {
        ListNode* minNode = extractMin(heap);

        // Append the minimum node to our merged list
        tail->next = minNode;
        tail = minNode;

        // If this node has a subsequent node in its original list, insert it into heap
        if (minNode->next != nullptr) {
            insertMinHeap(heap, minNode->next);
        }
    }

    // Terminate the merged linked list
    tail->next = nullptr;

    // Clean up heap structure memory
    delete[] heap->heapArr;
    delete heap;

    return dummy.next;
}

// Helper to build a linked list from an array
ListNode* buildListFromArray(const int arr[], int size) {
    if (size <= 0) {
        return nullptr;
    }

    ListNode* head = createListNode(arr[0]);
    ListNode* curr = head;
    for (int i = 1; i < size; i++) {
        curr->next = createListNode(arr[i]);
        curr = curr->next;
    }
    return head;
}

// Helper to display linked list nodes
void printList(ListNode* head) {
    if (head == nullptr) {
        cout << "[Empty List] NULL" << endl;
        return;
    }

    ListNode* curr = head;
    while (curr != nullptr) {
        cout << curr->val << " -> ";
        curr = curr->next;
    }
    cout << "NULL" << endl;
}

// Helper: freeList
// Deallocates all nodes of a linked list
void freeList(ListNode* head) {
    ListNode* curr = head;
    while (curr != nullptr) {
        ListNode* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
}

// Main demonstration for Task 2
int main() {
    cout << "Task 2: Merging K Sorted Lists using Min-Heap\n\n";

    const int k = 4;
    ListNode* lists[k];

    // List 0: 1 -> 4 -> 7
    int arr0[] = {1, 4, 7};
    lists[0] = buildListFromArray(arr0, 3);

    // List 1: 2 -> 5 -> 8 -> 12
    int arr1[] = {2, 5, 8, 12};
    lists[1] = buildListFromArray(arr1, 4);

    // List 2: Empty list (to demonstrate edge case robustness)
    lists[2] = nullptr;

    // List 3: 0 -> 3 -> 6 -> 9
    int arr3[] = {0, 3, 6, 9};
    lists[3] = buildListFromArray(arr3, 4);

    cout << "Input " << k << " Sorted Linked Lists:" << endl;
    for (int i = 0; i < k; i++) {
        cout << "  List " << i << ": ";
        printList(lists[i]);
    }
    cout << endl;

    cout << "Merging all " << k << " sorted lists using Binary Min-Heap..." << endl;
    ListNode* mergedHead = mergeKLists(lists, k);
    cout << "Merge operation complete!" << endl << endl;

    cout << "Final Merged Sorted Linked List:" << endl;
    cout << "  ";
    printList(mergedHead);
    cout << endl;

    // Free all allocated nodes of the merged linked list
    freeList(mergedHead);
    cout << "Memory successfully freed. Task 2 completed." << endl;

    return 0;
}

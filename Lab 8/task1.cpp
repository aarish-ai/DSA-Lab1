// DSA Lab 08 - Task 1: Huffman Tree Construction and Preorder Traversal using Binary Min-Heap

#include <iostream>

using namespace std;

// Huffman tree node structure
struct HuffmanNode {
    char data;              // Character stored (or '$' for internal nodes)
    int freq;               // Frequency of occurrence
    HuffmanNode* left;      // Pointer to left child
    HuffmanNode* right;     // Pointer to right child
};

// Min-heap storing pointers to HuffmanNode
struct MinHeap {
    HuffmanNode** heapArr;  // Dynamic array of pointers to HuffmanNode
    int capacity;           // Maximum capacity of the heap
    int size;               // Current number of elements inside the heap
};

// Helper function to create a new Huffman Tree node
HuffmanNode* createNode(char data, int freq) {
    HuffmanNode* newNode = new HuffmanNode();
    newNode->data = data;
    newNode->freq = freq;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Helper function to create and initialize a MinHeap
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = new MinHeap();
    heap->capacity = capacity;
    heap->size = 0;
    heap->heapArr = new HuffmanNode*[capacity];
    return heap;
}

// Helper function to swap two HuffmanNode pointers
void swapNodes(HuffmanNode*& a, HuffmanNode*& b) {
    HuffmanNode* temp = a;
    a = b;
    b = temp;
}

// Min-heapify helper to maintain heap property
void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int leftChild = 2 * idx + 1;
    int rightChild = 2 * idx + 2;

    // Check if left child exists and has smaller frequency than current smallest
    if (leftChild < heap->size && heap->heapArr[leftChild]->freq < heap->heapArr[smallest]->freq) {
        smallest = leftChild;
    }

    // Check if right child exists and has smaller frequency than current smallest
    if (rightChild < heap->size && heap->heapArr[rightChild]->freq < heap->heapArr[smallest]->freq) {
        smallest = rightChild;
    }

    // If smallest is not current root, swap and recursively heapify affected subtree
    if (smallest != idx) {
        swapNodes(heap->heapArr[idx], heap->heapArr[smallest]);
        minHeapify(heap, smallest);
    }
}

// Extract minimum frequency node from the heap
HuffmanNode* extractMin(MinHeap* heap) {
    if (heap->size <= 0) {
        return nullptr;
    }

    // The root of the heap always holds the minimum element
    HuffmanNode* minNode = heap->heapArr[0];

    // Replace root with the last element in the heap
    heap->heapArr[0] = heap->heapArr[heap->size - 1];
    heap->size--;

    // Restore min-heap order starting from root
    minHeapify(heap, 0);

    return minNode;
}

// Insert node into min-heap
void insertMinHeap(MinHeap* heap, HuffmanNode* node) {
    if (heap->size == heap->capacity) {
        cout << "Heap overflow: cannot insert more nodes." << endl;
        return;
    }

    // Place the new node at the end of the heap array
    int currIdx = heap->size;
    heap->heapArr[currIdx] = node;
    heap->size++;

    // Bubble up while parent frequency is greater than current node frequency
    while (currIdx > 0) {
        int parentIdx = (currIdx - 1) / 2;
        if (heap->heapArr[currIdx]->freq < heap->heapArr[parentIdx]->freq) {
            swapNodes(heap->heapArr[currIdx], heap->heapArr[parentIdx]);
            currIdx = parentIdx;
        } else {
            break;
        }
    }
}

// Build Huffman Tree using the min-heap
HuffmanNode* buildHuffmanTree(const char characters[], const int frequencies[], int size) {
    // Step 1: Create a min heap of capacity equal to size
    MinHeap* heap = createMinHeap(size);

    // Step 2: Create leaf nodes for each character and insert into the heap
    for (int i = 0; i < size; i++) {
        HuffmanNode* leaf = createNode(characters[i], frequencies[i]);
        insertMinHeap(heap, leaf);
    }

    // Step 3: Iterate until the heap contains only one node (the root)
    while (heap->size > 1) {
        // Extract the two lowest frequency nodes
        HuffmanNode* leftChild = extractMin(heap);
        HuffmanNode* rightChild = extractMin(heap);

        // Create an internal node with frequency = sum of both frequencies
        // Use '$' as a marker character for internal nodes
        HuffmanNode* internalNode = createNode('$', leftChild->freq + rightChild->freq);
        internalNode->left = leftChild;
        internalNode->right = rightChild;

        // Insert the combined internal node back into min-heap
        insertMinHeap(heap, internalNode);
    }

    // Step 4: The last remaining node is the root of the complete Huffman tree
    HuffmanNode* root = extractMin(heap);

    // Clean up heap structure memory (the tree nodes remain preserved)
    delete[] heap->heapArr;
    delete heap;

    return root;
}

// Preorder traversal to print Huffman codes (0 for left, 1 for right)
void printPreorderCodes(HuffmanNode* root, char code[], int depth) {
    if (root == nullptr) {
        return;
    }

    // 1. Visit Root Node
    if (root->left == nullptr && root->right == nullptr) {
        // Leaf node reached: terminate code string and print character info
        code[depth] = '\0';
        cout << "  [Leaf Node] Character: '" << root->data
             << "' | Frequency: " << root->freq
             << " | Huffman Code: " << code << endl;
    } else {
        // Internal node
        cout << "  [Internal Node] Frequency Sum: " << root->freq << endl;
    }

    // 2. Traverse Left Subtree (append '0')
    if (root->left != nullptr) {
        code[depth] = '0';
        printPreorderCodes(root->left, code, depth + 1);
    }

    // 3. Traverse Right Subtree (append '1')
    if (root->right != nullptr) {
        code[depth] = '1';
        printPreorderCodes(root->right, code, depth + 1);
    }
}

// Function to clean up all allocated memory of the Huffman Tree
void freeHuffmanTree(HuffmanNode* root) {
    if (root == nullptr) {
        return;
    }
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

// Main demonstration for Task 1
int main() {
    cout << "Task 1: Huffman Coding using Binary Min-Heap\n\n";

    // Sample distinct characters and their corresponding frequencies
    const int N = 6;
    char characters[N] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int frequencies[N] = {5, 9, 12, 13, 16, 45};

    cout << "Input Characters and Frequencies:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "  Character '" << characters[i] << "' -> Frequency: " << frequencies[i] << endl;
    }
    cout << endl;

    cout << "Building Huffman Tree using Binary Min-Heap..." << endl;
    HuffmanNode* root = buildHuffmanTree(characters, frequencies, N);
    cout << "Huffman Tree built successfully!" << endl << endl;

    cout << "Preorder Traversal of Huffman Tree and Generated Codes:" << endl;
    char codeBuffer[100]; // Buffer to store binary path codes during traversal
    printPreorderCodes(root, codeBuffer, 0);
    cout << endl;

    // Free tree memory
    freeHuffmanTree(root);
    cout << "Memory successfully freed. Task 1 completed." << endl;

    return 0;
}

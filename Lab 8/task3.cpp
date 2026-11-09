// DSA Lab 08 - Task 3: AVL Tree Implementation for Top K Elements, Insert, Delete, and Query

#include <iostream>

using namespace std;

// AVL Tree node structure
struct AVLNode {
    int key;            // Key / data value
    int height;         // Height of the node in the AVL tree
    AVLNode* left;      // Pointer to left child
    AVLNode* right;     // Pointer to right child
};

// Query criteria for Top K elements
enum Criterion {
    CRITERION_MAX = 1,  // Top k maximum (largest) elements
    CRITERION_MIN = 2,  // Top k minimum (smallest) elements
    CRITERION_SUM = 3   // Top k largest elements along with their total sum
};

// Helper: return the maximum of two integers
int getMax(int a, int b) {
    return (a > b) ? a : b;
}

// Helper: return height of a node (0 if null)
int getHeight(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// Helper: return Balance Factor = height(left) - height(right)
int getBalanceFactor(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// Helper: create a new AVL node
AVLNode* createAVLNode(int key) {
    AVLNode* node = new AVLNode();
    node->key = key;
    node->height = 1; // New node is initially added at leaf level (height 1)
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

// Right rotation around y (Left-Left case)
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights (order matters: y is now child of x)
    y->height = 1 + getMax(getHeight(y->left), getHeight(y->right));
    x->height = 1 + getMax(getHeight(x->left), getHeight(x->right));

    // Return new subtree root
    return x;
}

// Left rotation around x (Right-Right case)
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights (order matters: x is now child of y)
    x->height = 1 + getMax(getHeight(x->left), getHeight(x->right));
    y->height = 1 + getMax(getHeight(y->left), getHeight(y->right));

    // Return new subtree root
    return y;
}

// Insert a key into AVL tree and rebalance via rotations
AVLNode* insertNode(AVLNode* node, int key) {
    // 1. Standard BST insertion
    if (node == nullptr) {
        return createAVLNode(key);
    }

    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    } else {
        // Duplicate keys not allowed in standard BST
        return node;
    }

    // 2. Update height of this ancestor node
    node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));

    // 3. Get balance factor to check whether this node became unbalanced
    int balance = getBalanceFactor(node);

    // Case 1: Left Left (LL)
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Case 2: Right Right (RR)
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Case 3: Left Right (LR)
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Case 4: Right Left (RL)
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return unchanged node pointer
    return node;
}

// Helper to find the node with minimum key value (inorder successor)
AVLNode* getMinValueNode(AVLNode* node) {
    AVLNode* curr = node;
    while (curr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

// Delete a key from the AVL tree and rebalance along ancestor path
AVLNode* deleteNode(AVLNode* root, int key) {
    // 1. Standard BST deletion
    if (root == nullptr) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node found: handle 0, 1, or 2 children

        // Node with only one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                // No child case
                temp = root;
                root = nullptr;
            } else {
                // One child case: copy contents of non-empty child
                *root = *temp;
            }
            delete temp;
        } else {
            // Node with two children: get inorder successor (smallest in right subtree)
            AVLNode* temp = getMinValueNode(root->right);

            // Copy inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If tree had only one node, return null
    if (root == nullptr) {
        return root;
    }

    // 2. Update height of current node
    root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));

    // 3. Check balance factor to see if rebalancing is required
    int balance = getBalanceFactor(root);

    // Case 1: Left Left (LL)
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }

    // Case 2: Left Right (LR)
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Case 3: Right Right (RR)
    if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }

    // Case 4: Right Left (RL)
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder traversal showing Key, Height, and Balance Factor
void printInorderDump(AVLNode* root) {
    if (root == nullptr) {
        return;
    }
    printInorderDump(root->left);
    cout << "    [Key: " << root->key
         << " | Height: " << root->height
         << " | Balance Factor: " << getBalanceFactor(root) << "]" << endl;
    printInorderDump(root->right);
}

// Level-Order traversal dump using a simple custom array-based queue
void printLevelOrderDump(AVLNode* root) {
    if (root == nullptr) {
        cout << "    [Empty Tree]" << endl;
        return;
    }

    // Simple custom circular queue of pointers for level-order traversal
    const int MAX_Q = 200;
    AVLNode* queueArr[MAX_Q];
    int front = 0;
    int rear = 0;

    // Enqueue root
    queueArr[rear++] = root;
    int currentLevel = 0;

    while (front < rear) {
        int levelNodeCount = rear - front;
        cout << "    Level " << currentLevel << ": ";

        for (int i = 0; i < levelNodeCount; i++) {
            AVLNode* curr = queueArr[front++];
            cout << "[Key: " << curr->key
                 << ", H: " << curr->height
                 << ", BF: " << getBalanceFactor(curr) << "] ";

            if (curr->left != nullptr) {
                queueArr[rear++] = curr->left;
            }
            if (curr->right != nullptr) {
                queueArr[rear++] = curr->right;
            }
        }
        cout << endl;
        currentLevel++;
    }
}

// Display tree state after any operation
void printTreeState(AVLNode* root, const char* label) {
    cout << "\n[" << label << "]\n";
    cout << "  Level-Order Structure:" << endl;
    printLevelOrderDump(root);
    cout << "  Inorder Sorted Listing:" << endl;
    printInorderDump(root);
    cout << endl;
}

// Top K query helper traversal functions

// Collects top k maximum elements using reverse inorder traversal (Right -> Root -> Left)
void collectTopKMax(AVLNode* root, int& count, int k, int collectedKeys[]) {
    if (root == nullptr || count >= k) {
        return;
    }
    collectTopKMax(root->right, count, k, collectedKeys);
    if (count < k) {
        collectedKeys[count++] = root->key;
    }
    collectTopKMax(root->left, count, k, collectedKeys);
}

// Collects top k minimum elements using standard inorder traversal (Left -> Root -> Right)
void collectTopKMin(AVLNode* root, int& count, int k, int collectedKeys[]) {
    if (root == nullptr || count >= k) {
        return;
    }
    collectTopKMin(root->left, count, k, collectedKeys);
    if (count < k) {
        collectedKeys[count++] = root->key;
    }
    collectTopKMin(root->right, count, k, collectedKeys);
}

// Query top k elements based on selected criterion
void queryTopK(AVLNode* root, int k, Criterion criterion) {
    const int MAX_K = 100;
    int collectedKeys[MAX_K];
    int count = 0;

    if (criterion == CRITERION_MAX) {
        cout << ">> Query Top " << k << " Elements [Criterion: MAXIMUM (Largest)]:" << endl;
        collectTopKMax(root, count, k, collectedKeys);
        cout << "   Result: [ ";
        for (int i = 0; i < count; i++) {
            cout << collectedKeys[i] << (i < count - 1 ? ", " : " ");
        }
        cout << "]" << endl << endl;
    }
    else if (criterion == CRITERION_MIN) {
        cout << ">> Query Top " << k << " Elements [Criterion: MINIMUM (Smallest)]:" << endl;
        collectTopKMin(root, count, k, collectedKeys);
        cout << "   Result: [ ";
        for (int i = 0; i < count; i++) {
            cout << collectedKeys[i] << (i < count - 1 ? ", " : " ");
        }
        cout << "]" << endl << endl;
    }
    else if (criterion == CRITERION_SUM) {
        cout << ">> Query Top " << k << " Elements [Criterion: SUM OF MAXIMUMS]:" << endl;
        collectTopKMax(root, count, k, collectedKeys);
        int totalSum = 0;
        cout << "   Result Elements: [ ";
        for (int i = 0; i < count; i++) {
            cout << collectedKeys[i] << (i < count - 1 ? ", " : " ");
            totalSum += collectedKeys[i];
        }
        cout << "]" << endl;
        cout << "   Calculated Cumulative Sum: " << totalSum << endl << endl;
    }
}

// Delete top k maximum elements one by one with rebalancing
AVLNode* deleteTopK(AVLNode* root, int k) {
    const int MAX_K = 100;
    int keysToDelete[MAX_K];
    int count = 0;

    // Collect top k maximum keys first
    collectTopKMax(root, count, k, keysToDelete);

    cout << ">> Deleting Top " << count << " Maximum Elements One-by-One:" << endl;
    cout << "   Target keys to delete: [ ";
    for (int i = 0; i < count; i++) {
        cout << keysToDelete[i] << (i < count - 1 ? ", " : " ");
    }
    cout << "]" << endl << endl;

    // Sequentially delete each key and display tree rebalancing
    for (int i = 0; i < count; i++) {
        int key = keysToDelete[i];
        cout << ">>> Step " << (i + 1) << ": Deleting Key (" << key << ") from AVL Tree..." << endl;
        root = deleteNode(root, key);

        char label[64];
        // Construct simple message label
        int pos = 0;
        const char* prefix = "Tree State after Deleting Key ";
        while (prefix[pos] != '\0') {
            label[pos] = prefix[pos];
            pos++;
        }
        // Append key digits
        int tempK = key;
        char digits[10];
        int dCount = 0;
        if (tempK == 0) {
            digits[dCount++] = '0';
        } else {
            while (tempK > 0) {
                digits[dCount++] = '0' + (tempK % 10);
                tempK /= 10;
            }
        }
        for (int d = dCount - 1; d >= 0; d--) {
            label[pos++] = digits[d];
        }
        label[pos] = '\0';

        printTreeState(root, label);
    }

    return root;
}

// Function to clean up all allocated memory of the AVL Tree
void freeAVLTree(AVLNode* root) {
    if (root == nullptr) {
        return;
    }
    freeAVLTree(root->left);
    freeAVLTree(root->right);
    delete root;
}

// Main demonstration for Task 3
int main() {
    cout << "Task 3: AVL Tree Operations & Top K Tracking\n\n";

    AVLNode* root = nullptr;

    // Sequence of elements to insert (triggers various rotation types LL, RR, LR, RL)
    int insertSequence[] = {50, 20, 60, 10, 8, 15, 30, 25, 70, 80};
    int totalElements = 10;

    cout << "Part 1: Inserting Elements with Automatic Rebalancing\n";
    for (int i = 0; i < totalElements; i++) {
        int key = insertSequence[i];
        cout << "-> Inserting Key: " << key << endl;
        root = insertNode(root, key);
    }
    cout << endl;

    // Print tree state after all insertions complete
    printTreeState(root, "Complete AVL Tree Structure After All Insertions");

    cout << "Part 2: Querying Top K Elements\n";
    int k = 3;

    // 1. Query Top k Maximum
    queryTopK(root, k, CRITERION_MAX);

    // 2. Query Top k Minimum
    queryTopK(root, k, CRITERION_MIN);

    // 3. Query Top k Sum
    queryTopK(root, k, CRITERION_SUM);

    cout << "Part 3: Deleting Top K Elements with Automatic Rebalancing\n";
    // Delete top k (k=3) maximum elements one-by-one with rebalance check
    root = deleteTopK(root, k);

    // Final check
    printTreeState(root, "Final AVL Tree Structure after Deletions");

    // Clean up memory
    freeAVLTree(root);
    cout << "Memory successfully freed. Task 3 completed." << endl;

    return 0;
}

#include <iostream>

using namespace std;

// node for binary tree
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// simple stack implementation for tree nodes
struct NodeStack {
    TreeNode* items[150];
    int top_idx;

    NodeStack() {
        top_idx = -1;
    }

    bool is_empty() {
        return (top_idx == -1);
    }

    void push(TreeNode* nd) {
        if (top_idx < 149) {
            top_idx++;
            items[top_idx] = nd;
        }
    }

    TreeNode* pop() {
        if (is_empty()) {
            return nullptr;
        }
        TreeNode* res = items[top_idx];
        top_idx--;
        return res;
    }

    TreeNode* peek() {
        if (is_empty()) return nullptr;
        return items[top_idx];
    }
};



// parse binary tree string like a(b(d,e),c(,f(g,)))
TreeNode* parseTreeStr(const char* str) {
    if (!str || str[0] == '\0') return nullptr;

    NodeStack st_nodes;
    TreeNode* rootNd = nullptr;
    TreeNode* lastCreated = nullptr;
    int childState = 0; // 1 for left child, 2 for right child

    int k = 0;
    while (str[k] != '\0') {
        char ch = str[k];

        if (ch == ' ' || ch == '\t') {
            k++;
            continue;
        }

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            TreeNode* newNd = new TreeNode(ch);
            if (rootNd == nullptr) {
                rootNd = newNd;
            }

            if (!st_nodes.is_empty()) {
                TreeNode* parentNd = st_nodes.peek();
                if (childState == 1) {
                    parentNd->left = newNd;
                } else if (childState == 2) {
                    parentNd->right = newNd;
                }
            }

            lastCreated = newNd;
        }
        else if (ch == '(') {
            st_nodes.push(lastCreated);
            childState = 1;
        }
        else if (ch == ',') {
            childState = 2;
        }
        else if (ch == ')') {
            st_nodes.pop();
        }

        k++;
    }

    return rootNd;
}



// recursive preorder traversal
void printPreorderRec(TreeNode* r) {
    if (r == nullptr) return;

    cout << r->data << " ";
    printPreorderRec(r->left);
    printPreorderRec(r->right);
}

// iterative inorder traversal using stack ADT
void printInorderIter(TreeNode* r) {
    NodeStack st_in;
    TreeNode* currNd = r;

    while (currNd != nullptr || !st_in.is_empty()) {
        while (currNd != nullptr) {
            st_in.push(currNd);
            currNd = currNd->left;
        }

        currNd = st_in.pop();
        cout << currNd->data << " ";
        currNd = currNd->right;
    }
}

// iterative postorder traversal using two stacks
void printPostorderIter(TreeNode* r) {
    if (r == nullptr) return;

    NodeStack st1;
    NodeStack st2;

    st1.push(r);
    while (!st1.is_empty()) {
        TreeNode* currP = st1.pop();
        st2.push(currP);

        if (currP->left != nullptr) {
            st1.push(currP->left);
        }
        if (currP->right != nullptr) {
            st1.push(currP->right);
        }
    }

    while (!st2.is_empty()) {
        TreeNode* outNd = st2.pop();
        cout << outNd->data << " ";
    }
}



// validate tree string without constructing tree
bool validateTreeString(const char* s) {
    if (!s || s[0] == '\0') return false;

    int parenCount = 0;
    int commaCount[50];
    int depthLvl = 0;

    for (int i = 0; i < 50; i++) commaCount[i] = 0;

    int idx = 0;
    bool expectIdentifier = true;

    while (s[idx] != '\0') {
        char c = s[idx];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            expectIdentifier = false;
        }
        else if (c == '(') {
            parenCount++;
            depthLvl++;
            if (depthLvl >= 50) return false;
            commaCount[depthLvl] = 0;
        }
        else if (c == ',') {
            if (depthLvl == 0) return false; // comma outside brackets
            commaCount[depthLvl]++;
            if (commaCount[depthLvl] > 1) {
                // binary tree can only have at most 1 comma per pair of parens (2 children)
                return false;
            }
        }
        else if (c == ')') {
            if (parenCount <= 0) return false;
            parenCount--;
            depthLvl--;
        }
        else if (c != ' ' && c != '\t') {
            return false; // unsuported character
        }

        idx++;
    }

    return (parenCount == 0);
}



// compute height of binary tree
int getTreeHeight(TreeNode* r) {
    if (r == nullptr) return -1; // height in edges

    int lH = getTreeHeight(r->left);
    int rH = getTreeHeight(r->right);

    if (lH > rH) return lH + 1;
    return rH + 1;
}

// compute and display depth of each node recursively
void showNodeDepths(TreeNode* r, int currDepth) {
    if (r == nullptr) return;

    cout << "  Node '" << r->data << "' -> Depth: " << currDepth << endl;

    showNodeDepths(r->left, currDepth + 1);
    showNodeDepths(r->right, currDepth + 1);
}



// BST node structure for integer sequence
struct BSTNode {
    int val;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

// insert into BST
BSTNode* insertBST(BSTNode* rootNd, int v) {
    if (rootNd == nullptr) {
        return new BSTNode(v);
    }

    if (v < rootNd->val) {
        rootNd->left = insertBST(rootNd->left, v);
    } else if (v > rootNd->val) {
        rootNd->right = insertBST(rootNd->right, v);
    }

    return rootNd;
}

// inorder traversal for BST
void inorderBST(BSTNode* r) {
    if (r == nullptr) return;

    inorderBST(r->left);
    cout << r->val << " ";
    inorderBST(r->right);
}



int main() {
    cout << "Task 1: Binary Tree Representation and Operations" << endl << endl;

    const char* treeExpression = "a(b(d,e),c(,f(g,)))";
    cout << "Given Tree Expression: " << treeExpression << endl << endl;

    // Subtask 1: Parse and build tree
    cout << "1. Generating Binary Tree from given string..." << endl;
    TreeNode* root = parseTreeStr(treeExpression);
    cout << "Tree successfully parsed and constructed in memory." << endl << endl;

    // Subtask 2: Preorder recursive
    cout << "2. Preorder Traversal (Recursive):" << endl;
    cout << "Result: ";
    printPreorderRec(root);
    cout << endl << endl;

    // Subtask 3: Inorder using linear ADT (Stack)
    cout << "3. Inorder Traversal (Iterative using Stack ADT):" << endl;
    cout << "Result: ";
    printInorderIter(root);
    cout << endl << endl;

    // Subtask 4: Postorder iterative using stack
    cout << "4. Postorder Traversal (Iterative using Stack):" << endl;
    cout << "Result: ";
    printPostorderIter(root);
    cout << endl << endl;

    // Subtask 5: Validation without building
    cout << "5. Validating Tree String Without Building Tree:" << endl;
    cout << "Validating \"" << treeExpression << "\": ";
    if (validateTreeString(treeExpression)) {
        cout << "VALID" << endl;
    } else {
        cout << "INVALID" << endl;
    }

    const char* badExpr1 = "a(b(d,e,z),c)"; // 3 children inside
    cout << "Validating invalid string \"" << badExpr1 << "\": ";
    if (validateTreeString(badExpr1)) {
        cout << "VALID" << endl;
    } else {
        cout << "INVALID (Detected > 2 children in subtree)" << endl;
    }

    const char* badExpr2 = "a(b(d,e),c"; // unballanced
    cout << "Validating invalid string \"" << badExpr2 << "\": ";
    if (validateTreeString(badExpr2)) {
        cout << "VALID" << endl;
    } else {
        cout << "INVALID (Mismatched parentheses)" << endl;
    }
    cout << endl;

    // Subtask 6: Height and Depth
    cout << "6. Height and Depth Calculation:" << endl;
    int hEdges = getTreeHeight(root);
    cout << "Total Tree Height (edges): " << hEdges << " (Tree levels: " << hEdges + 1 << ")" << endl;
    cout << "Depths of individual nodes:" << endl;
    showNodeDepths(root, 0);
    cout << endl;

    // Subtask 7: Generate BST from integer sequence
    cout << "7. Generating BST from Sequence of Integers:" << endl;
    int seq[] = {50, 30, 70, 20, 40, 60, 80};
    int seqSize = sizeof(seq) / sizeof(seq[0]);
    cout << "Input Sequence: [50, 30, 70, 20, 40, 60, 80]" << endl;

    BSTNode* bstRoot = nullptr;
    for (int i = 0; i < seqSize; i++) {
        bstRoot = insertBST(bstRoot, seq[i]);
    }

    cout << "BST Inorder Traversal (Sorted order): ";
    inorderBST(bstRoot);
    cout << endl;

    return 0;
}

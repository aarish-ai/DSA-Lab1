#include <iostream>
#include <string>

using namespace std;

// student record structure
struct Student {
    int studentID;
    string name;
    float GPA;

    Student* left;
    Student* right;

    Student(int id, string stName, float gpaVal) {
        studentID = id;
        name = stName;
        GPA = gpaVal;
        left = nullptr;
        right = nullptr;
    }
};



// function to insert a new student record ordered by studentID
Student* insertRecord(Student* rootNd, int id, string name, float gpa) {
    if (rootNd == nullptr) {
        return new Student(id, name, gpa);
    }

    if (id < rootNd->studentID) {
        rootNd->left = insertRecord(rootNd->left, id, name, gpa);
    } 
    else if (id > rootNd->studentID) {
        rootNd->right = insertRecord(rootNd->right, id, name, gpa);
    } 
    else {
        cout << "  [Warning] Student with ID " << id << " already exists in records." << endl;
    }

    return rootNd;
}



// search student by ID
Student* searchRecord(Student* rootNd, int targetId) {
    if (rootNd == nullptr || rootNd->studentID == targetId) {
        return rootNd;
    }

    if (targetId < rootNd->studentID) {
        return searchRecord(rootNd->left, targetId);
    }

    return searchRecord(rootNd->right, targetId);
}



// helper function to find node with minimum value (inorder successor)
Student* findMinNode(Student* nd) {
    Student* curr = nd;
    while (curr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

// delete student record by ID
Student* deleteRecord(Student* rootNd, int id) {
    if (rootNd == nullptr) {
        cout << "  Student ID " << id << " not found for deletion." << endl;
        return nullptr;
    }

    if (id < rootNd->studentID) {
        rootNd->left = deleteRecord(rootNd->left, id);
    } 
    else if (id > rootNd->studentID) {
        rootNd->right = deleteRecord(rootNd->right, id);
    } 
    else {
        // node to be deleted found

        // case 1: no child (leaf node)
        if (rootNd->left == nullptr && rootNd->right == nullptr) {
            delete rootNd;
            return nullptr;
        }
        // case 2: one child
        else if (rootNd->left == nullptr) {
            Student* temp = rootNd->right;
            delete rootNd;
            return temp;
        } 
        else if (rootNd->right == nullptr) {
            Student* temp = rootNd->left;
            delete rootNd;
            return temp;
        }
        // case 3: two children
        else {
            Student* succ = findMinNode(rootNd->right);
            // copy successor data
            rootNd->studentID = succ->studentID;
            rootNd->name = succ->name;
            rootNd->GPA = succ->GPA;

            // delete inorder successor
            rootNd->right = deleteRecord(rootNd->right, succ->studentID);
        }
    }

    return rootNd;
}



// inorder traversal to display student records sorted by ID
void displayInorder(Student* rootNd) {
    if (rootNd == nullptr) return;

    displayInorder(rootNd->left);

    cout << "  ID: " << rootNd->studentID 
         << " | Name: " << rootNd->name;
    if (rootNd->name.length() < 12) cout << "\t";
    cout << "\t| GPA: " << rootNd->GPA << endl;

    displayInorder(rootNd->right);
}



// count total number of students recursively
int countTotalStudents(Student* rootNd) {
    if (rootNd == nullptr) return 0;
    return 1 + countTotalStudents(rootNd->left) + countTotalStudents(rootNd->right);
}

// helper recursive function to locate highest and lowest GPA students
void findGPAExtremes(Student* rootNd, Student*& minGpaStu, Student*& maxGpaStu) {
    if (rootNd == nullptr) return;

    if (minGpaStu == nullptr || rootNd->GPA < minGpaStu->GPA) {
        minGpaStu = rootNd;
    }
    if (maxGpaStu == nullptr || rootNd->GPA > maxGpaStu->GPA) {
        maxGpaStu = rootNd;
    }

    findGPAExtremes(rootNd->left, minGpaStu, maxGpaStu);
    findGPAExtremes(rootNd->right, minGpaStu, maxGpaStu);
}

// display all students with GPA strictly above user defined threshold
void displayAboveGPA(Student* rootNd, float threshold) {
    if (rootNd == nullptr) return;

    displayAboveGPA(rootNd->left, threshold);

    if (rootNd->GPA > threshold) {
        cout << "  ID: " << rootNd->studentID 
             << " | Name: " << rootNd->name;
        if (rootNd->name.length() < 12) cout << "\t";
        cout << "\t| GPA: " << rootNd->GPA << endl;
    }

    displayAboveGPA(rootNd->right, threshold);
}



int main() {
    cout << "Task 2: Student Record Management System using BST" << endl << endl;

    Student* root = nullptr;

    // 1 & 2: Insert multiple student records into BST
    cout << "1. Inittializing BST with Student Records..." << endl;
    root = insertRecord(root, 105, "Ahmed Ali", 3.75f);
    root = insertRecord(root, 102, "Bilal Khan", 2.85f);
    root = insertRecord(root, 108, "Hamza Tariq", 3.92f);
    root = insertRecord(root, 101, "Zainab Bibi", 3.10f);
    root = insertRecord(root, 104, "Usman Ghani", 2.45f);
    root = insertRecord(root, 106, "Ayesha Malik", 3.65f);
    root = insertRecord(root, 110, "Saad Farooq", 3.88f);
    cout << "Successfully inserted 7 student records." << endl << endl;

    // 3: Display Inorder traversal (sorted by ID)
    cout << "2. Inorder Traversal of Student Records (Sorted by ID):" << endl;
    displayInorder(root);
    cout << endl;

    // 4: Search operation
    cout << "3. Searching for Student Records:" << endl;
    int searchId1 = 104;
    cout << "Searching for Student ID " << searchId1 << "..." << endl;
    Student* s1 = searchRecord(root, searchId1);
    if (s1 != nullptr) {
        cout << "  Found: ID=" << s1->studentID << ", Name=" << s1->name << ", GPA=" << s1->GPA << endl;
    } else {
        cout << "  Student ID " << searchId1 << " not found in records." << endl;
    }

    int searchId2 = 199;
    cout << "Searching for Student ID " << searchId2 << "..." << endl;
    Student* s2 = searchRecord(root, searchId2);
    if (s2 != nullptr) {
        cout << "  Found: ID=" << s2->studentID << ", Name=" << s2->name << ", GPA=" << s2->GPA << endl;
    } else {
        cout << "  Student ID " << searchId2 << " not found in records." << endl;
    }
    cout << endl;

    // 5: Analytical features
    cout << "4. Analytical Features:" << endl;
    int totalCount = countTotalStudents(root);
    cout << "Total number of students enrolled: " << totalCount << endl << endl;

    Student* minStu = nullptr;
    Student* maxStu = nullptr;
    findGPAExtremes(root, minStu, maxStu);

    if (maxStu != nullptr) {
        cout << "Highest GPA: " << maxStu->GPA << " (Student: " << maxStu->name << ", ID: " << maxStu->studentID << ")" << endl;
    }
    if (minStu != nullptr) {
        cout << "Lowest GPA:  " << minStu->GPA << " (Student: " << minStu->name << ", ID: " << minStu->studentID << ")" << endl;
    }
    cout << endl;

    float cutoff = 3.0f;
    cout << "Students with GPA above " << cutoff << " (Dean's Honor Roll):" << endl;
    displayAboveGPA(root, cutoff);
    cout << endl;

    // 6: Delete operations
    cout << "5. Performing Deletion Operations:" << endl;
    
    // Delete leaf node (ID 101)
    cout << "Deleting Leaf Node (Student ID 101 - Zainab Bibi)..." << endl;
    root = deleteRecord(root, 101);
    cout << "Record deleted successfully." << endl;

    // Delete node with two children (ID 102 - Bilal Khan)
    cout << "Deleting Node with Two Children (Student ID 102 - Bilal Khan)..." << endl;
    root = deleteRecord(root, 102);
    cout << "Record deleted successfully." << endl << endl;

    // Display records after deletion
    cout << "Inorder Listing After Deletions:" << endl;
    displayInorder(root);
    cout << endl;

    cout << "Updated total student count: " << countTotalStudents(root) << endl;

    return 0;
}

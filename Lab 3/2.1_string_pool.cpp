#include <iostream>
#include <string>

using namespace std;

class StringPool {
private:
    string* stringPool;
    int currentSize;

    int maxSize;

public:
    
    StringPool() {
        maxSize = 5;

        currentSize = 0;


        stringPool = new string[maxSize];
    }

    
    ~StringPool() {
        delete[] stringPool;

        stringPool = nullptr;
    }

    // Adds a string to the pool if capacity allows
    void addString(const string& str) {
        if (currentSize < maxSize) {

            stringPool[currentSize] = str;


            currentSize++;

            cout << "Added: \"" << str << "\"\n";
        } else {

            cout << "Pool is full. Cannot add: \"" << str << "\"\n";
        }
    }

    // Removes a string without freeing memory
    void removeString() {
        if (currentSize > 0) {


            currentSize--;

            cout << "Removed (without freeing): \"" << stringPool[currentSize] << "\"\n";
        } else {

            cout << "Pool is empty.\n";
        }
    }

    // Detects and fixes memory leak
    void fixMemoryLeak() {

        bool foundLeak = false;
        for (int i = currentSize; i < maxSize; i++) {

            if (!stringPool[i].empty()) {

                cout << "Leaked data detected at slot " << i << ": \"" << stringPool[i] << "\"\n";
                stringPool[i].clear();

                stringPool[i].shrink_to_fit();
                foundLeak = true;
            }
        }
        if (foundLeak) {
            cout << "Memory leak fixed: removed string memory cleared.\n";

        } else {
            cout << "No memory leaks detected.\n";
        }
    }

    // Properly removes a string and frees memory
    void removeStringProperly() {
        if (currentSize > 0) {
            currentSize--;

            cout << "Properly removed and cleared: \"" << stringPool[currentSize] << "\"\n";

            stringPool[currentSize].clear();
            stringPool[currentSize].shrink_to_fit();

        } else {
            cout << "Pool is empty.\n";
        }
    }

    // Displays current pool status and memory slots
    void displayStatus() const {
        cout << "\n--- String Pool Status ---\n";

        cout << "Pool size: " << currentSize << " / " << maxSize << "\n";

        cout << "Active strings:\n";

        if (currentSize == 0) {
            cout << "  (none)\n";

        } else {
            for (int i = 0; i < currentSize; i++) {
                cout << "  [" << i << "] " << stringPool[i] << "\n";
            }
        }

        cout << "Memory slot inspection:\n";

        for (int i = 0; i < maxSize; i++) {
            cout << "  Slot [" << i << "]: ";

            if (stringPool[i].empty()) {

                cout << "<empty/cleared>";
            } else {
                cout << "\"" << stringPool[i] << "\"";

            }

            if (i < currentSize) {

                cout << " (Active)\n";
            } else if (!stringPool[i].empty()) {

                cout << " (LEAK: Inactive but retained in memory)\n";
            } else {

                cout << " (Clean / Free)\n";
            }
        }
        cout << "--------------------------\n\n";
    }
};

int main() {
    cout << "String Pool Memory Management\n\n";

    StringPool pool;

    // 1. Add multiple strings to the pool
    cout << "Step 1: Adding strings to pool\n";
    pool.addString("DataStructures");
    pool.addString("Algorithms");
    
    pool.addString("Pointers");
    pool.addString("Memory");

    pool.displayStatus();

    // 2. Remove strings without freeing memory
    cout << "Step 2: Removing strings without freeing memory\n";
    pool.removeString();
    pool.removeString();

    pool.displayStatus();

    // 3. Detect and fix the memory leak
    cout << "Step 3: Detecting and fixing memory leak\n";
    pool.fixMemoryLeak();

    pool.displayStatus();

    // 4. Properly remove another string
    cout << "Step 4: Properly removing a string\n";
    pool.removeStringProperly();

    pool.displayStatus();

}

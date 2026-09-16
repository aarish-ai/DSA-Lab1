#include <iostream>

using namespace std;

int main() {
    // Lab 2 - Task 1: Find and print the memory in bytes occupied by 
    // int, long, double, float, and char

    cout << "Size of int:    " << sizeof(int)    << " byte(s)" << endl;
    cout << "Size of long:   " << sizeof(long)   << " byte(s)" << endl;
    cout << "Size of double: " << sizeof(double) << " byte(s)" << endl;
    cout << "Size of float:  " << sizeof(float)  << " byte(s)" << endl;
    cout << "Size of char:   " << sizeof(char)   << " byte(s)" << endl;

    return 0;
}

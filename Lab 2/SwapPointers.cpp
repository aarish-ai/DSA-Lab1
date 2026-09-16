#include <iostream>

using namespace std;


// Part a: Swap values taking the address of both variables (Single Pointers)

void swapByPointer(int* x, int* y) {
    // Dereference once to read the integer value at address x
    int temp = *x;

    
    *x = *y;

    // Write original value of x into memory location y
    *y = temp;
}


// Part b: Swap values using pointer-to-pointer variables (Double Pointers)

void swapByDoublePointer(int** x, int** y) {
    // Dereference twice: *x gives pointer pa, **x gives the integer value in variable a
    int temp = **x;

    // Write the integer value in b (**y) into variable a (**x)
    **x = **y;

    // Write original value of a into variable b (**y)
    **y = temp;
}

int main() {
    // Required declarations
    int a = 5, b = 10;
    int *pa = &a;
    int *pb = &b;
    int **ppa = &pa;
    int **ppb = &pb;


    // Initial state
    cout << "\n[Initial State]" << endl;
    cout << "  a = " << a << " (Address: " << &a << ")" << endl;
    cout << "  b = " << b << " (Address: " << &b << ")" << endl;
    cout << "  pa points to:  " << pa  << ", dereferenced *pa  = " << *pa  << endl;
    cout << "  pb points to:  " << pb  << ", dereferenced *pb  = " << *pb  << endl;
    cout << "  ppa points to: " << ppa << ", dereferenced **ppa = " << **ppa << endl;
    cout << "  ppb points to: " << ppb << ", dereferenced **ppb = " << **ppb << endl;

    
    // Demonstration 1: Part a - Swap using Single Pointers (Address of variables)
    
    cout << "\n--------------------------------------------------" << endl;
    cout << " Part a: Swapping values using swapByPointer(&a, &b)" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Before swap: a = " << a << ", b = " << b << endl;

    // Passing the addresses of a and b directly (pa and pb also hold &a and &b)
    swapByPointer(&a, &b);

    cout << "After swap:  a = " << a << ", b = " << b << endl;
    cout << "Verification via pointers: *pa = " << *pa << ", *pb = " << *pb << endl;

    
    // Demonstration 2: Part b - Swap using Double Pointers (ppa and ppb)
    
    cout << "\n--------------------------------------------------" << endl;
    cout << " Part b: Swapping values using swapByDoublePointer(ppa, ppb)" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Before swap: a = " << a << ", b = " << b << endl;

    // Passing double pointers ppa and ppb
    swapByDoublePointer(ppa, ppb);

    cout << "After swap:  a = " << a << ", b = " << b << endl;
    cout << "Verification via double pointers: **ppa = " << **ppa << ", **ppb = " << **ppb << endl;

    cout << "\n==================================================" << endl;
    cout << "Final Verification:" << endl;
    cout << "  a = " << a << " (restored to 5)" << endl;
    cout << "  b = " << b << " (restored to 10)" << endl;
    cout << "==================================================" << endl;

    return 0;
}

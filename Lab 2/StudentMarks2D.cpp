#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Lab 2 - Task 6: Dynamic 2D Array for Student Marks

int main() {
    int rows = 0;
    int cols = 0;

    cout << "   Lab 2 - Task 6: Student Marks 2D Dynamic Array   \n";


    // Step 1: Read and validate rows and cols before allocation
    // ------------------------------------------------------------------------
    cout << "Enter number of students (rows > 0): ";
    while (!(cin >> rows) || rows <= 0) {
        if (cin.eof()) {
            cerr << "Error: Unexpected end of input.\n";
            return 1;
        }
        cout << "Invalid input. Number of students must be a positive integer (> 0). Re-enter: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Enter number of subjects (cols > 0): ";
    while (!(cin >> cols) || cols <= 0) {
        if (cin.eof()) {
            cerr << "Error: Unexpected end of input.\n";
            return 1;
        }
        cout << "Invalid input. Number of subjects must be a positive integer (> 0). Re-enter: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "\nAllocating memory for " << rows << " student(s) and " << cols << " subject(s)...\n";


    // Step 2: Allocate dynamic 2D array
    //   - First, allocate array of row pointers (int**)
    //   - Next, allocate cols integers for each row
    // ------------------------------------------------------------------------
    int** marks = new int*[rows];
    for (int r = 0; r < rows; r++) {
        marks[r] = new int[cols];
    }


    // Step 3: Read marks (0 to 100) using pointer dereference notation
    //         *(*(marks + r) + c)
    // ------------------------------------------------------------------------
    cout << "\nEnter marks for each student (0 to 100):\n";
    for (int r = 0; r < rows; r++) {
        cout << "Student " << (r + 1) << " (" << cols << " subject marks): ";
        for (int c = 0; c < cols; c++) {
            // Read directly using pointer notation *(*(marks + r) + c)
            cin >> *(*(marks + r) + c);
        }
    }

    // Step 4: Display the marks matrix using pointer dereference notation
    //         *(*(marks + r) + c)
    // ------------------------------------------------------------------------
    cout << "\n----------------------------------------------------\n";
    cout << "Marks Matrix (" << rows << " Students x " << cols << " Subjects):\n";
    cout << "----------------------------------------------------\n";
    cout << left << setw(12) << "Student";
    for (int c = 0; c < cols; c++) {
        cout << "Sub " << (c + 1) << "\t";
    }
    cout << "\n";

    for (int r = 0; r < rows; r++) {
        cout << left << setw(12) << ("Student " + to_string(r + 1));
        for (int c = 0; c < cols; c++) {
            // Display value using pointer notation *(*(marks + r) + c)
            cout << *(*(marks + r) + c) << "\t";
        }
        cout << "\n";
    }
    cout << "----------------------------------------------------\n";

    // Step 5: Calculate each student's total and determine the top student
    //         - Student numbers start at 1
    //           subsequent students.
    //         - If totals tie, report the first student (strict '>' comparison).
    // ------------------------------------------------------------------------
    int bestTotal = 0;
    int topStudent = 1;

    cout << "\nStudent Totals:\n";
    for (int r = 0; r < rows; r++) {
        int studentTotal = 0;
        for (int c = 0; c < cols; c++) {
            studentTotal += *(*(marks + r) + c);
        }

        cout << "Student " << (r + 1) << " Total: " << studentTotal << "\n";

        // Determine best total and top student
        if (r == 0) {
            // Seed with student 1's total
            bestTotal = studentTotal;
            topStudent = 1;
        } else if (studentTotal > bestTotal) {
            // Strict inequality: if totals tie, the earlier student remains top student
            bestTotal = studentTotal;
            topStudent = r + 1;
        }
    }

    cout << "\n====================================================\n";
    cout << "Top Student: Student " << topStudent << "\n";
    cout << "Highest Total: " << bestTotal << "\n";
    cout << "====================================================\n";

    // Step 6: Proper Memory Cleanup
    //   - Delete each allocated row array
    //   - Delete the row pointer array
    //   - Reset marks to nullptr to avoid dangling pointer
    // ------------------------------------------------------------------------
    for (int r = 0; r < rows; r++) {
        delete[] marks[r];
        marks[r] = nullptr;
    }
    delete[] marks;
    marks = nullptr;

    cout << "\nMemory successfully deallocated and pointer reset to nullptr.\n";

    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> generatePascal(int n) {
    vector<vector<int>> triangle;

    for (int i = 0; i < n; i++) {
        vector<int> row(i + 1, 1);

        for (int j = 1; j < i; j++) {
            row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }

        triangle.push_back(row);
    }

    return triangle;
}

int main() {
    // Test case: n = 0
    vector<vector<int>> result0 = generatePascal(0);
    cout << "n = 0:" << endl;

    for (const auto& row : result0) {
        for (int value : row)
            cout << value << " ";
        cout << endl;
    }

    // Test case: n = 1
    vector<vector<int>> result1 = generatePascal(1);
    cout << "\nn = 1:" << endl;

    for (const auto& row : result1) {
        for (int value : row)
            cout << value << " ";
        cout << endl;
    }

    // Test case: n = 5
    vector<vector<int>> result5 = generatePascal(5);
    cout << "\nn = 5:" << endl;

    for (const auto& row : result5) {
        for (int value : row)
            cout << value << " ";
        cout << endl;
    }

    // Verify row 5
    cout << "\nRow 5: ";
    for (int value : result5[4])
        cout << value << " ";

}
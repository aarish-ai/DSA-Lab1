#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> add(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}

vector<vector<int>> subtract(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];

    return C;
}

vector<vector<int>> strassen(vector<vector<int>> A, vector<vector<int>> B) {
    int n = A.size();

    if (n == 1)
        return {{A[0][0] * B[0][0]}};

    int k = n / 2;

    vector<vector<int>> A11(k, vector<int>(k));
    vector<vector<int>> A12(k, vector<int>(k));
    vector<vector<int>> A21(k, vector<int>(k));
    vector<vector<int>> A22(k, vector<int>(k));

    vector<vector<int>> B11(k, vector<int>(k));
    vector<vector<int>> B12(k, vector<int>(k));
    vector<vector<int>> B21(k, vector<int>(k));
    vector<vector<int>> B22(k, vector<int>(k));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Seven multiplications
    auto M1 = strassen(add(A11, A22), add(B11, B22));
    auto M2 = strassen(add(A21, A22), B11);
    auto M3 = strassen(A11, subtract(B12, B22));
    auto M4 = strassen(A22, subtract(B21, B11));
    auto M5 = strassen(add(A11, A12), B22);
    auto M6 = strassen(subtract(A21, A11), add(B11, B12));
    auto M7 = strassen(subtract(A12, A22), add(B21, B22));

    vector<vector<int>> C(n, vector<int>(n));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {

            C[i][j] =
                M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];

            C[i][j + k] =
                M3[i][j] + M5[i][j];

            C[i + k][j] =
                M2[i][j] + M4[i][j];

            C[i + k][j + k] =
                M1[i][j] + M3[i][j] - M2[i][j] + M6[i][j];
        }
    }

    return C;
}

// Normal matrix multiplication
vector<vector<int>> multiply(vector<vector<int>> A,
                              vector<vector<int>> B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

void print(vector<vector<int>> A) {
    for (auto row : A) {
        for (int x : row)
            cout << x << " ";
        cout << endl;
    }
}

bool same(vector<vector<int>> A, vector<vector<int>> B) {
    return A == B;
}

int main() {

    // 2x2 test
    vector<vector<int>> A = {
        {1, 2},
        {3, 4}
    };

    vector<vector<int>> B = {
        {5, 6},
        {7, 8}
    };

    cout << "2x2 Matrix:" << endl;

    cout << "\nStrassen:" << endl;
    print(strassen(A, B));

    cout << "\nNormal:" << endl;
    print(multiply(A, B));

    cout << "\nSame result: "
         << (same(strassen(A, B), multiply(A, B)) ? "Yes" : "No")
         << endl;


    // 4x4 test
    vector<vector<int>> A4 = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    vector<vector<int>> B4 = {
        {1, 0, 0, 1},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1}
    };

    cout << "\n\n4x4 Matrix:" << endl;

    cout << "\nStrassen:" << endl;
    print(strassen(A4, B4));

    cout << "\nNormal:" << endl;
    print(multiply(A4, B4));

    cout << "\nSame result: "
         << (same(strassen(A4, B4), multiply(A4, B4)) ? "Yes" : "No")
         << endl;


    // Random values test
    vector<vector<int>> R1 = {
        {2, 4, 1, 3},
        {5, 1, 2, 6},
        {3, 7, 4, 2},
        {1, 5, 3, 4}
    };

    vector<vector<int>> R2 = {
        {4, 2, 1, 3},
        {2, 5, 3, 1},
        {1, 3, 4, 2},
        {3, 1, 2, 5}
    };

    cout << "\nRandom Test:" << endl;

    cout << "Same result: "
         << (same(strassen(R1, R2), multiply(R1, R2))
             ? "Yes" : "No")
         << endl;

    return 0;
}
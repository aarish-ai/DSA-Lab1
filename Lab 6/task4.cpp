#include <iostream>
#include <iomanip>

using namespace std;

// 8 possible L-shape moves of a knight
const int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// check if (x, y) is inside board boundaries and unvisited
bool isValid(int x, int y, int N, int** board) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// display board in formatted grid
void printBoard(int** board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(4) << board[i][j];
        }
        cout << "\n";
    }
}

// count unvisited onward moves from candidate square (Warnsdorff's heuristic degree)
int getDegree(int x, int y, int N, int** board) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny, N, board)) {
            count++;
        }
    }
    return count;
}

// helper structure for move ordering
struct MoveOption {
    int moveIdx;
    int degree;
    int nextX;
    int nextY;
};

// sort candidate moves in ascending order of degree (Warnsdorff's rule)
void sortMoves(MoveOption moves[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (moves[j].degree > moves[j + 1].degree) {
                MoveOption temp = moves[j];
                moves[j] = moves[j + 1];
                moves[j + 1] = temp;
            }
        }
    }
}

// recursive backtracking solver with Warnsdorff's heuristic optimization
bool solveKnightTour(int x, int y, int moveNumber, int N, int** board) {
    // Base Case: All N^2 squares visited
    if (moveNumber > N * N) {
        return true;
    }

    // Collect all valid next moves and their degrees
    MoveOption moves[8];
    int validCount = 0;

    for (int i = 0; i < 8; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (isValid(nextX, nextY, N, board)) {
            moves[validCount].moveIdx = i;
            moves[validCount].degree = getDegree(nextX, nextY, N, board);
            moves[validCount].nextX = nextX;
            moves[validCount].nextY = nextY;
            validCount++;
        }
    }

    // Sort moves by degree: Warnsdorff heuristic optimizes search to near O(N^2)
    sortMoves(moves, validCount);

    // Try candidate moves in heuristic order
    for (int i = 0; i < validCount; i++) {
        int nx = moves[i].nextX;
        int ny = moves[i].nextY;

        // Mark move
        board[nx][ny] = moveNumber;

        // Recursive call
        if (solveKnightTour(nx, ny, moveNumber + 1, N, board)) {
            return true;
        }

        // Backtrack: Undo move
        board[nx][ny] = -1;
    }

    return false;
}

void runTour(int N, int startX, int startY) {
    cout << "Board Size: " << N << "x" << N << ", Starting Position: (" << startX << ", " << startY << ")\n";

    // Allocate dynamic 2D array using raw pointers
    int** board = new int*[N];
    for (int i = 0; i < N; i++) {
        board[i] = new int[N];
        for (int j = 0; j < N; j++) {
            board[i][j] = -1; // unvisited
        }
    }

    // Mark starting square
    board[startX][startY] = 1;

    if (solveKnightTour(startX, startY, 2, N, board)) {
        cout << "Valid Knight's Tour Found (Numbered 1 to " << N * N << "):\n\n";
        printBoard(board, N);
    } else {
        cout << "No tour was found for the specified search.\n";
    }

    // Cleanup dynamic memory
    for (int i = 0; i < N; i++) {
        delete[] board[i];
    }
    delete[] board;
    cout << "\n";
}

int main() {
    cout << "Task 4: Knight's Tour Using Recursive Backtracking\n";
    cout << "Optimization: Warnsdorff's Heuristic (O(N^2) Average Running Time)\n\n";

    // Test Case 1: 5x5 board starting at (0, 0)
    cout << "=== Test Case 1: 5x5 Board ===\n";
    runTour(5, 0, 0);

    // Test Case 2: 8x8 standard board starting at (0, 0)
    cout << "=== Test Case 2: 8x8 Board ===\n";
    runTour(8, 0, 0);

    return 0;
}

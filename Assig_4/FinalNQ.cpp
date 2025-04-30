#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// ---------------------------- Backtracking Class ----------------------------
class NQueensBackTracking {
private:
    vector<vector<bool>> board; // 2D chess board representation
    int n; // Size of the board (NxN)

public:
    // Constructor to initialize board of given size
    NQueensBackTracking(int size) {
        this->n = size;
        board.resize(n, vector<bool>(n, false)); // Set all cells to false
    }

    // Recursive function to solve N-Queens using backtracking
    bool Solve(int col) {
        if (col >= n)
            return true; // All queens placed successfully

        for (int row = 0; row < n; row++) {
            if (IsSafe(row, col)) {
                PlaceQueen(row, col); // Place queen

                if (Solve(col + 1))
                    return true; // Recur for next column

                RemoveQueen(row, col); // Backtrack
            }
        }
        return false; // No valid position found in this column
    }

    // Place queen on board
    void PlaceQueen(int row, int col) {
        board[row][col] = true;
    }

    // Remove queen from board (backtracking)
    void RemoveQueen(int row, int col) {
        board[row][col] = false;
    }

    // Check if it's safe to place queen at (row, col)
    bool IsSafe(int row, int col) {
        return RowIsClear(row, col) &&
               UpperDiagIsClear(row, col) &&
               LowerDiagIsClear(row, col);
    }

    // Check row to the left
    bool RowIsClear(int queenRow, int queenCol) {
        for (int col = 0; col < queenCol; col++) {
            if (board[queenRow][col])
                return false;
        }
        return true;
    }

    // Check upper diagonal to the left
    bool UpperDiagIsClear(int queenRow, int queenCol) {
        int row = queenRow, col = queenCol;
        while (row >= 0 && col >= 0) {
            if (board[row][col])
                return false;
            row--;
            col--;
        }
        return true;
    }

    // Check lower diagonal to the left
    bool LowerDiagIsClear(int queenRow, int queenCol) {
        int row = queenRow, col = queenCol;
        while (row < n && col >= 0) {
            if (board[row][col])
                return false;
            row++;
            col--;
        }
        return true;
    }

    // Print the chessboard with queen positions
    void PrintBoard() {
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                cout << (board[row][col] ? "Q " : ". ");
            }
            cout << endl;
        }
    }
};

// ------------------------- Branch and Bound Class --------------------------
class NQueensBranchAndBound {
private:
    vector<int> board; // board[i] = column position of queen in row i
    int n;

public:
    // Constructor to initialize board with -1 (no queen placed)
    NQueensBranchAndBound(int size) {
        this->n = size;
        board.resize(n, -1);
    }

    // Check if it's safe to place a queen at (row, col)
    bool IsSafe(int row, int col) {
        for (int i = 0; i < row; i++) {
            if (board[i] == col || abs(board[i] - col) == abs(i - row))
                return false; // Same column or diagonal
        }
        return true;
    }

    // Bounding function to check feasibility (optional here but included)
    bool Bound(int row) {
        for (int i = 0; i < row; i++) {
            if (board[i] == -1)
                return false; // Unassigned row found => infeasible
        }
        return true;
    }

    // Recursive solver using Branch and Bound
    bool SolveNQueensUtil(int row) {
        if (row == n) {
            PrintBoard(); // Solution found
            return true;
        }

        for (int col = 0; col < n; col++) {
            if (IsSafe(row, col)) {
                board[row] = col; // Place queen

                if (Bound(row) && SolveNQueensUtil(row + 1))
                    return true; // Continue to next row

                board[row] = -1; // Backtrack
            }
        }
        return false; // No valid position found
    }

    // Start the solving process
    bool SolveNQueens() {
        return SolveNQueensUtil(0);
    }

    // Print the board
    void PrintBoard() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << (board[i] == j ? "Q " : ". ");
            }
            cout << endl;
        }
    }
};

// ----------------------------- Main Function -------------------------------
int main() {
    cout << "Which option do you want?\n";
    cout << "1. Backtracking\n";
    cout << "2. Branch and Bound\n";
    
    int op;
    cin >> op;

    if (op == 1) {
        int size;
        cout << "Enter the size of Chess Board (N): ";
        cin >> size;

        NQueensBackTracking solver(size);

        if (solver.Solve(0)) {
            cout << "Solution:\n";
            solver.PrintBoard();
        } else {
            cout << "No solution exists.\n";
        }
    } 
    else if (op == 2) {
        int n;
        cout << "Enter the size of the chessboard (N): ";
        cin >> n;

        NQueensBranchAndBound solver(n);

        if (!solver.SolveNQueens()) {
            cout << "No solution exists for N = " << n << endl;
        }
    } 
    else {
        cout << "Invalid option selected.\n";
    }

    return 0;
}

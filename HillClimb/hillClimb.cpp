#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int N = 9;
typedef vector<vector<int>> Grid;

struct Sudoku {
    Grid board;
    Grid fixed;

    Sudoku(const Grid& input) : board(input), fixed(N, vector<int>(N)) {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (board[i][j] != 0)
                    fixed[i][j] = 1;
        fillRandom();
    }

    void fillRandom() {
        srand(time(0));
        for (int boxRow = 0; boxRow < 3; boxRow++) {
            for (int boxCol = 0; boxCol < 3; boxCol++) {
                vector<int> nums;
                for (int k = 1; k <= 9; k++) nums.push_back(k);
                // Remove already fixed numbers in the box
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        int r = boxRow * 3 + i, c = boxCol * 3 + j;
                        if (fixed[r][c]) nums.erase(remove(nums.begin(), nums.end(), board[r][c]), nums.end());
                    }
                }
                // Fill remaining cells randomly
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        int r = boxRow * 3 + i, c = boxCol * 3 + j;
                        if (!fixed[r][c]) {
                            int idx = rand() % nums.size();
                            board[r][c] = nums[idx];
                            nums.erase(nums.begin() + idx);
                        }
                    }
                }
            }
        }
    }

    int heuristic() {
        int conflicts = 0;
        // Row conflicts
        for (int i = 0; i < N; i++) {
            vector<int> count(N + 1, 0);
            for (int j = 0; j < N; j++) count[board[i][j]]++;
            for (int k = 1; k <= 9; k++) if (count[k] > 1) conflicts += count[k] - 1;
        }
        // Column conflicts
        for (int j = 0; j < N; j++) {
            vector<int> count(N + 1, 0);
            for (int i = 0; i < N; i++) count[board[i][j]]++;
            for (int k = 1; k <= 9; k++) if (count[k] > 1) conflicts += count[k] - 1;
        }
        return conflicts;
    }

    void swapRandomInBox(int boxRow, int boxCol) {
        vector<pair<int, int>> cells;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                int r = boxRow * 3 + i, c = boxCol * 3 + j;
                if (!fixed[r][c]) cells.push_back({r, c});
            }
        if (cells.size() >= 2) {
            int a = rand() % cells.size(), b;
            do {
                b = rand() % cells.size();
            } while (a == b);
            swap(board[cells[a].first][cells[a].second], board[cells[b].first][cells[b].second]);
        }
    }

    bool hillClimb(int maxSteps = 10000) {
        int steps = 0;
        int currentH = heuristic();
        int g = 0;
        while (steps < maxSteps && currentH > 0) {
            Grid best = board;
            int bestH = currentH;
            bool improved = false;
            for (int br = 0; br < 3; br++) {
                for (int bc = 0; bc < 3; bc++) {
                    for (int trial = 0; trial < 5; trial++) {
                        swapRandomInBox(br, bc);
                        int h = heuristic();
                        if (h < bestH) {
                            bestH = h;
                            best = board;
                            improved = true;
                        }
                        board = best; // Undo if worse
                    }
                }
            }
    
            if (improved) {
                board = best;
                currentH = bestH;
                g++;
                int f = g + currentH;
                cout << "g(n): " << g << ", h(n): " << currentH << ", f(n): " << f << endl;
            } else {
                break; // Local optimum
            }
            steps++;
        }
    
        return currentH == 0;
    }
    

    void print() {
        for (int i = 0; i < N; i++) {
            if (i % 3 == 0 && i != 0) cout << "------+-------+------\n";
            for (int j = 0; j < N; j++) {
                if (j % 3 == 0 && j != 0) cout << "| ";
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

int main() {
    Grid puzzle = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    Sudoku s(puzzle);
    cout << "Initial board:\n";
    s.print();

    if (s.hillClimb()) {
        cout << "\nSolved!\n";
        s.print();
    } else {
        cout << "\nLocal optimum reached. Final board:\n";
        s.print();
    }

    return 0;
}


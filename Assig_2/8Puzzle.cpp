#include <bits/stdc++.h>
using namespace std;
 
const int N = 3;
const vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

struct Node {
    vector<vector<int>> state;
    int x, y; // position of 0
    int g, h;
    vector<string> path; // store moves

    bool operator>(const Node& other) const {
        return (g + h) > (other.g + other.h);
    }
};

int manhattan(const vector<vector<int>>& a) {
    int dist = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val = a[i][j];
            if (val == 0) continue;
            int targetX = (val - 1) / N;
            int targetY = (val - 1) % N;
            dist += abs(i - targetX) + abs(j - targetY);
        }
    }
    return dist;
}

bool isGoal(const vector<vector<int>>& a) {
    return a == goal;
}

vector<Node> getNeighbors(Node node) {
    vector<Node> neighbors;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    string dir[] = {"Up", "Down", "Left", "Right"};

    for (int k = 0; k < 4; k++) {
        int nx = node.x + dx[k];
        int ny = node.y + dy[k];

        if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
            vector<vector<int>> newState = node.state;
            swap(newState[node.x][node.y], newState[nx][ny]);
            Node neighbor = {newState, nx, ny, node.g + 1, manhattan(newState), node.path};
            neighbor.path.push_back(dir[k]);
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

void printState(const vector<vector<int>>& state) {
    for (auto row : state) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }
}

void solve(vector<vector<int>> start) {
    int sx, sy;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (start[i][j] == 0) sx = i, sy = j;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<vector<vector<int>>> visited;

    Node startNode = {start, sx, sy, 0, manhattan(start), {}};
    pq.push(startNode);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (visited.count(current.state)) continue;
        visited.insert(current.state);

        cout << "Current state (g = " << current.g << ", h = " << current.h << ", f = " << current.g + current.h << "):\n";
        printState(current.state);
        cout << "----\n";

        if (isGoal(current.state)) {
            cout << "Goal reached in " << current.g << " moves.\n";
            cout << "Path: ";
            for (auto move : current.path) cout << move << " ";
            cout << "\n";
            return;
        }

        for (auto neighbor : getNeighbors(current)) {
            if (!visited.count(neighbor.state))
                pq.push(neighbor);
        }
    }

    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> initial(3, vector<int>(3));
    cout << "Enter the initial state of the puzzle (0 represents the empty tile):\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Enter value at position (" << i << ", " << j << "): ";
            cin >> initial[i][j];
        }
    }

    cout << "\nInitial State:\n";
    for (auto row : initial) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }

    solve(initial);
    return 0;
}

// int main() {
//     vector<vector<int>> initial = {
//         {0, 1, 2},
//         {4, 6, 3},
//         {7, 5, 8}
//     };
//     solve(initial);
//     return 0;
// }


/*
Enter the initial state of the puzzle (0 represents the empty tile):
Enter value at position (0, 0): 0
Enter value at position (0, 1): 1
Enter value at position (0, 2): 2
Enter value at position (1, 0): 4
Enter value at position (1, 1): 6
Enter value at position (1, 2): 3
Enter value at position (2, 0): 7
Enter value at position (2, 1): 5
Enter value at position (2, 2): 8
Enter the final state of the puzzle (0 represents the empty tile):
Enter value at position (0, 0): 1
Enter value at position (0, 1): 2
Enter value at position (0, 2): 3
Enter value at position (1, 0): 4
Enter value at position (1, 1): 5
Enter value at position (1, 2): 6
Enter value at position (2, 0): 7
Enter value at position (2, 1): 8
Enter value at position (2, 2): 0
Initial State:
0 1 2
4 6 3
7 5 8
-----
Current State:
0 1 2
4 6 3
7 5 8
-----
Number of moves: 0
Heuristic cost: 6
-------------------
Current State:
1 0 2
4 6 3
7 5 8
-----
Number of moves: 1
Heuristic cost: 5
-------------------
Current State:
1 2 0
4 6 3
7 5 8
-----
Number of moves: 2
Heuristic cost: 4
-------------------
Current State:
1 2 3
4 6 0
7 5 8
-----
Number of moves: 3
Heuristic cost: 3
-------------------
Current State:
1 2 3
4 0 6
7 5 8
-----
Number of moves: 4
Heuristic cost: 2
-------------------
Current State:
1 2 3
4 5 6
7 0 8
-----
Number of moves: 5
Heuristic cost: 1
-------------------
Current State:
1 2 3
4 5 6
7 8 0
-----
Number of moves: 6
Heuristic cost: 0
-------------------
Goal State Reached!
Number of moves: 6
Heuristic cost: 0
*/


// #include <iostream>
// #include <vector>
// #include <queue>
// #include <cmath>
// #include <algorithm>
// #include <unordered_set>
// #include <cstring>

// using namespace std;

// const int N = 3;

// class PuzzleState {
// private:
//     int puzzle[N][N];
//     int zeroRow, zeroCol;
//     int g;
//     int h;

// public:
//     PuzzleState() {
//         g = 0;
//         h = 0;
//         zeroRow = zeroCol = 0;
//         memset(puzzle, 0, sizeof(puzzle));
//     }

//     void input(const string &prompt) {
//         cout << prompt << " (0 represents the empty tile):\n";
//         for (int i = 0; i < N; i++) {
//             for (int j = 0; j < N; j++) {
//                 cout << "Enter value at position (" << i << ", " << j << "): ";
//                 cin >> puzzle[i][j];
//                 if (puzzle[i][j] == 0) {
//                     zeroRow = i;
//                     zeroCol = j;
//                 }
//             }
//         }
//         g = 0;
//         h = calculateManhattanDistance();
//     }

//     void print() const {
//         for (int i = 0; i < N; i++) {
//             for (int j = 0; j < N; j++) {
//                 cout << puzzle[i][j] << " ";
//             }
//             cout << endl;
//         }
//         cout << "-----\n";
//     }

//     bool isEqual(const PuzzleState &other) const {
//         for (int i = 0; i < N; i++)
//             for (int j = 0; j < N; j++)
//                 if (puzzle[i][j] != other.puzzle[i][j])
//                     return false;
//         return true;
//     }

//     int calculateManhattanDistance() const {
//         int distance = 0;
//         for (int i = 0; i < N; i++) {
//             for (int j = 0; j < N; j++) {
//                 int value = puzzle[i][j];
//                 if (value != 0) {
//                     int targetRow = (value - 1) / N;
//                     int targetCol = (value - 1) % N;
//                     distance += abs(i - targetRow) + abs(j - targetCol);
//                 }
//             }
//         }
//         return distance;
//     }

//     vector<PuzzleState> generateNextStates() const {
//         vector<PuzzleState> nextStates;
//         const int moves[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

//         for (int k = 0; k < 4; k++) {
//             int nextZeroRow = zeroRow + moves[k][0];
//             int nextZeroCol = zeroCol + moves[k][1];

//             if (nextZeroRow >= 0 && nextZeroRow < N && nextZeroCol >= 0 && nextZeroCol < N) {
//                 PuzzleState nextState = *this;
//                 swap(nextState.puzzle[zeroRow][zeroCol], nextState.puzzle[nextZeroRow][nextZeroCol]);
//                 nextState.zeroRow = nextZeroRow;
//                 nextState.zeroCol = nextZeroCol;
//                 nextState.g = g + 1;
//                 nextState.h = nextState.calculateManhattanDistance();
//                 nextStates.push_back(nextState);
//             }
//         }
//         return nextStates;
//     }

//     int getG() const { return g; }
//     int getH() const { return h; }
//     int getF() const { return g + h; }

//     int hashCode() const {
//         int hash = 0;
//         for (int i = 0; i < N; i++)
//             for (int j = 0; j < N; j++)
//                 hash = hash * 10 + puzzle[i][j];
//         return hash;
//     }

//     bool operator<(const PuzzleState &other) const {
//         return (g + h) > (other.g + other.h);  // min-heap
//     }

//     friend void aStarSearch(const PuzzleState &initialState, const PuzzleState &finalState);
// };

// void aStarSearch(const PuzzleState &initialState, const PuzzleState &finalState) {
//     priority_queue<PuzzleState> pq;
//     unordered_set<int> visited;

//     pq.push(initialState);

//     while (!pq.empty()) {
//         PuzzleState current = pq.top();
//         pq.pop();

//         cout << "Current State:\n";
//         current.print();
//         cout << "g(n) - Cost so far: " << current.getG() << endl;
//         cout << "h(n) - Heuristic cost: " << current.getH() << endl;
//         cout << "f(n) = g(n) + h(n): " << current.getF() << endl;
//         cout << "-------------------\n";

//         if (current.isEqual(finalState)) {
//             cout << "Goal State Reached!\n";
//             cout << "Number of moves: " << current.getG() << endl;
//             cout << "Heuristic cost: " << current.getH() << endl;
//             break;
//         }

//         vector<PuzzleState> nextStates = current.generateNextStates();

//         for (const PuzzleState &nextState : nextStates) {
//             int hash = nextState.hashCode();
//             if (visited.find(hash) == visited.end()) {
//                 pq.push(nextState);
//                 visited.insert(hash);
//             }
//         }
//     }
// }

// int main() {
//     PuzzleState initialState, finalState;
//     initialState.input("Enter the initial state of the puzzle");
//     finalState.input("Enter the final state of the puzzle");

//     cout << "Initial State:\n";
//     initialState.print();

//     aStarSearch(initialState, finalState);

//     return 0;
// }

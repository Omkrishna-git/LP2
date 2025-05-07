#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;

const int ROOM_WIDTH = 10;
const int ROOM_HEIGHT = 10;

map<string, pair<int, int>> objects = {
    {"R1", {3, 2}},
    {"R2", {2, 4}},
    {"R3", {1, 5}},
    {"R4", {4, 1}},
    {"R5", {3, 4}},
    {"S1", {2, 2}},
    {"S2", {3, 3}},
    {"S3", {5, 5}},
    {"S4", {4, 4}}
};

int heuristic(const vector<string>& remaining_objs) {
    int total = 0;
    for (const auto& obj : remaining_objs) {
        total += objects[obj].first * objects[obj].second;
    }
    return total;
}

bool can_place(const vector<vector<int>>& room, int x, int y, int w, int h) {
    if (x + w > ROOM_WIDTH || y + h > ROOM_HEIGHT)
        return false;
    for (int i = x; i < x + w; ++i) {
        for (int j = y; j < y + h; ++j) {
            if (room[j][i] != 0)
                return false;
        }
    }
    return true;
}

void place(vector<vector<int>>& room, int x, int y, int w, int h, int val) {
    for (int i = x; i < x + w; ++i) {
        for (int j = y; j < y + h; ++j) {
            room[j][i] = val;
        }
    }
}

vector<vector<int>> clone_room(const vector<vector<int>>& room) {
    return room;
}

struct State {
    int f, g;
    vector<string> remaining;
    vector<vector<int>> room;
    vector<tuple<string, int, int>> placed;

    bool operator>(const State& other) const {
        return f > other.f;
    }
};

pair<vector<vector<int>>, vector<tuple<string, int, int>>> a_star_placement() {
    vector<vector<int>> start_room(ROOM_HEIGHT, vector<int>(ROOM_WIDTH, 0));
    vector<string> all_keys;
    for (const auto& kv : objects) {
        all_keys.push_back(kv.first);
    }

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({heuristic(all_keys), 0, all_keys, start_room, {}});

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        int h_val = current.f - current.g;

        cout << "f(n): " << current.f << ", g(n): " << current.g << ", h(n): " << h_val
             << ", placed: " << current.placed.size()  << endl;

        if (current.remaining.empty()) {
            return make_pair(current.room, current.placed);
        }

        for (const auto& obj : current.remaining) {
            int w = objects[obj].first;
            int h = objects[obj].second;
            for (int y = 0; y < ROOM_HEIGHT; ++y) {
                for (int x = 0; x < ROOM_WIDTH; ++x) {
                    if (can_place(current.room, x, y, w, h)) {
                        auto new_room = clone_room(current.room);
                        place(new_room, x, y, w, h, current.placed.size() + 1);

                        vector<string> new_remaining = current.remaining;
                        new_remaining.erase(remove(new_remaining.begin(), new_remaining.end(), obj), new_remaining.end());

                        vector<tuple<string, int, int>> new_placed = current.placed;
                        new_placed.push_back(make_tuple(obj, x, y));

                        int g_new = current.g + 1;
                        int h_new = heuristic(new_remaining);
                        int f_new = g_new + h_new;

                        pq.push({f_new, g_new, new_remaining, new_room, new_placed});
                        goto next_object;
                    }
                }
            }
        next_object:;
        }
    }

    return make_pair(vector<vector<int>>(), vector<tuple<string, int, int>>());
}

int main() {
    pair<vector<vector<int>>, vector<tuple<string, int, int>>> result = a_star_placement();
    vector<vector<int>> final_room = result.first;
    vector<tuple<string, int, int>> placed = result.second;

    if (!placed.empty()) {
        cout << "\nFinal placement:\n";
        for (size_t i = 0; i < placed.size(); ++i) {
            string obj;
            int x, y;
            tie(obj, x, y) = placed[i];
            cout<<i+1<<" -> ";
            cout << obj << " at (" << x << ", " << y << ")\n";
        }

        cout << "\nFinal room layout:\n";
        for (const auto& row : final_room) {
            for (int cell : row) {
                if (cell == 0)
                    cout << "* ";
                else
                    cout << cell << " ";
            }
            cout << "\n";
        }

    } else {
        cout << "No valid arrangement found.\n";
    }

    return 0;
}




// Problem Summary

// - Goal: Arrange 5 rectangular and 4 square-shaped objects efficiently into a 9x9 room grid.
// - Objects: Each has fixed width and height.
// - Constraints: Objects must not overlap or extend beyond room boundaries.
// - Approach: Use A* (A-Star) search algorithm to explore and find an optimal arrangement.

// A* Search Overview

// A* is a best-first search algorithm that finds the least-cost path using:

// f(n) = g(n) + h(n)

// - g(n): Cost from the start node to the current node.
// - h(n): Estimated cost from current node to goal (heuristic).
// - f(n): Total estimated cost of the cheapest solution through the current node.

// Heuristic Function h(n)

// In this problem, we want to place all objects efficiently. So we define:

// h(n): Total area of all unplaced objects.

// int heuristic(const vector<string>& remaining_objs) {
//     int total = 0;
//     for (const auto& obj : remaining_objs) {
//         total += objects[obj].first * objects[obj].second;
//     }
//     return total;
// }

// - It estimates how much space will still be needed (remaining area).
// - The lower the remaining area, the closer we are to completion.
// - Simple, admissible (never overestimates), and monotonic (non-decreasing).

// Cost Function g(n)

// g(n): Number of objects placed so far (i.e., depth of the search path).

// - Every time we place an object, g(n) is incremented by 1.
// - Represents progress toward the goal.

// State Definition

// Each state in A* includes:

// struct State {
//     int f, g;
//     vector<string> remaining; // Objects not placed yet
//     vector<vector<int>> room; // Room layout (grid)
//     vector<tuple<string, int, int>> placed; // What has been placed and where
// };

// Room Representation

// The room is a 2D grid:

// vector<vector<int>> room(ROOM_HEIGHT, vector<int>(ROOM_WIDTH, 0));

// - 0: Empty space -> printed as '*'
// - >0: ID for an object placed in that cell.

// Object Placement

// can_place(room, x, y, w, h) checks if an object fits at a certain position:

// - Doesn’t go out of bounds.
// - Doesn’t overlap existing objects.

// place(room, x, y, w, h, id) writes the object's ID into the room grid.

// Main Algorithm Loop

// 1. Start with all objects unplaced, empty grid.
// 2. Push initial state into priority queue with f(n) = g(n) + h(n).
// 3. Loop while priority queue is not empty:
//    - Pop state with the lowest f(n) (most promising).
//    - If remaining is empty -> done (goal reached).
//    - For each remaining object:
//      - Try to place it in every possible (x, y) position.
//      - If it fits:
//        - Create a new state:
//          - Updated room
//          - Updated placed list
//          - One less object in remaining
//          - Recalculate g, h, and f
//        - Push new state into priority queue.
//        - Break after one successful placement (DFS-like behavior due to goto).

// Example of A* Flow

// Let’s say you have these remaining objects:

// remaining = ["R1", "R2", "S1", ...]

// The algorithm will:

// 1. Compute h(n) by summing all their areas.
// 2. Try placing "R1" at all possible grid positions.
// 3. Once it finds a valid spot:
//    - It places it.
//    - Creates new state with:
//      - updated g(n) = 1
//      - updated h(n) (minus area of "R1")
//      - updated room grid.
// 4. Pushes it into the queue for future expansion.

// ID System

// Each object gets a unique numeric ID in the room grid by its placement order:

// - First object placed -> ID = 1
// - Second -> 2
// - ...

// These are stored visually and help differentiate object placements.

// Why A* Works Here

// - It avoids blindly placing objects (like DFS).
// - Prioritizes placements that leave less area unfilled.
// - Ensures valid and efficient packing using a smart combination of cost so far (g) and estimate to goal (h).

// Summary of Key Calculations

// Component | Meaning                            | How It's Calculated
// --------- | ---------------------------------- | ----------------------
// g(n)      | Objects placed so far              | Incremented by 1 with each placement
// h(n)      | Estimated area of unplaced objects | Sum of width × height of remaining objects
// f(n)      | Priority score used in A* search   | f(n) = g(n) + h(n)
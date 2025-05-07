#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <functional>

using namespace std;

// Structure to represent an object
struct Object {
    int id;         // Unique identifier
    int width;
    int height;
    int x;          // Placement position x
    int y;          // Placement position y
    bool rotated;   // Whether the object is rotated (width and height swapped)
    bool isPlaced;
    
    Object(int id, int w, int h) : id(id), width(w), height(h), x(-1), y(-1), rotated(false), isPlaced(false) {}
    
    // Get area of the object
    int area() const { return width * height; }
    
    // Rotate the object (swap width and height)
    void rotate() {
        swap(width, height);
        rotated = !rotated;
    }
};

// Structure to represent the room
struct Room {
    int width;
    int height;
    vector<vector<bool>> grid; // Grid to track occupied spaces
    
    Room(int w, int h) : width(w), height(h) {
        grid.resize(height, vector<bool>(width, false));
    }
    
    // Check if a position is available for placement
    bool isAvailable(int x, int y, int objWidth, int objHeight) const {
        if (x + objWidth > width || y + objHeight > height) {
            return false;
        }
        
        for (int i = y; i < y + objHeight; ++i) {
            for (int j = x; j < x + objWidth; ++j) {
                if (grid[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    // Place an object at a position
    void placeObject(int x, int y, int objWidth, int objHeight) {
        for (int i = y; i < y + objHeight; ++i) {
            for (int j = x; j < x + objWidth; ++j) {
                grid[i][j] = true;
            }
        }
    }
    
    // Calculate remaining free area
    int freeArea() const {
        int count = 0;
        for (const auto& row : grid) {
            count += count_if(row.begin(), row.end(), [](bool val) { return !val; });
        }
        return count;
    }
};

// State representation for A* search
struct State {
    vector<Object> objects;
    Room room;
    int cost;
    int heuristicValue;
    
    State(const vector<Object>& objs, const Room& r, int c) 
        : objects(objs), room(r), cost(c) {
        heuristicValue = calculateHeuristic();
    }
    
    // Check if all objects are placed
    bool isGoal() const {
        return all_of(objects.begin(), objects.end(), [](const Object& obj) { return obj.isPlaced; });
    }
    
    // Calculate heuristic (remaining free area + unplaced objects area)
    int calculateHeuristic() const {
        int unplacedArea = 0;
        for (const auto& obj : objects) {
            if (!obj.isPlaced) {
                unplacedArea += obj.area();
            }
        }
        return max(room.freeArea(), unplacedArea);
    }
    
    // Generate successor states
    vector<State> getSuccessors() const {
        vector<State> successors;
        
        // Find the first unplaced object
        auto it = find_if(objects.begin(), objects.end(), [](const Object& obj) { return !obj.isPlaced; });
        if (it == objects.end()) return successors;
        
        Object nextObj = *it;
        int objIndex = distance(objects.begin(), it);
        
        // Try both orientations (original and rotated)
        for (int rotation = 0; rotation < 2; ++rotation) {
            if (rotation == 1) {
                nextObj.rotate();
            }
            
            // Find all possible positions in the room
            for (int y = 0; y <= room.height - nextObj.height; ++y) {
                for (int x = 0; x <= room.width - nextObj.width; ++x) {
                    if (room.isAvailable(x, y, nextObj.width, nextObj.height)) {
                        // Create new state with object placed at (x,y)
                        vector<Object> newObjects = objects;
                        Room newRoom = room;
                        
                        newObjects[objIndex].x = x;
                        newObjects[objIndex].y = y;
                        newObjects[objIndex].isPlaced = true;
                        newObjects[objIndex].rotated = (rotation == 1);
                        
                        newRoom.placeObject(x, y, nextObj.width, nextObj.height);
                        
                        // Cost is the remaining free area
                        int newCost = newRoom.freeArea();
                        
                        successors.emplace_back(newObjects, newRoom, newCost);
                    }
                }
            }
            
            if (nextObj.width == nextObj.height) break; // No need to rotate squares
        }
        
        return successors;
    }
    
    // For priority queue ordering
    bool operator<(const State& other) const {
        return (cost + heuristicValue) > (other.cost + other.heuristicValue);
    }
    
    // For visited states tracking
    size_t hash() const {
        size_t seed = 0;
        for (const auto& obj : objects) {
            if (obj.isPlaced) {
                seed ^= std::hash<int>()(obj.id) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                seed ^= std::hash<int>()(obj.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                seed ^= std::hash<int>()(obj.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                seed ^= std::hash<bool>()(obj.rotated) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }
        return seed;
    }
};

// A* algorithm implementation
vector<Object> aStarPlacement(Room room, vector<Object> objects) {
    priority_queue<State> frontier;
    unordered_set<size_t> visited;
    
    // Sort objects by area (largest first) for better placement
    sort(objects.begin(), objects.end(), [](const Object& a, const Object& b) {
        return a.area() > b.area();
    });
    
    // Assign unique IDs to objects
    for (int i = 0; i < objects.size(); ++i) {
        objects[i].id = i;
    }
    
    frontier.emplace(objects, room, 0);
    
    while (!frontier.empty()) {
        State current = frontier.top();
        frontier.pop();
        
        size_t currentHash = current.hash();
        if (visited.count(currentHash)) continue;
        visited.insert(currentHash);
        
        if (current.isGoal()) {
            return current.objects;
        }
        
        for (const auto& successor : current.getSuccessors()) {
            size_t succHash = successor.hash();
            if (visited.count(succHash) == 0) {
                frontier.push(successor);
            }
        }
    }
    
    return {}; // Return empty vector if no solution found
}

int main() {
    int roomWidth, roomHeight;
    int numRectangular, numSquare;
    
    // Get room dimensions from user
    cout << "Enter room width: ";
    cin >> roomWidth;
    cout << "Enter room height: ";
    cin >> roomHeight;
    
    Room room(roomWidth, roomHeight);
    
    // Get number of rectangular and square objects
    cout << "Enter number of rectangular objects: ";
    cin >> numRectangular;
    cout << "Enter number of square objects: ";
    cin >> numSquare;
    
    vector<Object> objects;
    int idCounter = 0;
    
    // Input rectangular objects
    cout << "\nEnter dimensions for rectangular objects (width height):\n";
    for (int i = 0; i < numRectangular; ++i) {
        int w, h;
        cout << "Rectangular object " << i+1 << ": ";
        cin >> w >> h;
        objects.emplace_back(idCounter++, w, h);
    }
    
    // Input square objects
    cout << "\nEnter dimensions for square objects (size):\n";
    for (int i = 0; i < numSquare; ++i) {
        int size;
        cout << "Square object " << i+1 << ": ";
        cin >> size;
        objects.emplace_back(idCounter++, size, size);
    }
    
    vector<Object> placedObjects = aStarPlacement(room, objects);
    
    if (placedObjects.empty()) {
        cout << "\nNo valid placement found for all objects.\n";
    } else {
        cout << "\nOptimal object placement:\n";
        cout << "Room dimensions: " << room.width << "x" << room.height << "\n\n";
        
        for (const auto& obj : placedObjects) {
            if (obj.isPlaced) {
                cout << "Object " << obj.id << ": Size " << obj.width << "x" << obj.height;
                if (obj.rotated && obj.width != obj.height) cout << " (rotated)";
                cout << " placed at (" << obj.x << ", " << obj.y << ")\n";
            } else {
                cout << "Object " << obj.id << ": Size " << obj.width << "x" << obj.height << " NOT placed\n";
            }
        }
        
        // Calculate utilization
        int totalArea = room.width * room.height;
        int usedArea = 0;
        for (const auto& obj : placedObjects) {
            if (obj.isPlaced) {
                usedArea += obj.area();
            }
        }
        double utilization = (usedArea * 100.0) / totalArea;
        
        cout << "\nSpace utilization: " << utilization << "%\n";
    }
    
    return 0;
}
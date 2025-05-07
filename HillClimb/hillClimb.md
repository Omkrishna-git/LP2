Great! Let’s break down the **complete theory** and **explanation** of how the **Hill Climbing algorithm** works in this Sudoku solver — including how we compute `h(n)`, `g(n)`, how values are filled, and how the code navigates toward the solution.

---

## ✅ Hill Climbing for Sudoku – Full Theory & Code Breakdown

---

### 🔍 Problem Statement

We’re solving a **9x9 Sudoku puzzle** using **Hill Climbing**, a heuristic search algorithm. The goal is to fill all empty cells such that:

* Each **row**, **column**, and **3x3 box** contains the digits `1-9` **without repetition**.

---

## 🧠 Heuristic Approach – Hill Climbing

Hill climbing:

* **Starts with a complete but suboptimal solution**.
* Moves to **neighboring solutions** that are better based on a **heuristic** (`h(n)`).
* Stops if:

  * A solution is found (`h(n) = 0`)
  * Or no better neighbor exists (local optimum).

---

## 📊 Key Definitions

### 1. `h(n)` – Heuristic Function

Represents the **number of conflicts** in the Sudoku board:

* A **conflict** is counted when the same number appears **more than once** in any **row** or **column**.

#### ✅ How it’s calculated:

```cpp
// For each row
for each row i:
    count how many times each number appears
    for each number:
        if count > 1 => conflicts += (count - 1)

// Same for columns
```

### 2. `g(n)` – Cost So Far (Step Counter)

In this context:

* `g(n)` is the **number of iterations or steps** taken so far.
* It increments every time we move to a better (lower conflict) board.

### 3. `f(n)` – Total Cost (Informational)

Here:

* `f(n) = g(n) + h(n)`
* Not actually used for decision-making (since hill climbing uses only `h(n)`), but printed for **monitoring**.

---

## ⚙️ How the Code Works – Step by Step

---

### **Step 1: Input Puzzle**

We start with a partially filled 9x9 grid. Zeros indicate empty cells.

---

### **Step 2: Initialization (`fillRandom`)**

Each **3x3 box** is filled randomly:

* Identify which cells in the box are **not fixed** (i.e., originally empty).
* Fill them randomly with the remaining numbers `1–9`, avoiding repetition **within the box only**.
* This guarantees that **each 3x3 box is valid** from the start.

> ❗ Important: Row/Column conflicts may still exist — that’s what we try to reduce using hill climbing.

---

### **Step 3: Heuristic Evaluation (`heuristic()`)**

Calculates total number of **row + column conflicts**.

* If a number appears more than once in a row or column, every extra occurrence adds to `h(n)`.

---

### **Step 4: Hill Climbing Loop**

#### 4.1 Loop Until:

* Max steps reached.
* Or `h(n) == 0` (solution found).

#### 4.2 For each 3x3 box:

* Find 2 non-fixed cells.
* Try swapping them to see if `h(n)` improves.
* Keep the swap **only if it reduces** conflicts.

Repeat this across all 9 boxes.

#### 4.3 If any improvement:

* Accept it, update `g(n)`, `h(n)`, `f(n)`, and print board.

Else:

* **No better neighbor found** → stuck at a **local minimum** → stop.

---

### **Step 5: Print g(n), h(n), f(n) and Board**

At every successful move:

* Print current values of:

  * `g(n)`: step number
  * `h(n)`: remaining conflicts
  * `f(n) = g(n) + h(n)`
* Show updated board visually.

---

## 🔁 Example Scenario:

Imagine this simplified situation:

* Initial board has 20 conflicts → `h(n) = 20`, `g(n) = 0`
* We swap two numbers inside a box → new board has 18 conflicts → we **accept the swap**
* Now: `g(n) = 1`, `h(n) = 18`, `f(n) = 19`
* Repeat...

Eventually:

* If we reach `h(n) = 0`, solution is found.
* If no better swap is found, we stop (local minimum).

---

## 💡 Why Use Box-Only Swapping?

Because:

* The initial box is **valid** (contains 1–9)
* Swapping inside the box keeps it valid.
* We're minimizing **row/column** conflicts only, not breaking boxes.

---

## ❗ Limitations of Hill Climbing

* **Local optima**: May get stuck with no better neighbor.
* **No backtracking**: Doesn’t remember past states or explore worse options.
* **No randomness to escape traps**.

🛠️ Can be improved using:

* **Random restart hill climbing**
* **Simulated annealing**
* **Genetic algorithms**

---

## ✅ Summary

| Term   | Meaning                                      |
| ------ | -------------------------------------------- |
| `g(n)` | Steps taken (number of moves made)           |
| `h(n)` | Conflicts in rows and columns                |
| `f(n)` | Informational total: `g(n) + h(n)`           |
| Move   | Swapping 2 non-fixed values inside a 3x3 box |
| Goal   | `h(n) = 0` (valid board)                     |

---

Would you like a visual diagram or animation of this process (e.g., swap visualization or conflict heatmap)?

# Assignment-1-Programming-Fundamentals
## ONE PIECE - Arc Water 7 - Enies Lobby (Part 1)

<p align="center">
  <img src="https://img.shields.io/badge/C++-11-blue?logo=c%2B%2B" />
  <img src="https://img.shields.io/badge/Concepts-Algorithms%20%7C%20Simulation-lightgrey" />
  <img src="https://img.shields.io/badge/Status-Completed-brightgreen" />
</p>

---

## Overview

This project is a multi-module C++ program that simulates key events from the Water 7 – Enies Lobby arc.

The program integrates multiple programming concepts into a single system, including:

* File input/output processing
* Mathematical evaluation
* Simulation logic
* Subset optimization
* String decoding
* Grid-based pathfinding

The assignment is designed to reinforce core programming concepts such as loops, conditionals, arrays, functions, and structured problem solving. 

---

## Project Structure

```text
.
├── main.cpp
├── main.h
├── water_seven.cpp
├── water_seven.h
├── run.sh
├── opw_tc_01_input
├── output/
│   └── main
└── README.md
```

---

## Core Modules

### Task 0 – Input Processing

* Reads structured data from file
* Normalizes values within valid ranges
* Handles duplicate character entries

---

### Task 1 – Damage Evaluation

* Checks:

  * shipHP < 455
  * digit sum is a perfect number
* Increases repair cost by 50% if both conditions are satisfied

---

### Task 2 – Conflict Simulation

```text
conflictIndex = skill_Luffy − skill_Usopp + repairCost/100 + (500 − shipHP)/50
```

* Applies event-based updates
* Stops when:

  * conflictIndex ≥ 255
  * or 10 iterations reached

---

### Task 3 – Duel Resolution

* Selects optimal subset of crew members
* Objective:

  * minimize total cost
  * minimize number of members
  * prioritize smaller index
* Uses brute-force subset enumeration (2^n)

---

### Task 4 – Message Decoding

Processing pipeline:

1. Checksum validation
2. Block-wise reversal
3. Reverse Caesar cipher
4. Keyword validation:

   * CP9
   * ENIESLOBBY

---

### Task 5 – Grid Analysis

#### Danger Limit

```text
dangerLimit = maxRowSum + maxCell
```

#### Pathfinding

* Movement allowed:

  * Right
  * Down
* Uses dynamic programming
* Computes minimum danger path

---

## Requirements

* C++11 compatible compiler
* Only standard libraries provided in the assignment

Constraint:

* Only one `#include` per file is allowed 

---

## How to Run

### Compile

```bash
g++ -o main main.cpp water_seven.cpp -I . -std=c++11
```

### Run

```bash
./main opw_tc_01_input
```

Or using script:

```bash
bash run.sh
```

---

## Input Format

```text
<NAME> <HP> <SKILL>
...
GOING_MERRY <SHIPHP> <REPAIRCOST>
```

Constraints:

* Exactly 7 characters
* Values are clamped within allowed ranges

---

## Key Algorithms

* File parsing and validation
* Perfect number detection
* Iterative simulation
* Bitmask subset enumeration
* String transformation and cipher decoding
* Dynamic programming (grid path)

---

## Complexity

| Module              | Complexity     |
| ------------------- | -------------- |
| Input processing    | O(n)           |
| Conflict simulation | O(1)           |
| Subset selection    | O(2^n)         |
| String decoding     | O(n)           |
| Grid pathfinding    | O(rows × cols) |

---

## Limitations

* Fixed-size arrays
* Brute-force subset approach
* Limited input validation
* Console-based program

---

## Author

Hắc Minh Quân
Student ID: 2550201

---

## License

MIT License

---

## Notes

This project demonstrates the ability to:

* Translate complex specifications into code
* Combine multiple algorithmic techniques
* Structure a multi-stage program clearly

---

# Assignment-1-Programming-Fundamentals
## ONE PIECE - Arc Water 7 - Enies Lobby (Part 1)

<p align="center">
  <img src="https://img.shields.io/badge/C++-11-blue?logo=c%2B%2B" />
  <img src="https://img.shields.io/badge/Focus-Algorithms%20%7C%20Simulation-lightgrey" />
  <img src="https://img.shields.io/badge/Status-Completed-brightgreen" />
</p>

---

## Overview

This project is a multi-module C++ program that simulates key events from the *Water 7 – Enies Lobby* arc using algorithmic problem-solving techniques.

It combines:

* File processing
* Mathematical modeling
* Simulation logic
* Subset optimization
* String decoding
* Grid-based pathfinding

The assignment is designed to apply core programming concepts including arrays, loops, conditionals, functions, and file I/O. 

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

## Important Notes About Files

Some files in this repository are **generated artifacts**:

* `main` → compiled executable
* `main.dSYM` → debug symbols (macOS)
* `output/` → runtime outputs

These **should NOT be committed** in a clean project.

Recommended `.gitignore`:

```bash
main
*.dSYM
output/
```

---

## Core Modules

### Task 0 – Input Processing

* Reads data from file
* Normalizes values within constraints
* Handles duplicate character updates

---

### Task 1 – Damage Evaluation

* Checks:

  * shipHP < 455
  * digit sum is a perfect number
* Adjusts repair cost accordingly

---

### Task 2 – Conflict Simulation

* Computes conflict index:

```text
conflictIndex = skill_Luffy − skill_Usopp + repairCost/100 + (500 − shipHP)/50
```

* Applies iterative event updates until threshold reached

---

### Task 3 – Duel Resolution

* Solves subset selection problem:

  * maximize support
  * minimize cost
* Uses brute-force (2^n)

---

### Task 4 – Message Decoding

Pipeline:

1. Checksum validation
2. Block-wise reversal
3. Reverse Caesar cipher
4. Keyword validation (`CP9`, `ENIESLOBBY`)

---

### Task 5 – Grid Analysis

#### Danger Limit

```text
dangerLimit = maxRowSum + maxCell
```

#### Pathfinding

* Movement: right, down
* Uses dynamic programming
* Finds minimum danger path

---

## Requirements

* C++11 compiler
* No additional libraries allowed beyond provided headers

Strict constraint from assignment:

* Only one `#include` per file 

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

Or use script:

```bash
bash run.sh
```

---

## Example Input

```text
LUFFY 120 95
ZORO 110 90
...
GOING_MERRY 320 1500
```

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

| Module           | Complexity     |
| ---------------- | -------------- |
| Input parsing    | O(n)           |
| Simulation       | O(1)           |
| Subset selection | O(2^n)         |
| String decoding  | O(n)           |
| Grid path        | O(rows × cols) |

---

## Limitations

* Fixed-size arrays (not scalable)
* Brute-force subset approach
* No exception handling for invalid files
* Console-based only

---

## Author

Hắc Minh Quân
Student ID: 2550201

---

## License

MIT License

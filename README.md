# AVL Tree Implementation

This project provides a straightforward C++ implementation of an AVL (Adelson-Velsky and Landis) self-balancing binary search tree. It includes the tree class definition, supporting rotation logic, and a sample `main` program that demonstrates basic operations.

## Features
- Insert and delete nodes while maintaining AVL balance invariants.
- Automatic height updates and rebalancing rotations.
- In-order traversal helper to visualize sorted output.
- Header (`AVL.h`) and source (`AVL.cpp`) separation for ease of reuse.

## Building
```bash
cmake -S . -B build
cmake --build build
```

Alternatively, compile the sources directly with `g++`:
```bash
g++ -std=c++17 -O2 main.cpp AVL.cpp -o avl
```

## Running
After building, run the executable to see insertion and traversal examples:
```bash
./avl
```

## Project Structure
- `AVL.h` – Class declarations for AVL nodes and tree operations.
- `AVL.cpp` – Implementation of AVL tree member functions.
- `main.cpp` – Example usage of the AVL tree.
- `README.md` – Project overview and setup instructions.

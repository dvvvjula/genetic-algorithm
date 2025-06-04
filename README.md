# 🧬 Sudoku Solver with Genetic Algorithm

This project implements a Sudoku solver using a genetic algorithm. It supports different board sizes and allows experimenting with various genetic operators.

![c](https://github.com/user-attachments/assets/9c6e1c3b-de8d-4db8-b797-6d469fc3b238)


## 📦 Features

- Solves Sudoku puzzles of size **4x4**, **9x9**, and **16x16**
- Implements three selection methods:
  - 🎯 Roulette Selection
  - 🏆 Tournament Selection
  - 📈 Rank Selection
- Supports two crossover methods:
  - 🔁 One-Point Crossover
  - 🔀 Two-Point Crossover
- Includes two mutation methods:
  - ♻️ Inversion Mutation
  - 🎲 Random Reset Mutation

## 🚀 How to Run

1. Compile the program:

   ```bash
   gcc -o sudoku_solver main.c genetic.c utils.c -lm

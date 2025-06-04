# Sudoku Solver with Genetic Algorithm
This project implements a Sudoku solver using a genetic algorithm. It supports different Sudoku board sizes: 4x4, 9x9, and 16x16. The program provides detailed console output describing the algorithm’s operations, such as crossover, mutation, and selection.

![c](https://github.com/user-attachments/assets/9c6e1c3b-de8d-4db8-b797-6d469fc3b238)


### Features
- Solve Sudoku puzzles of sizes 4x4, 9x9, and 16x16.
- Three selection methods for parents: Roulette Wheel, Tournament, and Rank selection.
- Detailed console output:
  - Crossover description (random mask, parents, child) is printed only in the 1st and last generation.
  - Fitness and partial solution prints every 10th generation.
- Mutation introduces diversity with a small probability.
- Stops early if solution is found.

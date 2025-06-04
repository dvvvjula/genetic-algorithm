#ifndef SUDOKU_H
#define SUDOKU_H

int **allocateSudoku(int size);
void generateSudoku(int **sudoku, int size);
void printSudoku(int **sudoku, int size);
void printSudokuFlat(int *genes, int size);
void freeSudoku(int **sudoku, int size);

#endif

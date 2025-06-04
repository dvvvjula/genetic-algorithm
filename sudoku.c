#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

// allocate memory for a 2d sudoku grid of given size
int **allocateSudoku(int size)
{
    int **sudoku = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        sudoku[i] = calloc(size, sizeof(int)); // initialize each row with zeros
    return sudoku;
}

// initialize sudoku grid with zeros (empty puzzle)
void generateSudoku(int **sudoku, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            sudoku[i][j] = 0; // set all cells to empty
}

// print sudoku grid in 2d format
void printSudoku(int **sudoku, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf("%2d ", sudoku[i][j]);
        printf("\n");
    }
}

// print sudoku represented as a flat array (1d genes array)
void printSudokuFlat(int *genes, int size)
{
    for (int i = 0; i < size * size; i++)
    {
        printf("%2d ", genes[i]);
        if ((i + 1) % size == 0)
            printf("\n"); // new line after each row
    }
}

// free allocated memory for sudoku grid
void freeSudoku(int **sudoku, int size)
{
    for (int i = 0; i < size; i++)
        free(sudoku[i]); // free each row
    free(sudoku);        // free row pointers array
}

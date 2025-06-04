#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

// allocate memory for sudoku grid
int **allocateSudoku(int size)
{
    int **sudoku = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
        sudoku[i] = calloc(size, sizeof(int));
    return sudoku;
}

// initialize sudoku grid with zeros (empty puzzle)
void generateSudoku(int **sudoku, int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            sudoku[i][j] = 0;
}

// print sudoku grid in matrix form
void printSudoku(int **sudoku, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf("%2d ", sudoku[i][j]);
        printf("\n");
    }
}

// print sudoku genes in flat array form
void printSudokuFlat(int *genes, int size)
{
    for (int i = 0; i < size * size; i++)
    {
        printf("%2d ", genes[i]);
        if ((i + 1) % size == 0)
            printf("\n");
    }
}

// free allocated memory for sudoku grid
void freeSudoku(int **sudoku, int size)
{
    for (int i = 0; i < size; i++)
        free(sudoku[i]);
    free(sudoku);
}

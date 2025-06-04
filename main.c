#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "genetic.h"
#include "sudoku.h"

int main()
{
    srand((unsigned int)time(NULL));

    int size;
    printf("Choose Sudoku size (4 for 4x4, 9 for 9x9, 16 for 16x16): ");
    scanf("%d", &size);

    int **sudoku = allocateSudoku(size);
    generateSudoku(sudoku, size);

    printf("\nInitial Sudoku Puzzle:\n");
    printSudoku(sudoku, size);

    printf("\nSolving using Roulette Selection:\n");
    solveWithGenetic(sudoku, size, ROULETTE);

    printf("\nSolving using Tournament Selection:\n");
    solveWithGenetic(sudoku, size, TOURNAMENT);

    printf("\nSolving using Rank Selection:\n");
    solveWithGenetic(sudoku, size, RANK);

    freeSudoku(sudoku, size);
    return 0;
}

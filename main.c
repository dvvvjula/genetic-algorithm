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

    printf("\nSolving using roulette selection:\n");
    solveWithGenetic(sudoku, size, ROULETTE, 1, 1); // one-point crossover, inversion mutation

    printf("\nSolving using tournament selection:\n");
    solveWithGenetic(sudoku, size, TOURNAMENT, 2, 2); // two-point crossover, random reset mutation

    printf("\nSolving using rank selection:\n");
    solveWithGenetic(sudoku, size, RANK, 1, 2); // one-point crossover, random reset mutation

    freeSudoku(sudoku, size);
    return 0;
}

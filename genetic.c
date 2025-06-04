#include <stdio.h>
#include <stdlib.h>
#include "genetic.h"
#include "sudoku.h"

int getFitness(int *genes, int size);
void mutate(int *genes, int size);
void crossover(int *parent1, int *parent2, int *child, int size, int generation, int index, int selectionMethod);
Individual *selectParent(Population *population, int method, int size);
int compareFitness(const void *a, const void *b);
int isSolved(int *genes, int size);

void solveWithGenetic(int **puzzle, int size, int selectionMethod)
{
    // for later
}

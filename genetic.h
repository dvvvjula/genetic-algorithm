#ifndef GENETIC_H
#define GENETIC_H

#define ROULETTE 0
#define TOURNAMENT 1
#define RANK 2

#define POPULATION_SIZE 50
#define GENERATIONS 100
#define MUTATION_RATE 0.05

typedef struct
{
    int *genes;
    int fitness;
} Individual;

typedef struct
{
    Individual **individuals;
} Population;

void solveWithGenetic(int **puzzle, int size, int selectionMethod);

#endif
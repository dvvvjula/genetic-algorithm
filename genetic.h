#ifndef GENETIC_H
#define GENETIC_H

#define ROULETTE 0
#define TOURNAMENT 1
#define RANK 2

#define CROSSOVER_UNIFORM 0
#define CROSSOVER_ONE_POINT 1
#define CROSSOVER_TWO_POINT 2

#define MUTATION_SWAP 0
#define MUTATION_INVERSION 1
#define MUTATION_RANDOM_RESET 2

void solveWithGenetic(int **puzzle, int size, int selectionMethod, int crossoverMethod, int mutationMethod);
void crossoverOnePoint(int *p1, int *p2, int *child, int length);
void crossoverTwoPoint(int *p1, int *p2, int *child, int length);
void mutateInversion(int *genes, int size);
void mutateRandomReset(int *genes, int size);

#endif
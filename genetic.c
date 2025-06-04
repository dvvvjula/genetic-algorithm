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
    int chromosomeLength = size * size;
    Population *population = malloc(sizeof(Population));
    population->individuals = malloc(sizeof(Individual *) * POPULATION_SIZE);

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        population->individuals[i] = malloc(sizeof(Individual));
        population->individuals[i]->genes = malloc(sizeof(int) * chromosomeLength);
        for (int j = 0; j < chromosomeLength; j++)
        {
            population->individuals[i]->genes[j] = puzzle[j / size][j % size];
            if (population->individuals[i]->genes[j] == 0)
                population->individuals[i]->genes[j] = (rand() % size) + 1;
        }
        population->individuals[i]->fitness = getFitness(population->individuals[i]->genes, size);
    }
}

int getFitness(int *genes, int size)
{
    int fitness = 0;

    for (int i = 0; i < size; i++)
    {
        int *row = calloc(size + 1, sizeof(int));
        int *col = calloc(size + 1, sizeof(int));
        for (int j = 0; j < size; j++)
        {
            row[genes[i * size + j]]++;
            col[genes[j * size + i]]++;
        }
        for (int k = 1; k <= size; k++)
        {
            if (row[k] == 1)
                fitness++;
            if (col[k] == 1)
                fitness++;
        }
        free(row);
        free(col);
    }
    return fitness;
}

void mutate(int *genes, int size)
{
    int i = rand() % (size * size);
    int j = rand() % (size * size);
    int temp = genes[i];
    genes[i] = genes[j];
    genes[j] = temp;
}

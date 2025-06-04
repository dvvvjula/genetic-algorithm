#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genetic.h"
#include "sudoku.h"

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

// calculate fitness score based on number of unique numbers in rows and columns
int getFitness(int *genes, int size);

// randomly mutate genes by swapping two positions
void mutate(int *genes, int size);

// perform crossover between two parents producing a child; print details on 1st and last generation
void crossover(int *parent1, int *parent2, int *child, int size, int generation, int index, int selectionMethod);

// create a copy of genes array
int *copyGenes(int *genes, int size);

// select a parent individual from population based on selection method
Individual *selectParent(Population *population, int method, int size);

// comparison function for qsort to sort individuals by fitness descending
int compareFitness(const void *a, const void *b);

// check if sudoku solution is complete and correct
int isSolved(int *genes, int size);

void solveWithGenetic(int **puzzle, int size, int selectionMethod)
{
    int chromosomeLength = size * size;
    Population *population = malloc(sizeof(Population));
    population->individuals = malloc(sizeof(Individual *) * POPULATION_SIZE);

    // initialize population with puzzle values or random numbers
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        population->individuals[i] = malloc(sizeof(Individual));
        population->individuals[i]->genes = malloc(sizeof(int) * chromosomeLength);
        for (int j = 0; j < chromosomeLength; j++)
        {
            population->individuals[i]->genes[j] = puzzle[j / size][j % size];
            if (population->individuals[i]->genes[j] == 0)
                population->individuals[i]->genes[j] = (rand() % size) + 1; // random gene if empty
        }
        population->individuals[i]->fitness = getFitness(population->individuals[i]->genes, size);
    }

    const char *methodName;

    if (selectionMethod == ROULETTE)
    {
        methodName = "ROULETTE";
    }
    else if (selectionMethod == TOURNAMENT)
    {
        methodName = "TOURNAMENT";
    }
    else
    {
        methodName = "RANK";
    }

    printf("\n=== Starting Genetic Algorithm with %s Selection ===\n", methodName);

    for (int gen = 1; gen <= GENERATIONS; gen++)
    {
        Population *newPop = malloc(sizeof(Population));
        newPop->individuals = malloc(sizeof(Individual *) * POPULATION_SIZE);

        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            // select two parents based on selection method
            Individual *parent1 = selectParent(population, selectionMethod, size);
            Individual *parent2 = selectParent(population, selectionMethod, size);

            newPop->individuals[i] = malloc(sizeof(Individual));
            newPop->individuals[i]->genes = malloc(sizeof(int) * chromosomeLength);

            // perform crossover with detailed print on 1st and last generation only
            if (gen == 1 || gen == GENERATIONS)
            {
                crossover(parent1->genes, parent2->genes, newPop->individuals[i]->genes, size, gen, i, selectionMethod);
            }
            else
            {
                // simple crossover without print: randomly select gene from either parent
                for (int k = 0; k < chromosomeLength; k++)
                {
                    int choose = rand() % 2;
                    if (choose == 1)
                        newPop->individuals[i]->genes[k] = parent1->genes[k];
                    else
                        newPop->individuals[i]->genes[k] = parent2->genes[k];
                }
            }

            // mutate child with some probability
            if ((rand() / (double)RAND_MAX) < MUTATION_RATE)
            {
                mutate(newPop->individuals[i]->genes, size);
            }

            // calculate fitness for child
            newPop->individuals[i]->fitness = getFitness(newPop->individuals[i]->genes, size);
        }

        // print best individual summary on 1st, every 10th, and last generation
        if (gen == 1 || gen % 10 == 0 || gen == GENERATIONS)
        {
            printf("\nGeneration %d best individual:\n", gen);
            printSudokuFlat(newPop->individuals[0]->genes, size);
            printf("Fitness: %d\n", newPop->individuals[0]->fitness);
        }

        // free old population memory
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            free(population->individuals[i]->genes);
            free(population->individuals[i]);
        }
        free(population->individuals);
        free(population);

        population = newPop;

        // stop if solution is found
        if (isSolved(population->individuals[0]->genes, size))
            break;
    }

    printf("\nFinal Sudoku solution with %s selection:\n", methodName);
    printSudokuFlat(population->individuals[0]->genes, size);

    // free final population memory
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        free(population->individuals[i]->genes);
        free(population->individuals[i]);
    }
    free(population->individuals);
    free(population);
}

int getFitness(int *genes, int size)
{
    int fitness = 0;

    // count unique values in each row and column
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

// swap two random genes to mutate individual
void mutate(int *genes, int size)
{
    int i = rand() % (size * size);
    int j = rand() % (size * size);
    int temp = genes[i];
    genes[i] = genes[j];
    genes[j] = temp;
}

// perform crossover with a random mask and print detailed info for debugging
void crossover(int *parent1, int *parent2, int *child, int size, int generation, int index, int selectionMethod)
{
    const char *methodName;

    if (selectionMethod == ROULETTE)
    {
        methodName = "ROULETTE";
    }
    else if (selectionMethod == TOURNAMENT)
    {
        methodName = "TOURNAMENT";
    }
    else
    {
        methodName = "RANK";
    }

    printf("\n[crossover] generation %d, individual %d, selection method: %s\n", generation, index, methodName);

    printf("parent 1: [");
    for (int i = 0; i < size * size; i++)
    {
        printf("%d", parent1[i]);
        if (i < size * size - 1)
            printf(" ");
    }
    printf("]\n");

    printf("parent 2: [");
    for (int i = 0; i < size * size; i++)
    {
        printf("%d", parent2[i]);
        if (i < size * size - 1)
            printf(" ");
    }
    printf("]\n");

    printf("random mask (0/1): [");
    for (int i = 0; i < size * size; i++)
    {
        int choose = rand() % 2;
        printf("%d", choose);
        if (choose == 1)
        {
            child[i] = parent1[i];
        }
        else
        {
            child[i] = parent2[i];
        }
        if (i < size * size - 1)
            printf(" ");
    }
    printf("]\n");

    printf("child:    [");
    for (int i = 0; i < size * size; i++)
    {
        printf("%d", child[i]);
        if (i < size * size - 1)
            printf(" ");
    }
    printf("]\n");
}

// select a parent based on selection method
Individual *selectParent(Population *population, int method, int size)
{
    if (method == ROULETTE)
    {
        int totalFitness = 0;
        for (int i = 0; i < POPULATION_SIZE; i++)
            totalFitness += population->individuals[i]->fitness;
        int r = rand() % totalFitness;
        int sum = 0;
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            sum += population->individuals[i]->fitness;
            if (sum >= r)
                return population->individuals[i];
        }
    }
    else if (method == TOURNAMENT)
    {
        int best = rand() % POPULATION_SIZE;
        for (int i = 0; i < 4; i++)
        {
            int challenger = rand() % POPULATION_SIZE;
            if (population->individuals[challenger]->fitness > population->individuals[best]->fitness)
                best = challenger;
        }
        return population->individuals[best];
    }
    else if (method == RANK)
    {
        // sort individuals by fitness descending
        qsort(population->individuals, POPULATION_SIZE, sizeof(Individual *), compareFitness);
        int r = rand() % (POPULATION_SIZE * (POPULATION_SIZE + 1) / 2);
        int sum = 0;
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            sum += POPULATION_SIZE - i;
            if (sum >= r)
                return population->individuals[i];
        }
    }
    // fallback return first individual
    return population->individuals[0];
}

// compare function for qsort to sort by fitness descending
int compareFitness(const void *a, const void *b)
{
    return (*(Individual **)b)->fitness - (*(Individual **)a)->fitness;
}

// check if sudoku is solved by verifying max fitness possible
int isSolved(int *genes, int size)
{
    return getFitness(genes, size) == size * 2 * size;
}

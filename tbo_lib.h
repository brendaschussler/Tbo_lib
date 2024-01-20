#ifndef TBO_LIB_H
#define TBO_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MEGA 1.0e-6
#define GIGA 1.0e-9
#define NUM_GENERATIONS 3
#define POPULATION_SIZE 30
#define MAX_NUM_THREADS 64
#define MAX_MULTIPLICATION 1024
#define TOURNAMENT_SIZE 2
#define MUTATION_Y_PROBABILITY 0.2
#define MUTATION_X_PROBABILITY 0.2

typedef struct
{
    int thread_x;
    int thread_y;
    double fitness;
} Individual;

typedef struct
{
    int bsize_x;
    int bsize_y;
} BlockSizes;

void initialize_rand();
void initializePopulation(Individual *population, int population_size);
int findBestIndex(Individual *population);
void selectionByTournament(Individual *population, Individual *parents);
int generateNewRandomValue();
void crossoverMutation(Individual *parents, Individual *children);
BlockSizes generateNewSubpopulation(Individual *population);
BlockSizes initialize();
BlockSizes genetic_exec(int it, double kernel_time);
BlockSizes before_kernel(int it, BlockSizes bsizes);

#endif


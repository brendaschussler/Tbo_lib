#include "tbo_lib.h"

int generation = 0;
Individual population[POPULATION_SIZE];

void initialize_rand()
{
    srand(time(NULL));
}

void initializePopulation(Individual *population, int population_size)
{
    int fixed_indexes[][2] = {{32, 4}, {64, 8}, {32, 16}, {64, 4}};
    int num_fixed_indexes = sizeof(fixed_indexes) / sizeof(fixed_indexes[0]);

    int current_population = 0;
    while (current_population < num_fixed_indexes)
    {
        int x = fixed_indexes[current_population][0];
        int y = fixed_indexes[current_population][1];
        if (x * y < MAX_MULTIPLICATION)
        {
            population[current_population].thread_x = x;
            population[current_population].thread_y = y;
            population[current_population].fitness = 0.0;
            current_population++;
        }
    }

    int vector_x[] = {2, 4, 8, 16, 32, 64};
    int vector_y[] = {2, 4, 8, 16, 32, 64};
    int size_vector_x = sizeof(vector_x) / sizeof(vector_x[0]);
    int size_vector_y = sizeof(vector_y) / sizeof(vector_y[0]);

    while (current_population < population_size)
    {
        int random_index_x = rand() % size_vector_x;
        int random_index_y = rand() % size_vector_y;

        int x = vector_x[random_index_x];
        int y = vector_y[random_index_y];
        if (x * y < MAX_MULTIPLICATION)
        {
            population[current_population].thread_x = x;
            population[current_population].thread_y = y;
            population[current_population].fitness = 0.0;
            current_population++;
        }
    }
}

int findBestIndex(Individual *population)
{
    int bestIndex = 0;
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        if (population[i].fitness > population[bestIndex].fitness)
        {
            bestIndex = i;
        }
    }
    return bestIndex;
}

void selectionByTournament(Individual *population, Individual *parents)
{
    for (int i = 0; i < 2; i++)
    {
        Individual winner = population[rand() % POPULATION_SIZE];

        for (int j = 1; j < TOURNAMENT_SIZE; j++)
        {
            Individual competitor = population[rand() % POPULATION_SIZE];
            if (competitor.fitness > winner.fitness)
            {
                winner = competitor;
            }
        }

        parents[i] = winner;
    }
}

int generateNewRandomValue()
{
    int vector[] = {2, 4, 8, 16, 32, 64};
    int vector_size = sizeof(vector) / sizeof(vector[0]);

    int random_index = rand() % vector_size;
    int random_value = vector[random_index];

    return random_value;
}

void crossoverMutation(Individual *parents, Individual *children)
{
    if ((parents[1].thread_y * parents[0].thread_x < 1024) && (parents[1].thread_x * parents[0].thread_y < 1024))
    {
        children[0].thread_x = parents[0].thread_x;
        children[0].thread_y = parents[1].thread_y;

        children[1].thread_x = parents[1].thread_x;
        children[1].thread_y = parents[0].thread_y;
    }
    else
    {
        children[0].thread_x = parents[0].thread_x;
        children[0].thread_y = parents[0].thread_y;
        children[1].thread_x = parents[1].thread_x;
        children[1].thread_y = parents[1].thread_y;
    }

    if ((double)rand() / RAND_MAX < MUTATION_Y_PROBABILITY)
    {
        int new_thread_y = generateNewRandomValue();

        while (new_thread_y * children[0].thread_x >= MAX_MULTIPLICATION)
        {
            new_thread_y = generateNewRandomValue();
        }

        children[0].thread_y = new_thread_y;
    }

    if ((double)rand() / RAND_MAX < MUTATION_X_PROBABILITY)
    {
        int new_thread_x = generateNewRandomValue();

        while (new_thread_x * children[0].thread_y >= MAX_MULTIPLICATION)
        {
            new_thread_x = generateNewRandomValue();
        }

        children[0].thread_x = new_thread_x;
    }
}

BlockSizes generateNewSubpopulation(Individual *population)
{
    Individual *newSubpopulation = (Individual *)malloc(POPULATION_SIZE * sizeof(Individual));

    int bestIndex = findBestIndex(population);
    newSubpopulation[0] = population[bestIndex];

    for (int i = 1; i < POPULATION_SIZE; i = i + 2)
    {
        Individual parents[2];
        selectionByTournament(population, parents);

        Individual children[2];
        crossoverMutation(parents, children);

        newSubpopulation[i] = children[0];
        newSubpopulation[i + 1] = children[1];
    }

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        population[i] = newSubpopulation[i];
    }

    free(newSubpopulation);

    BlockSizes blockSizes;
    blockSizes.bsize_x = population[0].thread_x;
    blockSizes.bsize_y = population[0].thread_y;

    return blockSizes;
}

BlockSizes initialize()
{
    initialize_rand();
    initializePopulation(population, POPULATION_SIZE);
    BlockSizes blockSizes;
    generation = 0;

    blockSizes.bsize_x = population[0].thread_x;
    blockSizes.bsize_y = population[0].thread_y;

    return blockSizes;
}

BlockSizes genetic_exec(int it, double kernel_time)
{
    BlockSizes blockSizes;
    int bestConfiguration = 0;

    if (it == 0)
    {
        population[0].fitness = 1 / kernel_time;
        blockSizes.bsize_x = population[it + 1 - (generation) * POPULATION_SIZE].thread_x;
        blockSizes.bsize_y = population[it + 1 - (generation) * POPULATION_SIZE].thread_y;
        return blockSizes;
    }
    else if (it % POPULATION_SIZE != 0 && it < POPULATION_SIZE * NUM_GENERATIONS)
    {
        population[it - (generation) * POPULATION_SIZE].fitness = 1 / kernel_time;
        blockSizes.bsize_x = population[it + 1 - (generation) * POPULATION_SIZE].thread_x;
        blockSizes.bsize_y = population[it + 1 - (generation) * POPULATION_SIZE].thread_y;
        return blockSizes;
    }
    else if (it > 0 && it % POPULATION_SIZE == 0 && it < POPULATION_SIZE * NUM_GENERATIONS)
    {
        generation++;
        population[0].fitness = 1 / kernel_time;
        blockSizes.bsize_x = population[it + 1 - (generation) * POPULATION_SIZE].thread_x;
        blockSizes.bsize_y = population[it + 1 - (generation) * POPULATION_SIZE].thread_y;
        return blockSizes;
    }
    else if (it == POPULATION_SIZE * NUM_GENERATIONS)
    {
        bestConfiguration = findBestIndex(population);
        blockSizes.bsize_x = population[bestConfiguration].thread_x;
        blockSizes.bsize_y = population[bestConfiguration].thread_y;
        return blockSizes;
    }
    else
    {
        blockSizes.bsize_x = population[bestConfiguration].thread_x;
        blockSizes.bsize_y = population[bestConfiguration].thread_y;
        return blockSizes;
    }
}

BlockSizes before_kernel(int it, BlockSizes bsizes)
{
    BlockSizes blockSizes;
    if (it == 0)
    {
        blockSizes = initialize();
        return blockSizes;
    }
    else if (it % POPULATION_SIZE == 0 && it <= POPULATION_SIZE * NUM_GENERATIONS)
    {
        blockSizes = generateNewSubpopulation(population);
        return blockSizes;
    }
    else
    {
        return bsizes;
    }
}

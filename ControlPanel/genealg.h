#ifndef GA_H
#define GA_H
#include "ialgorithm.h"

class Fitness;

// Belongs to GA, stores a individual's gene sequence
class Individual{
public:
    Individual();
    Individual(int sampleLength, Fitness* fit);
    void generateIndividual();
    void setGeneLength(int len);
    float getGene(int index);
    void setGene(int index, float value);
    int size();
    int getFit();
    Fitness* getChecker(){return fitnessCheck;}
private:
    float fit = 0;
    int geneLength = 0;
    QVector<float> sequence;
    Fitness* fitnessCheck;

};

// Population stores the individuals of a generation
class Population
{
public:
    Population(int sampleSize, int populationSize, bool initialized, Fitness * Fit);
    Individual getIndividual(int index);
    Individual getFittest();
    int size();
    void saveIndividual(int index, Individual indiv);
private:
    Fitness* fitnessCheck;
    QVector<Individual> individuals;
};

// The actual algorithm to be used
class Algorithm
{
public:
    Algorithm();
    Algorithm(double uniform, double mutation,
              int children, int sample, bool elite);
    Population evolvePopulation(Population parent);

private:
    double uniformRate = 0.5;
    double mutationRate = 0.015;
    int childPop = 5;
    int sampleSize = 0;
    bool elitism = true;

    Individual crossover(Individual indiv1, Individual indiv2);
    void mutate(Individual indiv);
    Individual childSelect(Population parent);
};

// Function to find the most fit solution
class Fitness
{
public:
    QVector<QVector<float> > * solution;

    Fitness() {}

    void setSolution(QVector<QVector<float> > * newSolution);
    int getFitness(Individual* in);
    int getMaxFitness();
};

// Uses the IAlgorithm interface
class GeneAlg : public IAlgorithm
{
public:
    GeneAlg();
    GeneAlg(AlgoSettings* settings);
    QVector<float> run(QVector<QVector<float> > input) override;
    void setOutputLength(double len);

private:
    double uniformRate;
    double mutationRate;
    int childPop;
    int generations;
    bool elitism;
    double outputLength = 10;
};

#endif // GA_H

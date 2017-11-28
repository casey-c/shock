#ifndef GA_H
#define GA_H
#include "ialgorithm.h"

// Belongs to GA, stores a individual's gene sequence
class Individual{
public:
    Individual();
    Individual(int sampleLength);
    void generateIndividual();
    void setGeneLength(int len);
    short getGene(int index);
    void setGene(int index, short value);
    int size();
    int getFit();
private:
    int fit = 0;
    int geneLength = 0;
    QVector<short> sequence;

};

// Population stores the individuals of a generation
class Population
{
public:
    Population(int sampleSize, int populationSize, bool initialized);
    Individual getIndividual(int index);
    Individual getFittest();
    int size();
    void saveIndividual(int index, Individual indiv);
private:
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
    QVector<QVector<short> > * solution;

    Fitness() {}

    void setSolution(QVector<QVector<short> > * newSolution);
    int getFitness(Individual* in);
    int getMaxFitness();
};

// Uses the IAlgorithm interface
class GeneAlg : public IAlgorithm
{
public:
    GeneAlg();
    GeneAlg(AlgoSettings* settings);
    QVector<short> run(QVector<QVector<short> > input) override;

private:
    double uniformRate;
    double mutationRate;
    int childPop;
    int sampleSize;
    bool elitism;
};

#endif // GA_H

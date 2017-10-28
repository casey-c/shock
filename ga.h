#ifndef GA_H
#define GA_H
#include <QVector>
#include "stdlib.h"

class Individual{
public:
    Individual();
    Individual(int sampleLength);
    void generateIndividual();
    void setGeneLength(int len);
    double getGene(int index);
    void setGene(int index, double value);
    int size();
    int getFit();
private:
    int fit = 0;
    int geneLength = 0;
    QVector<double> sequence;

};



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

class Fitness
{
public:
    QVector<double> solution;

    Fitness() {}

    void setSolution(QVector<double> newSolution);
    int getFitness(Individual* in);
    int getMaxFitness();
};



class GA
{
public:
    GA(QVector<QVector<double> > input);
};

#endif // GA_H

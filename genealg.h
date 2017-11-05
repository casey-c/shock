#ifndef GA_H
#define GA_H
#include <QVector>
#include "stdlib.h"
#include "ialgorithm.h"

class Individual{
public:
    Individual();
    Individual(int sampleLength);
    void generateIndividual();
    void setGeneLength(int len);
    float getGene(int index);
    void setGene(int index, float value);
    int size();
    int getFit();
private:
    int fit = 0;
    int geneLength = 0;
    QVector<float> sequence;

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
    Algorithm(float uniform, float mutation,
              int children, int sample, bool elite);
    Population evolvePopulation(Population parent);

private:
    float uniformRate = 0.5;
    float mutationRate = 0.015;
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
    QVector<float> solution;

    Fitness() {}

    void setSolution(QVector<float> newSolution);
    int getFitness(Individual* in);
    int getMaxFitness();
};



class GeneAlg : public IAlgorithm
{
public:
    GeneAlg(QVector<QVector<float> > input);
    QVector<float> run();
};

#endif // GA_H

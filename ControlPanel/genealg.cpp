#include "genealg.h"
#include <qglobal.h>
#include <QTime>
#include <climits>

class Algorithm;
class Fitness;
class Individual;
class Population;


//Individual methods
Individual::Individual() {}

// Create an individual with sample length
Individual::Individual(int sampleLength) {
    setGeneLength(sampleLength);
    sequence = QVector<float>(geneLength);
}

// Fills in the individual with random points
void Individual::generateIndividual(){
    for(int i = 0; i < size(); i++){
        float gene = ((float)(qrand() % (2000) - 1000)) / 1000;
        sequence[i] = gene;
    }
}

// Sets the length of gene
void Individual::setGeneLength(int len){
    geneLength = len;
}

// Gets Gene at a specific index
float Individual::getGene(int index){
    return sequence.at(index);
}

// Sets gene at a specicic index with a specific value
void Individual::setGene(int index, float value){
    sequence[index] = value;
    fit = 0;
}

// Returns length of the sequence
int Individual::size(){
    return sequence.length();
}

// Get the fitness of the individual
int Individual::getFit(){
    if(fit == 0){
        Fitness find;
        fit = find.getFitness(this);
    }

    return fit;
}



//Population methods

// Create a population with a specific population
Population::Population(int sampleSize, int populationSize, bool initialized) {
    individuals = QVector<Individual>(populationSize);
    if(initialized){
        for (int i = 0; i < size(); ++i){
            Individual newIndividual = Individual(sampleSize);
            newIndividual.generateIndividual();
            saveIndividual(i, newIndividual);
        }
    }
}

// Get an individual at an index
Individual Population::getIndividual(int index){
    return individuals[index];
}

// Get the fittest of the population
Individual Population::getFittest(){
    Individual fittest = individuals[0];
    for(int i = 0; i < this->size(); ++i){
        if (fittest.getFit() >= getIndividual(i).getFit()){
            fittest = getIndividual(i);
        }
    }

    return fittest;
}

// Return the number of individuals in population
int Population::size(){
    return individuals.length();
}

// Write an idividual in the population
void Population::saveIndividual(int index, Individual indiv){
    individuals[index] = indiv;
}



//Algorithm Methods
Algorithm::Algorithm() {}

// Set the settings
Algorithm::Algorithm(double uniform, double mutation,
                     int children, int sample, bool elite){
    this->uniformRate = uniform;
    this->mutationRate = mutation;
    this->childPop = children;
    this->sampleSize = sample;
    this->elitism = elite;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

// Start evolving populations, crossing over and generating new children
Population Algorithm::evolvePopulation(Population parent){
    this->sampleSize = parent.getIndividual(0).size();

    Population newPopulation = Population(sampleSize, parent.size(), false);

    if(this->elitism){
        newPopulation.saveIndividual(0, parent.getFittest());
    }

    int elitismOffset;
    if(this->elitism){
        elitismOffset = 1;
    } else{
        elitismOffset = 0;
    }

    for(int i = 0; i < parent.size(); ++i){
        Individual indiv1 = childSelect(parent);
        Individual indiv2 = childSelect(parent);
        Individual newIndiv = crossover(indiv1, indiv2);
        newPopulation.saveIndividual(i, newIndiv);
    }

    for(int i = elitismOffset; i < newPopulation.size(); ++i){
        mutate(newPopulation.getIndividual(i));
    }

    return newPopulation;
}

// Switching the gene based on the given uniform rate
Individual Algorithm::crossover(Individual indiv1, Individual indiv2){
    Individual newChild = Individual(indiv1.size());

    for(int i = 0; i < indiv1.size(); i++){
        if(rand() <= this->uniformRate){
            newChild.setGene(i, indiv1.getGene(i));
        } else {
            newChild.setGene(i, indiv2.getGene(i));
        }
    }
    return newChild;
}

// Randomly introduce a random gene to prevent too early convergence
void Algorithm::mutate(Individual indiv){
    for(int i = 0; i < indiv.size(); ++i){
        if(rand() <= mutationRate){
            float gene = ((float)(qrand() % (2000) - 1000)) / 1000;
            indiv.setGene(i, gene);
        }
    }
}

// Select the fittest child
Individual Algorithm::childSelect(Population parent){
    Population result = Population(sampleSize, childPop, false);

    for(int i = 0; i < this->childPop; ++i){
        int randomID = qrand() % parent.size();

        result.saveIndividual(i, parent.getIndividual(randomID));
    }
    Individual fittest = result.getFittest();
    return fittest;
}



//Fitness methods

// Set the best solution
void Fitness::setSolution(QVector<QVector<float>> * newSolution){
    solution = newSolution;
}

// Get the fitness of an individual based on the result
int Fitness::getFitness(Individual* in){
    int fitness = 0;
    Individual individual = *in;
    for(int j = 0; j < solution->size(); ++j){
        for(int i = 0; i < individual.size() && i < (*solution)[0].length(); ++i){
            fitness += qAbs(individual.getGene(i) - (*solution)[j][i]);
        }
    }
    return fitness;
}

// Get the most fit
int Fitness::getMaxFitness(){
    int maxFitness = solution->length();
    return maxFitness;
}

//GA methods

GeneAlg::GeneAlg(){

}

// Set the settings
GeneAlg::GeneAlg(AlgoSettings* settings)
{
    //?
}

// overrides IAlgorithm's method
QVector<float> GeneAlg::run(QVector<QVector<float> > input){
    QVector<QVector<float>> * solutions = new QVector<QVector<float>>;

    for(int i = 0; i < input.length(); i++){
        solutions->append(input[i]);
        qDebug() << input[i].size();
    }
    for(int i = 0; i < input[0].length(); i++){
        break;
        qDebug() << input[0][i];
    }
    Fitness * checkFitness = new Fitness;
    checkFitness->setSolution(solutions);
    Population myPop = Population(44100, 4, true);
    int targetGen = 1;
    int generationCount = 0;
    Algorithm* start = new Algorithm();
    while(generationCount < targetGen){
        myPop = start->evolvePopulation(myPop);
        generationCount++;
    }
    QVector<float> a;

    for(int i = 0; i < myPop.size(); ++i){
        Individual ind = myPop.getIndividual(i);

        for(int j = 0; j < ind.size(); ++j){
            a.push_back(ind.getGene(j));
        }
    }

    return a;
}

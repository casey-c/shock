#include "genealg.h"

class Algorithm;
class Fitness;
class Individual;
class Population;


//Individual methods
Individual::Individual() {}

// Create an individual with sample length
Individual::Individual(int sampleLength) {
    this->setGeneLength(sampleLength);
    this->sequence = QVector<float>(geneLength);
}

// Fills in the individual with random points
void Individual::generateIndividual(){
    for(int i = 0; i < size(); i++){
        float gene = (float) rand();
        sequence[i] = gene;
    }
}

// Sets the length of gene
void Individual::setGeneLength(int len){
    this->geneLength = len;
}

// Gets Gene at a specific index
float Individual::getGene(int index){
    return this->sequence.at(index);
}

// Sets gene at a specicic index with a specific value
void Individual::setGene(int index, float value){
    this->sequence[index] = value;
    this->fit = 0;
}

// Returns length of the sequence
int Individual::size(){
    return this->sequence.length();
}

// Get the fitness of the individual
int Individual::getFit(){
    if(this->fit == 0){
        Fitness find;
        this->fit = find.getFitness(this);
    }
    return this->fit;
}



//Population methods

// Create a population with a specific population
Population::Population(int sampleSize, int populationSize, bool initialized) {
    this->individuals = QVector<Individual>(populationSize);
    if(initialized){
        for (int i = 0; i < size(); ++i){
            Individual newIndividual = Individual(sampleSize);
            newIndividual.generateIndividual();
            this->saveIndividual(i, newIndividual);
        }
    }
}

// Get an individual at an index
Individual Population::getIndividual(int index){
    return this->individuals[index];
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
    return this->individuals.length();
}

// Write an idividual in the population
void Population::saveIndividual(int index, Individual indiv){
    this->individuals[index] = indiv;
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
        if(rand() <= this->mutationRate){
            float gene = (float) rand();
            indiv.setGene(i, gene);
        }
    }
}

// Select the fittest child
Individual Algorithm::childSelect(Population parent){
    Population result = Population(this->sampleSize, this->childPop, false);
    for(int i = 0; i < this->childPop; ++i){
        int randomID = (int) rand() * parent.size();
        result.saveIndividual(i, parent.getIndividual(randomID));
    }
    Individual fittest = result.getFittest();
    return fittest;
}



//Fitness methods

// Set the best solution
void Fitness::setSolution(QVector<float> newSolution){
    solution = newSolution;
}

// Get the fitness of an individual based on the result
int Fitness::getFitness(Individual* in){
    int fitness = 0;
    Individual individual = *in;
    for(int i = 0; i < individual.size() && i < this->solution.length(); ++i){
        fitness += abs(individual.getGene(i) - this->solution[i]);
    }
    return fitness;
}

// Get the most fit
int Fitness::getMaxFitness(){
    int maxFitness = this->solution.length();
    return maxFitness;
}

//GA methods

GeneAlg::GeneAlg(){}

// Set the settings
GeneAlg::GeneAlg(AlgoSettings settings)
{
    //if(settings != NULL){
    //uniformRate = settings;
    //mutationRate = settings;
    //childPop = settings;
    //sampleSize = settings;
    //elitism = settings;
    //}
}

// overrides IAlgorithm's method
QVector<float> GeneAlg::run(QVector<QVector<float> > input){
    //QVector<Individual> solutions = QVector<Individual>();

    //for(int i = 0; i < input.length(); i++){
    //     solutions.append(input[i]);
    //}

    //Fitness.setSolution(solutions[0]);

    Population myPop = Population(44100, 4, true);

    int targetGen = 10;

    int generationCount = 0;
    Algorithm start;
    while(generationCount < targetGen){
        myPop = start.evolvePopulation(myPop);
        generationCount++;
    }
    QVector<float> a;
    return a;
}

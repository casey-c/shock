#include "genealg.h"

class Algorithm;
class Fitness;
class Individual;
class Population;


//Individual methods
Individual::Individual() {}

// Create an individual with sample length
Individual::Individual(int sampleLength) {
    setGeneLength(sampleLength);
    sequence = QVector<double>(geneLength);
}

// Fills in the individual with random points
void Individual::generateIndividual(){
    for(int i = 0; i < size(); i++){
        double gene = (double) rand();
        sequence[i] = gene;
    }
}

// Sets the length of gene
void Individual::setGeneLength(int len){
    geneLength = len;
}

// Gets Gene at a specific index
double Individual::getGene(int index){
    return sequence.at(index);
}

// Sets gene at a specicic index with a specific value
void Individual::setGene(int index, double value){
    sequence[index] = value;
    fit = 0;
}

// Returns length of the sequence
int Individual::size(){
    return sequence.length();
}

// Get the fitness of the individual
int Individual::getFit(){
    qDebug() << "good so far fit";
    if(fit == 0){
        Fitness find;
        fit = find.getFitness(this);
    }
    qDebug() << "good so far return fit";
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
    qDebug() << "good so far get";
    return this->individuals[index];
}

// Get the fittest of the population
Individual Population::getFittest(){
    qDebug() << "good so far";
    Individual fittest = individuals[0];
    qDebug() << "good so far";
    for(int i = 0; i < this->size(); ++i){
        qDebug() << "good so far loop";
        if (fittest.getFit() >= getIndividual(i).getFit()){
            qDebug() << "good so far if";
            fittest = getIndividual(i);
        }
    }
    qDebug() << "good so far!";
    return fittest;
}

// Return the number of individuals in population
int Population::size(){
    return individuals.length();
}

// Write an idividual in the population
void Population::saveIndividual(int index, Individual indiv){
    qDebug() << "save good so far" << individuals.size();
    individuals[index] = indiv;
    qDebug() << "good so far";
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
    qDebug() << "good so far1";
    Population newPopulation = Population(sampleSize, parent.size(), false);
    qDebug() << "good so far2";
    if(this->elitism){
        newPopulation.saveIndividual(0, parent.getFittest());
    }
    qDebug() << "good so far3";
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
            double gene = (double) rand();
            indiv.setGene(i, gene);
        }
    }
}

// Select the fittest child
Individual Algorithm::childSelect(Population parent){
    Population result = Population(sampleSize, childPop, false);
    for(int i = 0; i < this->childPop; ++i){
        int randomID = (int) rand() * parent.size();
        result.saveIndividual(i, parent.getIndividual(randomID));
    }
    Individual fittest = result.getFittest();
    return fittest;
}



//Fitness methods

// Set the best solution
void Fitness::setSolution(QVector<QVector<double>> * newSolution){
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

GeneAlg::GeneAlg(){}

// Set the settings
GeneAlg::GeneAlg(AlgoSettings* settings)
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
QVector<double> GeneAlg::run(QVector<QVector<double> > input){
    QVector<QVector<double>> * solutions = new QVector<QVector<double>>;

    qDebug() << "good so far";
    //for(int i = 0; i < input.length(); i++){
    //     solutions.append(input[i]);
    //}

    //Fitness.setSolution(solutions[0]);

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
    qDebug() << "good so far";
    Population myPop = Population(44100, 2, true);
    qDebug() << myPop.size();
    int targetGen = 1;
    qDebug() << "good so far";
    int generationCount = 0;
    Algorithm* start = new Algorithm();
    qDebug() << "good so far";
    while(generationCount < targetGen){
        myPop = start->evolvePopulation(myPop);
        qDebug() << "good so far" << generationCount;
        generationCount++;
    }
    QVector<double> a;
    return a;
}

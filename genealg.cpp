#include "genealg.h"

class Algorithm;
class Fitness;
class Individual;
class Population;


//Individual methods
Individual::Individual() {}

Individual::Individual(int sampleLength) {
    this->setGeneLength(sampleLength);
    this->sequence = QVector<float>(geneLength);
}

void Individual::generateIndividual(){
    for(int i = 0; i < size(); i++){
        float gene = (float) rand();
        sequence[i] = gene;
    }
}

void Individual::setGeneLength(int len){
    this->geneLength = len;
}

float Individual::getGene(int index){
    return this->sequence.at(index);
}

void Individual::setGene(int index, float value){
    this->sequence[index] = value;
    this->fit = 0;
}

int Individual::size(){
    return this->sequence.length();
}

int Individual::getFit(){
    if(this->fit == 0){
        Fitness find;
        this->fit = find.getFitness(this);
    }
    return this->fit;
}



//Population methods
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

Individual Population::getIndividual(int index){
    return this->individuals[index];
}

Individual Population::getFittest(){
    Individual fittest = individuals[0];
    for(int i = 0; i < this->size(); ++i){
        if (fittest.getFit() >= getIndividual(i).getFit()){
            fittest = getIndividual(i);
        }
    }
    return fittest;
}

int Population::size(){
    return this->individuals.length();
}

void Population::saveIndividual(int index, Individual indiv){
    this->individuals[index] = indiv;
}



//Algorithm Methods
Algorithm::Algorithm() {}

Algorithm::Algorithm(double uniform, double mutation,
                     int children, int sample, bool elite){
    this->uniformRate = uniform;
    this->mutationRate = mutation;
    this->childPop = children;
    this->sampleSize = sample;
    this->elitism = elite;
}


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

void Algorithm::mutate(Individual indiv){
    for(int i = 0; i < indiv.size(); ++i){
        if(rand() <= this->mutationRate){
            float gene = (float) rand();
            indiv.setGene(i, gene);
        }
    }
}

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
void Fitness::setSolution(QVector<float> newSolution){
    solution = newSolution;
}

int Fitness::getFitness(Individual* in){
    int fitness = 0;
    Individual individual = *in;
    for(int i = 0; i < individual.size() && i < this->solution.length(); ++i){
        fitness += abs(individual.getGene(i) - this->solution[i]);
    }
    return fitness;
}

int Fitness::getMaxFitness(){
    int maxFitness = this->solution.length();
    return maxFitness;
}


GeneAlg::GeneAlg(){}


//GA method
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

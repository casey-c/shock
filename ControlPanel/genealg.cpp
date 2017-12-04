#include "genealg.h"
#include <qglobal.h>
#include <QTime>
#include <climits>
#include <algorithm>
#include <random>

class Algorithm;
class Fitness;
class Individual;
class Population;


//Individual methods
Individual::Individual() {}

// Create an individual with sample length
Individual::Individual(int sampleLength, Fitness* fit) {
    setGeneLength(sampleLength);
    sequence = QVector<float>(geneLength);
    fitnessCheck = fit;
}

// Fills in the individual with random points
void Individual::generateIndividual(){
    for(int i = 0; i < size(); i++){
        //float gene = ((float)(qrand() % (200000) - 100000)) / 100000;
        float gene = (((float)(qrand() % (200000))) / 100000) - 0.12;
        //qDebug() << gene;
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
        fit = fitnessCheck->getFitness(this);
    }

    return fit;
}



//Population methods

// Create a population with a specific population
Population::Population(int sampleSize, int populationSize, bool initialized, Fitness* fit) {
    individuals = QVector<Individual>(populationSize);
    fitnessCheck = fit;
    if(initialized){
        for (int i = 0; i < size(); ++i){
            Individual newIndividual = Individual(sampleSize, fitnessCheck);
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
        if (fittest.getFit() <= getIndividual(i).getFit()){
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

    Population newPopulation = Population(sampleSize, parent.size(), false, parent.getIndividual(0).getChecker());

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
    Individual newChild = Individual(indiv1.size(), indiv1.getChecker());

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
            float gene = ((float)(qrand() % (200000) - 100000)) / 100000;
            indiv.setGene(i, gene);
        }
    }
}

// Select the fittest child
Individual Algorithm::childSelect(Population parent){
    Population result = Population(sampleSize, childPop, false, parent.getIndividual(0).getChecker());

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
    Param* p;
    foreach(p, settings->getParams()){
        if(p->getName() == "uniformRate")
            uniformRate = p->getValue();
        else if(p->getName() == "mutationRate")
            mutationRate = p->getValue();
        else if(p->getName() == "childPopSize")
            childPop = (int)p->getValue();
        else if(p->getName() == "elitism")
            elitism = p->getValue() != 0;
        else if(p->getName() == "generations")
            generations = (int)p->getValue();
    }
}

void GeneAlg::setOutputLength(double len) {
    outputLength = len;
}

// overrides IAlgorithm's method
QVector<float> GeneAlg::run(QVector<QVector<float> > input){
    QVector<QVector<float>> * solutions = new QVector<QVector<float>>;
    int minSize = input[0].size();
    for(int i = 0; i < input.length(); i++){
        solutions->append(input[i]);
        if(input[i].size() < minSize){
            minSize = input[i].size();
        }
    }

    qDebug()<<"minsize" << minSize;

    for(int i = 0; i < input[0].length(); i++){
        break;
        qDebug() << input[0][i];
    }
    Fitness * checkFitness = new Fitness;
    checkFitness->setSolution(solutions);
    Population myPop = Population(minSize, childPop, true, checkFitness);
    int generationCount = 0;
    Algorithm* start = new Algorithm(uniformRate,mutationRate,childPop,minSize,elitism);
    while(generationCount < generations){
        //qDebug()<<generationCount;
        myPop = start->evolvePopulation(myPop);
        generationCount++;
    }
    QVector<float> a;


    Individual ind = myPop.getFittest();

    double test1 = (double)qrand() / RAND_MAX;
    double section = (qrand() % 5000) + 900;
    int counter = 0;

    int sampleRate = 44100;

    int outBits = (int) (sampleRate * outputLength);

    //qDebug() << "outlen" << outputLength;

    //qDebug() << "outBits " << outBits;


    for(int i2 = 0; i2 < outBits; ++i2){
        int i = (int)(i2*((double)minSize/outBits))%(minSize-1);
        //int i= i2%(minSize-1);

        //qDebug() << i;
        if (i < 0)
            i=0;

        int mult = outBits/minSize;

        //qDebug() << mult;

        //if (i2 < outBits)

        if (i+1+counter > (minSize-1))
            i = minSize-mult^2-2;

        counter++;
        if (counter > mult^2){
            test1 = (double)qrand() / RAND_MAX;
            section = (qrand() % 5000) + 400;
            counter = 0;
        }
        float e = 0;
        float b = 0;
        for(int j = 0; j<input.size(); ++j){
            //float c = qrand()-RAND_MAX/2;
            //c /= RAND_MAX;
            //c /= 10;
            b += input[j][i+counter];
            e += input[j][i+1+counter];
        }
        e /= input.size();
        b /= input.size();
        /*
        if(b > 0)
            b = -b;
        else
            b = qAbs(b);
        */
        if (test1 < .25)
            a.append(e);
        else if (test1 < .75)
            a.append((e+b)/2);
        else if (test1 < 1)
            a.append(b);
    }
    /*
    for(int i = 1; i < minSize; i+=2){
        float e = 0;
        float b = 0;
        for(int j = 0; j<input.size(); ++j){
            //float c = qrand()-RAND_MAX/2;
            //c /= RAND_MAX;
            //c /= 10;
            b += input[j][i];
            e += input[j][i-1];
        }

        if(b > 0)
            b = -b;
        else
            b = qAbs(b);

        a.append(e);
        a.append((e+b)/2);
        a.append(b);
    }
    */
    //std::vector<float> ad = a.toStdVector();
    //auto rng = std::default_random_engine {};
    //std::shuffle(std::begin(ad), std::end(ad),rng);

    //QVector<float> ac = QVector<float>::fromStdVector(ad);

    //a.clear();
/*
    for(int j = 1; j < ind.size(); ++j){
        float x = ind.getGene(j-1);
        float y = ind.getGene(j);
        float tween = (x+y)/2;
        a.push_back(x);
        a.push_back(tween);
        a.push_back(y);
    }
*/

    return a;
}

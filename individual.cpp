#include "stdlib.h"
#include <QList>

class Individual
{
public:
    Individual(int sampleLength) {
        setGeneLength(sampleLength);
        sequence = new QList<double>(geneLength);
    }

    void generateIndividual(){
        for(int i = 0; i < size(); i++){
            double gene = (double) rand();
            sequence[i] = gene;
        }
    }

    static void setGeneLength(int len){
        geneLength = len;
    }

    double getGene(int index){
        return sequence.at(index);
    }

    void setGene(int index, double value){
        sequence[index] = value;
        fitness = 0
    }

    int size(){
        return sequence.length();
    }

    int getFitness(){
        if(fitness == 0){
            fitness = Fitness.getFitness(this);
        }
        return fitness;
    }


private:
    int fitness = 0;
    int geneLength = 0;
    QList<double> sequence;

};

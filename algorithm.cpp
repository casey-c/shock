#include "population.cpp"

class Algorithm
{
public:
    Algorithm() {}

    Population evolvePopulation(Population parent){
        Population newPopulation = new Population(parent.size(), false);

        if(elitism){
            newPopulation.saveIndividual(0, parent.getFittest());
        }

        int elitismOffset;
        if(elitism){
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



private:
    double uniformRate = 0.5;
    double mutationRate = 0.015;
    int childPop = 5;
    bool elitism = true;

    Individual crossover(Individual indiv1, Individual indiv2){
        Individual newChild = new Individual();

        for(int i = 0; i < indiv1.size(); i++){
            if(rand() <= uniformRate){
                newChild.setGene(i, indiv1.getGene(i));
            } else {
                newChild.setGene(i, indiv2.getGene(i));
            }
        }
        return newChild;
    }

    void mutate(Individual indiv){
        for(int i = 0; i < indiv.size(); ++i){
            if(rand() <= mutationRate){
                double gene = (double) rand();
                indiv.setGene(i, gene);
            }
        }
    }

    Individual childSelect(Population parent){
        Population result = new Population(childPop, false);
        for(int i = 0; i < childPop; ++i){
            int randomID = (int) rand * parent.size();
            result.saveIndividual(i, parent.getIndividual(randomID));
        }
        Individual fittest = result.getFittest();
        return fittest;
    }
};

#include "individual.cpp"

class Population
{
public:
    Population(int populationSize, boolean initialized) {
        individuals = new Individual[populationSize];
        if(initialized){
            for (int i = 0; i < size(); ++i){
                Individual newIndividual = new Individual();
                newIndividual.generateIndividual();
                saveIndividual(i, newIndividual);
            }
        }
    }

    Individual getIndividual(int index){
        return individuals[index];
    }

    Individual getFittest(){
        Individual fittest = individuals[0];
    }

    int size(){
        return individuals.length;
    }

    void saveIndividual(int index, Individual indiv){
        individuals[index] = indiv;
    }

private:
    QList<Individual> individuals;
};

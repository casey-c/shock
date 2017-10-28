#include "algorithm.cpp"

class Fitness
{
public:
    Fitness() {}

    QList<double> solution;

    void setSolution(QList<double> newSolution){
        solution = newSolution;
    }

    int getFitness(Individual individual){
        int fitness = 0;

        for(int i = 0; i < individual.size() && i < solution.length(); ++i){
            fitness += abs(individual.getGene(i) - solution[i]);
        }
        return fitness;
    }

    int getMaxFitness(){
        int maxFitness = solution.length();
        return maxFitness;
    }
};

#include "ga.h"

GA::GA(QList<QList<double> > input)
{
    QList<Individual> solutions = new QList<Individual>();

    for(i = 0; i < input.length(); i++){
        solutions.append(input[i]);
    }

    Fitness.setSolution(solutions[0]);

    Population myPop = new Population(44100, true);

    int targetGen = 10;

    int generationCount = 0;

    while(generationCount < targetGen){
        myPop = Algorithm.evolvePopulation(myPop);
        generationCount++;
    }
}

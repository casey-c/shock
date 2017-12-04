#ifndef IALGORITHM_H
#define IALGORITHM_H
#include <QVector>
#include "stdlib.h"
#include "algosettings.h"


//Abstract algorithm class which other algorithms will be based off of
class IAlgorithm
{
public:
    IAlgorithm(){}
    IAlgorithm(AlgoSettings input)
        :settings(input)
    {}
    virtual QVector<float> run(QVector<QVector<float> > input) = 0;
protected:
    AlgoSettings settings;
    double outputLength = 10;
};

#endif // IALGORITHM_H

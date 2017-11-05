#ifndef IALGORITHM_H
#define IALGORITHM_H
#include <QVector>
#include "stdlib.h"
#include "algosettings.h"

class IAlgorithm
{
public:
    IAlgorithm(AlgoSettings input)
        :settings(input)
    {}
    virtual QVector<float> run(QVector<QVector<float> > input) = 0;
protected:
    AlgoSettings settings;
};

#endif // IALGORITHM_H

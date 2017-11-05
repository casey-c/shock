#ifndef IALGORITHM_H
#define IALGORITHM_H
#include <QVector>
#include "stdlib.h"
#include "algosettings.h"

class IAlgorithm
{
public:
    IAlgorithm();
    virtual QVector<float> run();
private:
    AlgoSettings settings;
};

#endif // IALGORITHM_H

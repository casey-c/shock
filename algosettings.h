#ifndef ALGOSETTINGS_H
#define ALGOSETTINGS_H

#include <QList>
#include "param.h"

class AlgoSettings
{
public:
    AlgoSettings();
private:
    QList<Param*> params;
};

#endif // ALGOSETTINGS_H

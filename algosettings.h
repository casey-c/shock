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
    QString name;
};

#endif // ALGOSETTINGS_H

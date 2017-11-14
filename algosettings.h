#ifndef ALGOSETTINGS_H
#define ALGOSETTINGS_H

#include <QList>
#include <QDebug>
#include <QPair>
#include <QDir>
#include <QLineEdit>
#include <QSlider>
#include "param.h"
#include "jsontemplateinterpreter.h"
#include <QLabel>

class AlgoSettings
{
public:
    AlgoSettings();

    QList<Param*> getParams() {return params;}
private:
    QList<Param*> params;
    QString name;
};

#endif // ALGOSETTINGS_H

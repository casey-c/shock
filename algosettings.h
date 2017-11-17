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

    void addParam(QString name, double def, double high,
                  double low, int precision, QStringList widgetTypes);
};

#endif // ALGOSETTINGS_H

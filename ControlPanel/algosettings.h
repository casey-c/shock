#ifndef ALGOSETTINGS_H
#define ALGOSETTINGS_H

#include <QList>
#include <QDebug>
#include <QPair>
#include <QDir>
#include <QLineEdit>
#include <QSlider>
#include "ControlPanel/param.h"
#include "Config/jsontemplateinterpreter.h"
#include <QLabel>

class AlgoSettings
{
public:
    AlgoSettings();

    QList<Param*> getParams() {return params;}
    QString getName() {return name;}
private:
    QList<Param*> params;
    QString name;
    QString algoLoc = "templates/genalg2.json";
    void addParam(QString name, double def, double high,
                  double low, int precision, QJsonArray widgetTypes);
};

#endif // ALGOSETTINGS_H

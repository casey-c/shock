#include "algosettings.h"

AlgoSettings::AlgoSettings()
{
    //load in the genetic algorithm settings list from disk
    //(containing all parameters, widgets to modify them, and min/max/default values
    // e.g., "Randomness" parameter from 0 to 1, controlled by a slider and textbox)
    JSONTemplateInterpreter* json = new JSONTemplateInterpreter();
    bool d = json->readFromFile(algoLoc);
    if(!d){
        qDebug() << "OH NO!";
    }
    qDebug() << json->getName();
    name = json->getName();

    QString name;
    double def, high, low;
    int precision;
    QString types;

    QJsonArray data = json->getData();

    //for each object in the json file, get data and create
    // a new Param widget for it
    for(int i = 0; i < data.size(); ++i){
        QJsonObject jsonObj = data[i].toObject();

        name = jsonObj.value("name").toString();
        def = jsonObj.value("default").toDouble();
        high = jsonObj.value("high").toDouble();
        low = jsonObj.value("low").toDouble();
        precision = jsonObj.value("precision").toInt();

        QJsonArray widgetTypes =
                jsonObj.value("widgets").toArray();

        addParam(name, def, high, low, precision, widgetTypes);
    }
}


void AlgoSettings::addParam(QString name, double def, double high,
                            double low, int precision, QJsonArray widgetTypes){
    Param* p = new Param(name, def, low, high, precision);

    //add the widget types that the param contains
    for(QJsonValue wtv : widgetTypes){
        QString wt = wtv.toString();

        if(wt == "slider")
            p->addMutableElement(new QSlider(Qt::Horizontal));
        else if(wt == "lineedit")
            p->addMutableElement(new QLineEdit());
        else if(wt == "checkbox")
            p->addMutableElement(new QCheckBox());
        else if(wt == "label")
            p->addVisualElement(new QLabel(name));
        else if(wt.startsWith("label:")){
            QLabel* temp = new QLabel(wt.remove(0,6).trimmed());
            temp->setMinimumWidth(100);
            temp->setMinimumHeight(20);
            p->addVisualElement(temp);
        }
    }

    params.append(p);
}

#include "algosettings.h"

AlgoSettings::AlgoSettings()
{
    JSONTemplateInterpreter* json = new JSONTemplateInterpreter();
    bool d = json->readFromFile(":/genalg.JSON");
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

    for(int i = 0; i < data.size(); ++i){
        QJsonObject jsonObj = data[i].toObject();

        name = jsonObj.value("name").toString();
        def = jsonObj.value("default").toDouble();
        high = jsonObj.value("high").toDouble();
        low = jsonObj.value("low").toDouble();
        precision = jsonObj.value("precision").toInt();

        QStringList widgetTypes =
                jsonObj.value("widgets").toString().split(",");

        addParam(name, def, high, low, precision, widgetTypes);
    }
}


void AlgoSettings::addParam(QString name, double def, double high,
                            double low, int precision, QStringList widgetTypes){
    Param* p = new Param(name, def, low, high, precision);

    for(QString wt : widgetTypes){
        if(wt == "label")
            p->addVisualElement(new QLabel(name));
        else if(wt == "slider")
            p->addMutableElement(new QSlider(Qt::Horizontal));
        else if(wt == "lineedit")
            p->addMutableElement(new QLineEdit());
        else if(wt == "checkbox")
            p->addMutableElement(new QCheckBox());
    }

    params.append(p);
}

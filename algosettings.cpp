#include "algosettings.h"

AlgoSettings::AlgoSettings()
{
    JSONTemplateInterpreter* json = new JSONTemplateInterpreter();
    bool d = json->readFromFile("templates/GeneticAlgorithmBuilder.json");
    if(!d){
        qDebug() << "OH NO!";
    }
    qDebug() << json->getName();
    //qDebug() << QDir::currentPath();
    name = json->getName();

    QList<QPair<QString,QString>*>* dat = json->getData();

    double def;
    int hi;
    int low;
    QString name;
    int precision;
    QString types;

    for(QList<QPair<QString,QString>*>::iterator itr = dat->begin(); itr != dat->end(); ++itr){
        QPair<QString,QString> currentPair = **itr;
        if(currentPair.first == "def"){
            def = currentPair.second.toDouble();
        }
        if(currentPair.first == "hi"){
            hi = currentPair.second.toDouble();
        }
        if(currentPair.first == "low"){
            low = currentPair.second.toDouble();
        }
        if(currentPair.first == "name"){
            name = currentPair.second;
        }
        if(currentPair.first == "precision"){
            precision = currentPair.second.toInt();
        }
        if(currentPair.first == "type"){
            types = currentPair.second;
            Param* p = new Param(name, def, low, hi, precision);

            QStringList pieces = types.split(",");

            for(QStringList::iterator pIter = pieces.begin(); pIter != pieces.end(); ++pIter){
                if(*pIter == "text"){
                    p->addVisualElement(new QLabel(name));
                }
                else if(*pIter == "slider"){
                    QSlider* s = new QSlider(Qt::Horizontal);
                    p->addMutableElement(s);
                }
                else if(*pIter == "box"){
                    QLineEdit* le = new QLineEdit();
                    p->addMutableElement(le);
                }
                else if(*pIter == "check"){
                    QCheckBox* cb = new QCheckBox();
                    p->addMutableElement(cb);
                }
                else{
                    p->addVisualElement(new QLabel(*pIter));
                }
            }

            params.append(p);
        }
    }

}

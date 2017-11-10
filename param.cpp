#include "param.h"
#include "mutableparamelement.h"

Param::Param(QString nm, double def, QObject* parent):
    QObject(parent){
    name = nm;
    value = def;
}

void Param::addElement(QWidget* w){
    elements.push_back(w);
}

void Param::addMutableElement(MutableParamElement* w){
    QObject::connect(w, SIGNAL(sig_valueChanged(double)),
                     this, SLOT(on_valueChanged(double)));
}

QString Param::toString(){
    return "";
}

void Param::on_valueChanged(double newval){
    value = newval;
}



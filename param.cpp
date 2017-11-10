#include "param.h"

Param::Param(QString nm, double def){
    name = nm;
    value = def;
}

void Param::addElement(QWidget* w){
    elements.push_back(w);
}

QString Param::toString(){
    return "";
}



#include "param.h"
#include "mutableparamelement.h"

Param::Param(QString nm, double def){
    name = nm;
    value = def;
}

void Param::addVisualElement(QWidget* w){
    elements.push_back(w);
}

void Param::addMutableElement(QSlider* w){
    mutableElement_slider* ms =
            new mutableElement_slider(w, low, high, precision, value);

    QObject::connect(ms, SIGNAL(sig_valueChanged(double)),
                     this, SLOT(on_valueChanged(double)));
    elements.push_back(ms);
}

void Param::addMutableElement(QLineEdit* w){
    mutableElement_lineEdit* ms =
            new mutableElement_lineEdit(w, low, high, precision, value);

    QObject::connect(ms, SIGNAL(sig_valueChanged(double)),
                     this, SLOT(on_valueChanged(double)));
    elements.push_back(ms);
}

const QList<QWidget*> Param::getElements(){
    return elements;
}

QString Param::toString(){
    return "";
}

void Param::on_valueChanged(double newval){
    value = newval;
}



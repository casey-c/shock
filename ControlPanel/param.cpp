#include "param.h"

Param::Param(QString nm, double def, double lo, double hi, int precis){
    name = nm;
    value = def;
    low = lo;
    high = hi;
    precision = precis;
}

void Param::addVisualElement(QWidget* w){
    elements.push_back(w);
}

void Param::addMutableElement(QSlider* w){
    MutableElement_slider* ms =
            new MutableElement_slider(w, low, high, precision, value);

    QObject::connect(ms, SIGNAL(sig_valueChanged(double)),
                     this, SLOT(on_valueChanged(double)));

    QObject::connect(this, SIGNAL(changeValue(double)),
                     ms, SLOT(on_valueChanged(double)));

    elements.push_back(w);
}

void Param::addMutableElement(QLineEdit* w){
    MutableElement_lineEdit* ms =
            new MutableElement_lineEdit(w, low, high, precision, value);

    QObject::connect(ms, SIGNAL(sig_valueChanged(double)),
                     this, SLOT(on_valueChanged(double)));

    QObject::connect(this, SIGNAL(changeValue(double)),
                     ms, SLOT(on_valueChanged(double)));

    elements.push_back(w);
}

void Param::addMutableElement(QCheckBox* w){
    MutableElement_checkBox* ms =
            new MutableElement_checkBox(w, low, high, value);

    QObject::connect(ms, SIGNAL(sig_valueChanged(double)),
                     this, SLOT(on_valueChanged(double)));

    QObject::connect(this, SIGNAL(changeValue(double)),
                     ms, SLOT(on_valueChanged(double)));

    elements.push_back(w);
}

const QList<QWidget*> Param::getElements(){
    return elements;
}

QString Param::toString(){
    return "";
}

void Param::on_valueChanged(double newval){
    value = newval;

    emit changeValue(value);
}



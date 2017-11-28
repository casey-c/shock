#include "param.h"

Param::Param(QString nm, double def, double lo, double hi, int precis){ // create a new param
    name = nm;
    value = def;
    low = lo;
    high = hi;
    precision = precis;
}

void Param::addVisualElement(QWidget* w){
    elements.push_back(w);
}

void Param::addMutableElement(QSlider* w){ // add an element that the user can change
    MutableElement_slider* ms =
            new MutableElement_slider(w, low, high, precision, value);

    QObject::connect(ms, SIGNAL(sig_valueChanged(double)),
                     this, SLOT(on_valueChanged(double))); // connect signals with proper slots

    QObject::connect(this, SIGNAL(changeValue(double)),
                     ms, SLOT(on_valueChanged(double))); // connect signals with proper slots

    elements.push_back(w); // add element to elemt list
}

void Param::addMutableElement(QLineEdit* w){ // add an element that the user can change
    MutableElement_lineEdit* ms =
            new MutableElement_lineEdit(w, low, high, precision, value);

    QObject::connect(ms, SIGNAL(sig_valueChanged(double)),
                     this, SLOT(on_valueChanged(double))); // connect signals with proper slots

    QObject::connect(this, SIGNAL(changeValue(double)),
                     ms, SLOT(on_valueChanged(double))); // connect signals with proper slots

    elements.push_back(w); // add element to elemt list
}

void Param::addMutableElement(QCheckBox* w){ // add an element that the user can change
    MutableElement_checkBox* ms =
            new MutableElement_checkBox(w, low, high, value);

    QObject::connect(ms, SIGNAL(sig_valueChanged(double)),
                     this, SLOT(on_valueChanged(double))); // connect signals with proper slots

    QObject::connect(this, SIGNAL(changeValue(double)),
                     ms, SLOT(on_valueChanged(double))); // connect signals with proper slots

    elements.push_back(w); // add element to elemt list
}

const QList<QWidget*> Param::getElements(){ // returns all elements associated with parameter
    return elements;
}

QString Param::toString(){
    return "";
}

void Param::on_valueChanged(double newval){
    value = newval;

    emit changeValue(value); // tell linked slots that the value ws changed
}



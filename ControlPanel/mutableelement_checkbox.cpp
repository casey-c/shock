#include "mutableelement_checkbox.h"

MutableElement_checkBox::MutableElement_checkBox( // allows check boxes to be used
        QCheckBox* cb,
        double min, double max, double def)
{
    checkBox = cb;

    QObject::connect(checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(emitValChange())); // connect signals and slots for element
    checkBox->setLayoutDirection(Qt::LeftToRight);
    checkBox->setFixedWidth(60);
    maximum = max;
    minimum = min;

    on_valueChanged(def);
}

void MutableElement_checkBox::emitValChange(){ // used to link different mutable elements
    if(checkBox->isChecked())
        emit sig_valueChanged(maximum);
    else
        emit sig_valueChanged(minimum);
}

void MutableElement_checkBox::on_valueChanged(double newval){ // used to link different mutable elements
    if(newval == maximum)
        checkBox->setChecked(true);
    else
        checkBox->setChecked(false);
}

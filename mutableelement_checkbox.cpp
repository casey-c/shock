#include "mutableelement_checkbox.h"

MutableElement_checkBox::MutableElement_checkBox(
        QCheckBox* cb,
        double min, double max, double def)
{
    checkBox = cb;

    QObject::connect(checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(emitValChange()));

    maximum = max;
    minimum = min;

    on_valueChanged(def);
}

void MutableElement_checkBox::emitValChange(){
    if(checkBox->isChecked())
        emit sig_valueChanged(maximum);
    else
        emit sig_valueChanged(minimum);
}

void MutableElement_checkBox::on_valueChanged(double newval){
    if(newval == maximum)
        checkBox->setChecked(true);
    else
        checkBox->setChecked(false);
}

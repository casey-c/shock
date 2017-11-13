#include "mutableparamelement.h"

mutableElement_slider::mutableElement_slider(
        QSlider* sl,
        double low, double high, int precision, double def)
{
    slider = sl;

    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     this, SLOT(emitValChange()));

    div = (int) qPow(10, precision);
    slider->setTickInterval(div);
    slider->setMinimum(low * div);
    slider->setMaximum(high * div);
    slider->setValue(def * div);
}

void mutableElement_slider::emitValChange(){
    emit sig_valueChanged((double) slider->value() / (double) div);
}

void mutableElement_slider::on_valueChanged(double newval){
    slider->setValue(newval * div);
}

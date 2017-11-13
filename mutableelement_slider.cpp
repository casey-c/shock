#include "mutableelement_slider.h"

MutableElement_slider::MutableElement_slider(
        QSlider* sl,
        double low, double high, int precision, double def)
{
    slider = sl;

    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     this, SLOT(emitValChange()));

    div = (int) qPow(10, precision);
    slider->setMinimum(low * div);
    slider->setMaximum(high * div);
    slider->setValue(def * div);
}

void MutableElement_slider::emitValChange(){
    emit sig_valueChanged((double) slider->value() / (double) div);
}

void MutableElement_slider::on_valueChanged(double newval){
    slider->setValue(newval * div);
}

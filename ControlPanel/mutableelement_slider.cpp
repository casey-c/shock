#include "mutableelement_slider.h"

MutableElement_slider::MutableElement_slider( // allows sliders to be used
        QSlider* sl,
        double low, double high, int precision, double def)
{
    slider = sl;

    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     this, SLOT(emitValChange())); // connect signals and slots for element

    div = (int) qPow(10, precision);
    slider->setMinimum(low * div);
    slider->setMaximum(high * div);
    slider->setValue(def * div); // default value
}

void MutableElement_slider::emitValChange(){ // used to link different mutable elements
    emit sig_valueChanged((double) slider->value() / (double) div);
}

void MutableElement_slider::on_valueChanged(double newval){ // used to link different mutable elements
    slider->setValue(newval * div);
}

#include "mutableparamelement.h"

MPEslider::MPEslider(Qt::Orientation orientation,
          double low, double high, double step, int precision, double def,
          QWidget* parent): QSlider(orientation, parent){
    QObject::connect(this, SIGNAL(valueChanged(int)),
                     this, SLOT(emitValChange()));
    div = (int) qPow(10, precision);
    setTickInterval(step * div);
    setMinimum(low * div);
    setMaximum(high * div);
    setValue(def * div);
}

void MPEslider::emitValChange(){
    emit sig_valueChanged((double) value() / (double) div);
}

void MPEslider::on_valueChanged(double newval){
    setValue(newval * div);
}

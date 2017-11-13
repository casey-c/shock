#ifndef MUTABLEELEMENT_SLIDER_H
#define MUTABLEELEMENT_SLIDER_H

#include "mutableparamelement.h"
#include <QSlider>
#include <Qtmath>

class MutableElement_slider final: public MutableParamElement{
    Q_OBJECT
public:
    explicit MutableElement_slider(QSlider* sl,
              double low, double high, int precision, double def);
protected:
    void emitValChange();
    void on_valueChanged(double newval);

private:
    QSlider* slider;
    int div;
};

#endif // MUTABLEELEMENT_SLIDER_H

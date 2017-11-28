#ifndef MUTABLEELEMENT_CHECKBOX_H
#define MUTABLEELEMENT_CHECKBOX_H

#include "mutableparamelement.h"
#include <QCheckBox>

class MutableElement_checkBox final: public MutableParamElement{
    Q_OBJECT
public:
    explicit MutableElement_checkBox(QCheckBox* cb,
                double min, double max, double def);
protected:
    virtual void emitValChange();
    virtual void on_valueChanged(double newval);

private:
    QCheckBox* checkBox;

    double maximum;
    double minimum;
};

#endif // MUTABLEELEMENT_CHECKBOX_H

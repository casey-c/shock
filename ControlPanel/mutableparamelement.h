#ifndef MUTABLEPARAMELEMENT_H
#define MUTABLEPARAMELEMENT_H

#include "mutableparamelement.h"
#include <QWidget>

class MutableParamElement: public QWidget{
    Q_OBJECT
signals:
    void sig_valueChanged(double newval);
protected slots:
    virtual void emitValChange() = 0;
    virtual void on_valueChanged(double newval) = 0;
};

#endif // MUTABLEPARAMELEMENT_H

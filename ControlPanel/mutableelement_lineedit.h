#ifndef MUTABLEELEMENT_LINEEDIT_H
#define MUTABLEELEMENT_LINEEDIT_H

#include "mutableparamelement.h"
#include <QWidget>
#include <QLineEdit>
#include <QValidator>

class MutableElement_lineEdit final: public MutableParamElement{
    Q_OBJECT
public:
    explicit MutableElement_lineEdit(QLineEdit* le,
                double low, double high, int precision, double def);
protected:
    virtual void emitValChange();
    virtual void on_valueChanged(double newval);

private:
    QLineEdit* lineEdit;

private slots:
    void dropFocus();
};


#endif // MUTABLEELEMENT_LINEEDIT_H

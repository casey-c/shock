#include "mutableparamelement.h"


mutableElement_lineEdit::mutableElement_lineEdit(
        QLineEdit* le,
        double low, double high, int precision, double def)
{
    lineEdit = le;

    QObject::connect(lineEdit, SIGNAL(editingFinished()),
                     this, SLOT(emitValChange()));
    lineEdit->setText(QString::number(def));
    lineEdit->setValidator(new QDoubleValidator(low, high, precision, this));
}

void mutableElement_lineEdit::emitValChange(){
    emit sig_valueChanged(lineEdit->text().toDouble());
}

void mutableElement_lineEdit::on_valueChanged(double newval){
    lineEdit->setText(QString::number(newval));
}

#include "mutableelement_lineedit.h"

MutableElement_lineEdit::MutableElement_lineEdit(
        QLineEdit* le,
        double low, double high, int precision, double def)
{
    lineEdit = le;

    QObject::connect(lineEdit, SIGNAL(returnPressed()),
                     this, SLOT(dropFocus()));

    QObject::connect(lineEdit, SIGNAL(editingFinished()),
                     this, SLOT(emitValChange()));

    lineEdit->setText(QString::number(def));
    lineEdit->setValidator(new QDoubleValidator(low, high, precision, this));
}

void MutableElement_lineEdit::emitValChange(){
    emit sig_valueChanged(lineEdit->text().toDouble());
}

void MutableElement_lineEdit::on_valueChanged(double newval){
    lineEdit->setText(QString::number(newval));
}

void MutableElement_lineEdit::dropFocus(){
    lineEdit->clearFocus();
}
#include "mutableelement_lineedit.h"
#include <QtGlobal>

MutableElement_lineEdit::MutableElement_lineEdit( // allows text boxes to be used
        QLineEdit* le,
        double low, double high, int precision, double def)
{
    lineEdit = le;

    QObject::connect(lineEdit, SIGNAL(returnPressed()),
                     this, SLOT(dropFocus())); // connect signals and slots for element

    QObject::connect(lineEdit, SIGNAL(editingFinished()),
                     this, SLOT(emitValChange())); // connect signals and slots for element


    int n = (qMax(QString::number(((int) low)).length(),
                  QString::number(((int) high)).length())
                  + precision) * 10;
    lineEdit->setMinimumWidth(60);
    lineEdit->setMaximumWidth(n);
    lineEdit->setAlignment(Qt::AlignRight);

    lineEdit->setText(QString::number(def));
    lineEdit->setValidator(new QDoubleValidator(low, high, precision, this));
}

void MutableElement_lineEdit::emitValChange(){ // used to link different mutable elements
    emit sig_valueChanged(lineEdit->text().toDouble());
}

void MutableElement_lineEdit::on_valueChanged(double newval){ // used to link different mutable elements
    lineEdit->setText(QString::number(newval));
}

void MutableElement_lineEdit::dropFocus(){
    lineEdit->clearFocus();
}

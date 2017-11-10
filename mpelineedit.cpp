#include "mutableparamelement.h"


MPElineEdit::MPElineEdit(double low, double high, int precision, double def,
            QWidget* parent): QLineEdit(parent){
    QObject::connect(this, SIGNAL(editingFinished()),
                     this, SLOT(emitValChange()));
    setText(QString::number(def));
    setValidator(new QDoubleValidator(low, high, precision, this));
}

void MPElineEdit::emitValChange(){
    emit sig_valueChanged(text().toDouble());
}

void MPElineEdit::on_valueChanged(double newval){
    setText(QString::number(newval));
}

#ifndef MUTABLEPARAMELEMENT_H
#define MUTABLEPARAMELEMENT_H

#include <QObject>
#include <QLineEdit>
#include <QSlider>
#include <Qtmath>
#include <QValidator>

class mutableParamElement: public QWidget{
    Q_OBJECT
signals:
    void sig_valueChanged(double newval);
private:
    virtual void emitValChange();
    virtual void on_valueChanged(double newval);
};

class mutableElement_lineEdit: public mutableParamElement{
    Q_OBJECT
public:
    explicit mutableElement_lineEdit(QLineEdit* le,
                double low, double high, int precision, double def);
private:
    QLineEdit* lineEdit;

    void emitValChange();
    void on_valueChanged(double newval);
};

class mutableElement_slider: public mutableParamElement{
    Q_OBJECT
public:
    explicit mutableElement_slider(QSlider* sl,
              double low, double high, int precision, double def);
private:
    QSlider* slider;

    int div;

    void emitValChange();
    void on_valueChanged(double newval);
};

#endif // MUTABLEPARAMELEMENT_H

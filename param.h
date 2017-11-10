#ifndef PARAM_H
#define PARAM_H

#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QSlider>
#include <QValidator>
#include <QtMath>

// Storage for a specific setting
class Param{
public:
    Param(QString nm, double def = 0.00);
    void addElement(QWidget* w);
    QString toString();
    double getValue(){return value;}

private:
    QList<QWidget*> elements;
    double value;
    QString name;

private slots:
    void on_valueChanged(double newval);
};

class MutableParamElement{
signals:
    void sig_valueChanged(double newval);
protected slots:
    virtual void on_valueChanged(double newval);
};

class MPElineEdit: public MutableParamElement, public QLineEdit{
public:
    MPElineEdit(double low, double high, int precision, double def,
                QWidget* parent = Q_NULLPTR): QLineEdit(parent){
        QObject::connect(this, SIGNAL(editingFinished()),
                         this, SLOT(emitValChange()));
        setText(QString::number(def));
        setValidator(new QDoubleValidator(low, high, precision, this));
    }
private:
    void emitValChange(){
        emit sig_valueChanged(text().toDouble());
    }

    void on_valueChanged(double newval){
        setText(QString::number(newval));
    }
};

class MPEslider: public MutableParamElement, public QSlider{
public:
    MPEslider(Qt::Orientation orientation,
              double low, double high, double step, int precision, double def,
              QWidget* parent = Q_NULLPTR): QSlider(orientation, parent){
        QObject::connect(this, SIGNAL(valueChanged(int)),
                         this, SLOT(emitValChange()));
        div = (int) qPow(10, precision);
        setTickInterval(step * div);
        setMinimum(low * div);
        setMaximum(high * div);
        setValue(def * div);
    }
private:
    int div;

    void emitValChange(){
        emit sig_valueChanged((double) value() / (double) div);
    }

    void on_valueChanged(double newval){
        setValue(newval * div);
    }
};

#endif // PARAM_H

#ifndef MUTABLEPARAMELEMENT_H
#define MUTABLEPARAMELEMENT_H

#include <QObject>
#include <QLineEdit>
#include <QSlider>
#include <Qtmath>
#include <QValidator>

class MutableParamElement : virtual public QObject
{
    Q_OBJECT
signals:
    void sig_valueChanged(double newval);
protected slots:
    virtual void on_valueChanged(double newval);
public slots:
};

class MPElineEdit: virtual public MutableParamElement, public QLineEdit{
    Q_OBJECT
public:
    MPElineEdit(double low, double high, int precision, double def,
                QWidget* parent = Q_NULLPTR);

private:
    void emitValChange();
    void on_valueChanged(double newval);
};

class MPEslider: virtual public MutableParamElement, public QSlider{
    Q_OBJECT
public:
    MPEslider(Qt::Orientation orientation,
              double low, double high, double step, int precision, double def,
              QWidget* parent = Q_NULLPTR);
private:
    int div;

    void emitValChange();
    void on_valueChanged(double newval);
};

#endif // MUTABLEPARAMELEMENT_H

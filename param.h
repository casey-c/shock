#ifndef PARAM_H
#define PARAM_H

#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QSlider>
#include <QValidator>
#include <QtMath>
#include "mutableparamelement.h"

// Storage for a specific setting
class Param: public QObject{
    Q_OBJECT
public:
    explicit Param(QString nm, double def = 0.00);
    void addVisualElement(QWidget* w);

    void addMutableElement(QSlider* w);
    void addMutableElement(QLineEdit* w);

    const QList<QWidget*> getElements();

    QString toString();
    double getValue(){return value;}

private:
    QList<QWidget*> elements;
    double value;

    double low;
    double high;
    int precision;

    QString name;

private slots:
    void on_valueChanged(double newval);
};

#endif // PARAM_H

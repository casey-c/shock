#ifndef PARAM_H
#define PARAM_H

#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QSlider>
#include <QValidator>
#include <QtMath>
#include "mutableparamelement.h"
#include "mutableelement_lineedit.h"
#include "mutableelement_slider.h"
#include "mutableelement_checkbox.h"

// Storage for a specific setting
class Param: public QObject{
    Q_OBJECT
public:
    explicit Param(QString nm, double def, double lo, double hi,
                   int precis);
    void addVisualElement(QWidget* w);

    void addMutableElement(QSlider* w);
    void addMutableElement(QLineEdit* w);
    void addMutableElement(QCheckBox* w);

    const QList<QWidget*> getElements();

    QString toString();
    double getValue(){return value;}

signals:
    void changeValue(double newval);

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

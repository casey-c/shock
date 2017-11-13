#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QHash>
#include "param.h"

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = 0);
    ~ControlPanel();

    int getTime();

    void addParam(Param* p);
    double getValue(QString key);
private slots:
    void on_infiniteSoundChk_toggled(bool checked);
    void on_time_changed();

private:
    Ui::ControlPanel *ui;
    QString alg;
    QHash<QString, Param*> data;

    bool infinite;
    int mins;
    int secs;

    void addRow(QList<QWidget*> widgets);
};

#endif // CONTROLPANEL_H

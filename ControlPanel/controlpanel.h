#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QHash>
#include <QLineEdit>
#include <QSlider>
#include <QDebug>
#include "algosettings.h"
#include "genealg.h"
#include "testalg.h"
#include "param.h"
#include "soundcontainer.h"

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
    void removeParam(Param* p);
    void setCont(SoundContainer* p) {cont = p;}
    double getValue(QString key);

signals:
    void loadGeneratedToWorkspace(QString);

private slots:
    void on_infiniteSoundChk_toggled(bool checked);
    void on_time_changed();
    void on_shockButton_pressed();

    void on_algComboBox_currentIndexChanged(int index);

private:
    Ui::ControlPanel *ui;
    QString alg;
    QHash<QString, Param*> data;

    AlgoSettings* settings;

    bool infinite;
    int mins;
    int secs;
    SoundContainer* cont;
    void addRow(QList<QWidget*> widgets);
    QString loc;
};

#endif // CONTROLPANEL_H

#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>

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
    double getRandomness();

private slots:
    void on_randomnessLE_returnPressed();
    void on_randomnessLE_editingFinished();
    void on_randomnessSlider_valueChanged(int value);
    void on_infiniteSoundChk_toggled(bool checked);
    void on_time_changed();

private:
    Ui::ControlPanel *ui;
    QString alg;
    double randomness;

    bool infinite;
    int mins;
    int secs;
};

#endif // CONTROLPANEL_H

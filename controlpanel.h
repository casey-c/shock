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

private slots:
    void on_randomnessLE_returnPressed();
    void on_randomnessLE_editingFinished();
    void on_randomnessSlider_sliderMoved(int position);
private:
    Ui::ControlPanel *ui;
    QString alg;
    float randomness;
};

#endif // CONTROLPANEL_H

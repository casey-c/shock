#include "controlpanel.h"
#include "ui_controlpanel.h"
#include <QLineEdit>

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

    ui->randomnessLE->setValidator(new QDoubleValidator(0.00, 1.00, 2, this));
    ui->minutesLE->setValidator(new QIntValidator(0, 59, this));
    ui->secondsLE->setValidator(new QIntValidator(0, 59, this));

    infinite = false;
    mins = 0;
    secs = 0;

    QObject::connect(ui->minutesLE, SIGNAL(returnPressed()), SLOT(on_time_changed()));
    QObject::connect(ui->secondsLE, SIGNAL(returnPressed()), SLOT(on_time_changed()));
}

ControlPanel::~ControlPanel()
{
    delete ui;
}

//return -1 if infinite, otherwise the length in seconds
int ControlPanel::getTime(){
    if(infinite) return -1;

    return mins * 60 + secs;
}

double ControlPanel::getRandomness(){
    return randomness;
}

void ControlPanel::on_randomnessLE_returnPressed()
{
    ui->randomnessLE->clearFocus();
}

void ControlPanel::on_randomnessLE_editingFinished()
{
    randomness = (ui->randomnessLE->text()).toDouble();
    ui->randomnessSlider->setValue((int) (randomness * 100));
}

void ControlPanel::on_randomnessSlider_valueChanged(int value)
{
    randomness = (double)value / 100;
    ui->randomnessLE->setText(QString::number(randomness));
}


void ControlPanel::on_infiniteSoundChk_toggled(bool checked)
{
    infinite = checked;

    ui->minutesLE->setEnabled(!checked);
    ui->secondsLE->setEnabled(!checked);
}

void ControlPanel::on_time_changed(){
    mins = ui->minutesLE->text().toInt();
    secs = ui->minutesLE->text().toInt();

    QLineEdit* le = qobject_cast<QLineEdit*>(sender());
    if(le->text().length() == 1){
        le->setText("0" + le->text());
    }
    le->clearFocus();
}

#include "controlpanel.h"
#include "ui_controlpanel.h"

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

    ui->randomnessLE->setValidator(new QDoubleValidator(0.00, 1.00, 2, this));
}

ControlPanel::~ControlPanel()
{
    delete ui;
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

void ControlPanel::on_randomnessSlider_sliderMoved(int position)
{
    randomness = (double)position / 100;
    ui->randomnessLE->setText(QString::number(randomness));
}


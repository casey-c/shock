#include "controlpanel.h"
#include "ui_controlpanel.h"
#include <QLineEdit>
#include <QDebug>

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);
    infinite = false; //initialize time settings
    mins = 0;
    secs = 0;

    QObject::connect(ui->minutesLE, SIGNAL(returnPressed()), SLOT(on_time_changed()));
    QObject::connect(ui->secondsLE, SIGNAL(returnPressed()), SLOT(on_time_changed()));


    Param* p = new Param("crab", 2.1);
    MPElineEdit* m = new MPElineEdit(-4.1, 7.4, 1, 2.1, this);


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


void ControlPanel::on_infiniteSoundChk_toggled(bool checked)
{
    infinite = checked;

    ui->minutesLE->setEnabled(!checked);
    ui->secondsLE->setEnabled(!checked);
}

void ControlPanel::on_time_changed(){
    //get time settings from line edits
    mins = ui->minutesLE->text().toInt();
    secs = ui->minutesLE->text().toInt();

    //make "12:6" look like time: "12:06"
    QLineEdit* le = qobject_cast<QLineEdit*>(sender());
    if(le->text().length() == 1){
        le->setText("0" + le->text());
    }
    le->clearFocus();
}

void ControlPanel::addRow(QList<QWidget*> widgets){
    QHBoxLayout* l = new QHBoxLayout();
    for(auto w: widgets){
        l->addWidget(w);
    }
    ui->scrlLayout->addLayout(l);
}

double ControlPanel::getValue(QString key){
    if(data.find(key) != data.end()){
        return data[key]->getValue();
    }else{
        return 0.00;
    }
}

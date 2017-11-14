#include "controlpanel.h"
#include "ui_controlpanel.h"

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

    settings = new AlgoSettings();

    Param* p;
    foreach(p, settings->getParams()){
        addParam(p);
    }
/*********************PARAM EXAMPLE************************/
    /*
    Param* p = new Param("prm", 3.33, -20, 50.44, 2);
    p->addVisualElement(new QLabel("value"));

    QSlider* s = new QSlider(Qt::Horizontal);
    p->addMutableElement(s);

    p->addVisualElement(new QLabel("here"));

    QLineEdit* le = new QLineEdit();
    p->addMutableElement(le);

    p->addVisualElement(new QLabel("ok"));

    QCheckBox* cb = new QCheckBox();
    p->addMutableElement(cb);

    addParam(p);

    qDebug() << "value of prm is" << getValue("prm");
*/

    /*********************PARAM EXAMPLE************************//*
    Param* p = new Param("Randomness", 0, 0, 1, 3);
    p->addVisualElement(new QLabel("Randomness"));

    QSlider* s = new QSlider(Qt::Horizontal);
    p->addMutableElement(s);

    //p->addVisualElement(new QLabel("here"));

    QLineEdit* le = new QLineEdit();
    p->addMutableElement(le);

    //p->addVisualElement(new QLabel("ok"));

    //QCheckBox* cb = new QCheckBox();
    //p->addMutableElement(cb);

    addParam(p);

    qDebug() << "value of prm is" << getValue("prm");*/
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
    l->setSpacing(4);
    l->setMargin(2);

    for(auto w: widgets){
        l->addWidget(w);
    }
    ui->scrlLayout->addLayout(l);
}

void ControlPanel::addParam(Param* p){
    data[p->getName()] = p;
    addRow(p->getElements());
}

double ControlPanel::getValue(QString key){
    if(data.find(key) != data.end()){
        return data[key]->getValue();
    }else{
        return 0.0;
    }
}

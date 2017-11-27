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

void ControlPanel::on_shockButton_pressed(){
    QString setting = settings->getName();
    QVector<QVector<float>> input = cont->getAllData();

    if(input.size() == 0)
        return;

    if(setting == "Genetic Algorithm"){
        GeneAlg* alg = new GeneAlg(settings);
        QVector<float> result = alg->run(input);

        for(float f: result)
            qDebug() << f;

        SF_INFO info;
        info.samplerate = 44100;
        info.channels = 1;
        info.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;

        qDebug() << sf_format_check(&info);

        SNDFILE* sf = sf_open("out.wav", SFM_WRITE, &info);

        sf_write_float(sf, result.data(), result.size());

        sf_close(sf);
    }
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

void ControlPanel::removeParam(Param *p){
    data.remove(p->getName());
}

double ControlPanel::getValue(QString key){
    if(data.find(key) != data.end()){
        return data[key]->getValue();
    }else{
        return 0.0;
    }
}

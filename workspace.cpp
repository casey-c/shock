#include "workspace.h"
#include "ui_workspace.h"
#include "waveformwidget.h"
#include "sound.h"

Workspace::Workspace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Workspace)
{

}

Workspace::~Workspace()
{
    delete ui;
}




void Workspace::loadSound(Sound* sound){
    this->snd = sound;
    this->soundLoaded = true;

    qDebug() << "trying to display waveform!!" << snd->getFileName();

    WaveformWidget* w = new WaveformWidget(this, snd->getFileName());
    //w->setMinimumHeight(40);

    qDebug() << "trying..." << w;


    //TODO I need help here. I have no clue how to get the UI to display the waveform :(

    ui->gridLayout->addWidget(w);
    //ui->workspaceWaveform->addWidget(w);


    qDebug() << "trying..." << w;

    ui->setupUi(this);
}

void Workspace::unloadSound()
{
    //this->snd = null;
    this->soundLoaded = false;
}

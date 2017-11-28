#include "workspace.h"
#include "ui_workspace.h"
#include "waveformwidget.h"
#include "Sound/sound.h"

Workspace::Workspace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Workspace)
{
    ui->setupUi(this);
    soundLoaded = false;
}

Workspace::~Workspace(){
    delete ui;
}

void Workspace::loadSound(Sound* sound){
    if(snd == sound){
        return;
    }

    if (soundLoaded) {
        unloadSound();
    }

    snd = sound;
    soundLoaded = true;

    dispWaveform = new WaveformWidget(this, snd->getFileName());
    ui->gridLayout->addWidget(dispWaveform);
}

void Workspace::validateSound(Sound* sound){
    if (snd == sound){
        unloadSound();
    }
}

void Workspace::unloadSound(){
    soundLoaded = false;
    qDebug() << "removing " << snd->getFileName() << " from workspace";
    ui->gridLayout->removeWidget(dispWaveform);

    //qDebug() << this->children();
    delete dispWaveform;

    ui->retranslateUi(this);
}

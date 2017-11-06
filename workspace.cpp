#include "workspace.h"
#include "ui_workspace.h"
#include "waveformwidget.h"
#include "sound.h"

Workspace::Workspace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Workspace)
{
    ui->setupUi(this);
    this->soundLoaded = false;
}

Workspace::~Workspace()
{
    delete ui;
}


void Workspace::loadSound(Sound* sound){

    if (this->soundLoaded) {
        unloadSound();
    }

    this->snd = sound;
    this->soundLoaded = true;




    WaveformWidget* w = new WaveformWidget(this, snd->getFileName());
    //w->setMinimumHeight(40);

    //w->setParent(this);

    //TODO I need help here. I have no clue how to get the UI to display the waveform :(

    //ui->frame->setLayout(ui->gridLayout);

    ui->gridLayout->addWidget(w);
    child = w;
}

void Workspace::unloadSound()
{
    // TODO need help here


    //this->snd = null;
    this->soundLoaded = false;
    qDebug() << "removing" << snd->getFileName();
    ui->gridLayout->removeWidget(child);

    qDebug() << this->children();
}

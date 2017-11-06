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

    ui->gridLayout->addWidget(w);
    child = w;
}

void Workspace::unloadSound()
{
    this->soundLoaded = false;
    qDebug() << "removing " << snd->getFileName() << " from workspace";
    ui->gridLayout->removeWidget(child);

    //qDebug() << this->children();
    delete child;

    ui->retranslateUi(this);
}

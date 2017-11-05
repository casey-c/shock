#include "workspace.h"
#include "ui_workspace.h"
#include "waveformwidget.h"
#include "sound.h"

Workspace::Workspace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Workspace)
{
    QObject::connect(parent, SIGNAL(addToWorkspace(snd)), SLOT(loadSound(snd)));
}

Workspace::~Workspace()
{
    delete ui;
}


void Workspace::loadSound(Sound* sound){
    this->snd = sound;
    this->soundLoaded = true;

    WaveformWidget* w = new WaveformWidget(this, snd->getFileName());
    w->setMinimumHeight(40);
    //ui->gridLayout->addWidget(w);
    ui->workspaceWaveform->addWidget(w);

    //ui->setupUi(this);
}

void Workspace::unloadSound()
{
    //this->snd = null;
    this->soundLoaded = false;
}

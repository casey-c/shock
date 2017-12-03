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

void Workspace::loadSound(SoundCard* sound){ // load a sound to the workspace
    if(snd == sound){ // if the same sound is already loaded, dont load it again
        return;
    }

    if (soundLoaded) { // remove the sound that is already there
        unloadSound();
    }

    snd = sound; // load the new sound
    soundLoaded = true;

    dispWaveform = new WaveformWidget(this, snd->getFileName()); // create the waveform for the new sound
    ui->gridLayout->addWidget(dispWaveform); // display the waveform
}

void Workspace::validateSound(SoundCard* sound){
    if (snd == sound){ // if the sound passed in is already loaded
        unloadSound(); // unload the current sound
    }
}

void Workspace::unloadSound(){ // unload the current sound
    soundLoaded = false;

    ui->gridLayout->removeWidget(dispWaveform); // remove the waveform display

    delete dispWaveform;

    ui->retranslateUi(this); // update UI
}

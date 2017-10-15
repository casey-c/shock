#include "soundcontainer.h"
#include "ui_soundcontainer.h"
#include <QDebug>

SoundContainer::SoundContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundContainer)
{
    ui->setupUi(this);
    ui->frame->setLayout(ui->verticalLayout);
}

SoundContainer::~SoundContainer()
{
    for(QList<Sound*>::iterator itr = sounds.begin(); itr != sounds.end(); ++itr){
        delete *itr;
    }

    delete ui;
}

void SoundContainer::addSound(Sound* snd){
    ui->sndLayout->insertWidget(ui->sndLayout->count() - 1, snd);
    sounds.push_back(snd);
    QObject::connect(snd, SIGNAL(sig_shiftUp()), SLOT(shiftSndUp()));
    QObject::connect(snd, SIGNAL(sig_shiftDown()), SLOT(shiftSndDown()));
}

void SoundContainer::on_btnAdd_clicked()
{
    QStringList snds = QFileDialog::getOpenFileNames(this,
                                 "Import Sample",
                                 "",
                                 "Audio files (*.wav *.mp3)");

    for(QList<QString>::const_iterator itr = snds.begin(); itr != snds.end(); ++itr){
        Sound* snd = new Sound(this, *itr);
        addSound(snd);
    }
}

void SoundContainer::on_btnRemove_clicked()
{
    for(QList<Sound*>::iterator itr = sounds.begin(); itr != sounds.end(); ++itr){
        if((*itr)->selected()){
            Sound* snd = *itr;
            ui->sndLayout->removeWidget(snd);
            itr = sounds.erase(itr); --itr;
            delete snd;
        }
    }
}

void SoundContainer::shiftSoundPos(Sound* const &snd, int offset){
    int curIdx = ui->sndLayout->indexOf(snd);

    if(curIdx == -1 || curIdx + offset < 0 || curIdx + offset >= ui->sndLayout->count() - 1)
        return;

    ui->sndLayout->removeWidget(snd);
    ui->sndLayout->insertWidget(curIdx + offset, snd);
}

void SoundContainer::shiftSndDown(){
    shiftSoundPos(qobject_cast<Sound*>(sender()), 1);
}

void SoundContainer::shiftSndUp(){
    shiftSoundPos(qobject_cast<Sound*>(sender()), -1);
}

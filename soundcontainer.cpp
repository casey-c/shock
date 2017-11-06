#include "soundcontainer.h"
#include "ui_soundcontainer.h"
#include <QDebug>
#include <QScrollBar>

SoundContainer::SoundContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundContainer)
{
    ui->setupUi(this);
    ui->frame->setLayout(ui->verticalLayout);
    QObject::connect(this->parentWidget(),
                     SIGNAL(sig_sndFileDropped(QString)), SLOT(on_sndFileDropped(QString)));
}

SoundContainer::~SoundContainer()
{
    for(QList<Sound*>::iterator itr = sounds.begin(); itr != sounds.end(); ++itr){
        delete *itr;
    }

    delete ui;
}

int SoundContainer::size(){
    return sounds.size();
}

void SoundContainer::addSound(Sound* snd){
    ui->sndLayout->insertWidget(ui->sndLayout->count() - 1, snd);
    qApp->processEvents();//make sure the widget has drawn fully
    qApp->processEvents();//(apparently this takes 2)

    ui->scrollArea->verticalScrollBar()//then scroll down to see new sound
            ->triggerAction(QAbstractSlider::SliderToMaximum);

    snd->setVolumeMod(ui->tabVolSlider->value());

    sounds.push_back(snd);

    QObject::connect(snd, SIGNAL(sig_shiftUp()), SLOT(shiftSndUp()));
    QObject::connect(snd, SIGNAL(sig_shiftDown()), SLOT(shiftSndDown()));
    QObject::connect(snd, SIGNAL(sig_loadSoundToWorkspace(Sound*)), this, SLOT(loadSoundToWorkspace(Sound*)));
}

void SoundContainer::loadSoundToWorkspace(Sound* snd) {
    emit sig_loadToWorkspace(snd);
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

void SoundContainer::removeSound(Sound* snd){
    ui->sndLayout->removeWidget(snd);
    sounds.removeOne(snd);
    delete snd;
}

//remove all selected sounds
void SoundContainer::on_btnRemove_clicked()
{
    QList<Sound*>::iterator itr = sounds.begin();
    while(itr != sounds.end()){

        //if the sound is selected, remove it
        if((*itr)->selected()){
            Sound* snd = *itr;
            removeSound(snd);
            if(!sounds.empty()){
                itr = sounds.begin();
                continue;
            }
        }

        ++itr;
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


void SoundContainer::on_btnSelectAll_clicked()
{
    for(QList<Sound*>::iterator itr = sounds.begin(); itr != sounds.end(); ++itr){
        (*itr)->setSelected(true);
    }
}

void SoundContainer::on_btnDeselectAll_clicked()
{
    for(QList<Sound*>::iterator itr = sounds.begin(); itr != sounds.end(); ++itr){
        (*itr)->setSelected(false);
    }
}

void SoundContainer::on_tabVolSlider_valueChanged(int position)
{
    for(QList<Sound*>::iterator itr = sounds.begin(); itr != sounds.end(); ++itr){
        (*itr)->setVolumeMod(position);
    }
}

void SoundContainer::on_sndFileDropped(QString path){
    Sound* snd = new Sound(this, path);
    addSound(snd);
}

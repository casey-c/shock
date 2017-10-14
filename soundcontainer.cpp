#include "soundcontainer.h"
#include "ui_soundcontainer.h"

SoundContainer::SoundContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundContainer)
{
    ui->setupUi(this);
    ui->frame->setLayout(ui->verticalLayout);
    //ui->scrollAreaWidgetContents->setLayout(ui->soundLayout);
}

SoundContainer::~SoundContainer()
{
    for(QList<Sound*>::iterator itr = sounds.begin(); itr != sounds.end(); ++itr){
        delete *itr;
    }

    delete ui;
}

void SoundContainer::addSound(Sound* snd){
    ui->sndLayout->addWidget(snd);
    ui->sndLayout->removeItem(ui->vSpacer);
    ui->sndLayout->addSpacerItem(ui->vSpacer);
    sounds.push_back(snd);
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

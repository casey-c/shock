#include "soundcontainer.h"
#include "ui_soundcontainer.h"

SoundContainer::SoundContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundContainer)
{
    ui->setupUi(this);
    ui->frame->setLayout(ui->verticalLayout);
    ui->scrollAreaWidgetContents->setLayout(ui->soundLayout);
}

SoundContainer::~SoundContainer()
{
    for(QList<Sound*>::iterator itr = sounds.begin(); itr != sounds.end(); ++itr){
        removeSound(*itr);
    }

    delete ui;
}

void SoundContainer::addSound(Sound* snd){
    ui->soundLayout->addWidget(snd);
    snd->show();
    sounds.append(snd);

    ui->verticalLayout->removeItem(ui->vertSpacer);
    ui->verticalLayout->addSpacerItem(ui->vertSpacer);
}

void SoundContainer::removeSound(Sound* snd){
    ui->soundLayout->removeWidget(snd);
    sounds.removeOne(snd);
    delete snd;
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

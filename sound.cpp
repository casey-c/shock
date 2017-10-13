#include "sound.h"
#include "ui_sound.h"
#include <QDebug>

Sound::Sound(QWidget *parent, QString fn) :
    QWidget(parent),
    ui(new Ui::Sound)
{
    ui->setupUi(this);
    setPath(fn);
}

QString Sound::getFileName()
{
    return this->fileName;
}

void Sound::setPath(QString fn)
{
    this->fileName = fn;
    player.setMedia(QUrl::fromLocalFile(fn));
}

void Sound::play(){
    player.play();
}

void Sound::pause(){
    player.pause();
}

void Sound::stop(){
    player.stop();
}

Sound::~Sound()
{
    delete ui;
}

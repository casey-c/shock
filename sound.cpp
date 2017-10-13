#include "sound.h"
#include "ui_sound.h"

Sound::Sound(QWidget *parent, QString fn) :
    QWidget(parent),
    ui(new Ui::Sound)
{
    ui->setupUi(this);

    this->fileName = fn;
}

QString Sound::getFileName()
{
    return this->fileName;
}

void Sound::setPath(QString fn)
{
    this->fileName = fn;
}



Sound::~Sound()
{
    delete ui;
}

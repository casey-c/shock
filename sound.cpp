#include "sound.h"
#include "ui_sound.h"
#include <QDebug>
#include <QRegExp>

Sound::Sound(QWidget *parent, QString fn) :
    QWidget(parent),
    ui(new Ui::Sound)
{
    ui->setupUi(this);
    setPath(fn);
    ui->label->setText(fn.replace(QRegExp(".+/"), ""));
}

Sound::~Sound()
{
    delete ui;
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

void Sound::on_btnPlay_clicked()
{
    play();
}

void Sound::on_btnPause_clicked()
{
    pause();
}

void Sound::on_btnStop_clicked()
{
    stop();
}

bool Sound::selected(){
    return ui->checkBox->isChecked();
}

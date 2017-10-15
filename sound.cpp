#include "sound.h"
#include "ui_sound.h"
#include <QDebug>
#include <QRegExp>
#include <soundcontainer.h>

Sound::Sound(QWidget *parent, QString fn) :
    QWidget(parent),
    ui(new Ui::Sound)
{
    ui->setupUi(this);
    setPath(fn);
    ui->leName->setText(fn.replace(QRegExp(".+/"), ""));

    QPalette palette = ui->leName->palette();
    QColor color = palette.color( QPalette::Disabled, QPalette::Base );
    palette.setColor( QPalette::Normal, QPalette::Base, color );
    ui->leName->setPalette( palette );
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

void Sound::on_btnShiftUp_clicked()
{
    emit sig_shiftUp();
}

void Sound::on_btnShiftDown_clicked()
{
    emit sig_shiftDown();
}

void Sound::on_leName_returnPressed()
{
    ui->leName->clearFocus();
}

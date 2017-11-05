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

void Sound::setSelected(bool selected){
    ui->checkBox->setChecked(selected);
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

void Sound::setVolumeMod(int x){
    volumeMod = x;
    adjustVolume();
}

void Sound::adjustVolume(){
    // slider value and volume modifier in the range [0..100]

    qreal value = (volumeMod / qreal(100.0)) * ui->sliderVol->value();

    qreal linearVolume = QAudio::convertVolume( value / qreal(100.0),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);

    actualVolume = qRound(linearVolume * 100);
    player.setVolume(actualVolume);
}

void Sound::on_sliderVol_sliderMoved(){
    adjustVolume();
}

bool Sound::validSoundFile(QString path){
    QFileInfo fi(path);
    return fi.isFile() && fi.suffix() == "wav" || fi.suffix() == "mp3";
}

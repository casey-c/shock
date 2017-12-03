#include "sound.h"
#include "ui_sound.h"
#include <QDebug>
#include <QRegExp>
#include <QFileInfo>

//create a new sound widget with filepath fn
Sound::Sound(QWidget *parent, QString fn, QString fileText) :
    QWidget(parent),
    ui(new Ui::Sound)
{
    ui->setupUi(this);
    setPath(fn);

    if (fileText == "")
        ui->leName->setText(fn.replace(QRegExp(".+/"), "")); //strip folders off of filename and display it
    else
        ui->leName->setText((fileText));

    //set the background of the line edit to match the background
    // (so it looks like a label but it's editable)
    QPalette palette = ui->leName->palette();
    QColor color = palette.color( QPalette::Disabled, QPalette::Base );
    palette.setColor( QPalette::Normal, QPalette::Base, color );
    ui->leName->setPalette( palette );

}

Sound::~Sound() {
    delete ui;
}

QString Sound::getFileName() {
    return this->fileName;
}

void Sound::setPath(QString fn) {
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

void Sound::on_btnPlay_clicked() {
    play();
}

void Sound::on_btnPause_clicked() {
    pause();
}

void Sound::on_btnStop_clicked() {
    stop();
}

bool Sound::selected(){
    return ui->checkBox->isChecked();
}

void Sound::on_btnShiftUp_clicked() {
    emit sig_shiftUp();
}

void Sound::on_btnShiftDown_clicked() {
    emit sig_shiftDown();
}

void Sound::on_leName_returnPressed() {
    ui->leName->clearFocus();
}

void Sound::setVolumeMod(int x){
    volumeMod = x;
    adjustVolume();
}

void Sound::adjustVolume(){
    // slider value and volume modifier in the range [0..100]

    qreal value = (volumeMod / qreal(100.0)) * ui->sliderVol->value();

    //convert from logarithmic scale to linear
    qreal linearVolume = QAudio::convertVolume( value / qreal(100.0),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);

    actualVolume = qRound(linearVolume * 100);
    player.setVolume(actualVolume);
}

void Sound::on_sliderVol_valueChanged(){
    adjustVolume();
}

void Sound::on_loadToWorkspace_clicked() {
    emit sig_loadSoundToWorkspace(this);
}

bool Sound::validSoundFile(QString path){
    QFileInfo fi(path);
    return (fi.isFile()) && (fi.suffix() == "wav");
}

QString Sound::getText() {
    return ui->leName->text();
}

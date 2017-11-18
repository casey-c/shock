#include "soundcard.h"
#include "ui_soundcard.h"
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>

SoundCard::SoundCard(QWidget *parent, QString sndFile) :
    QWidget(parent),
    ui(new Ui::SoundCard),
    firstClick(true)
{
    ui->setupUi(this);
    setStyleSheet(":hover {background-color: #eeeeee;}");
    QObject::connect(ui->leName, SIGNAL(returnPressed()),
                     this, SLOT(finishNameEdit()));

    soundFile = sndFile;
    ui->leName->setText(sndFile.replace(QRegExp(".+/"), ""));
    setupMediaPlayer();

    contextMenu = new QMenu();

    QAction* a = new QAction("Remove");
    QObject::connect(a, SIGNAL(triggered()),
                     this, SLOT(removeSelf()));
    contextMenu->addAction(a);

    a = new QAction("Add To Workspace");
    QObject::connect(a, SIGNAL(triggered()),
                     this, SLOT(addSelfToWorkspace()));
    contextMenu->addAction(a);

    a = new QAction("Save A Copy As...");
    QObject::connect(a, SIGNAL(triggered()),
                     this, SLOT(saveCopyOfSelf()));
    contextMenu->addAction(a);
}

void SoundCard::removeSelf(){
    emit removeMe(this);
}

void SoundCard::addSelfToWorkspace(){
    emit addMeToWorkspace(this);
}

void SoundCard::saveCopyOfSelf(){
    //todo
}

void SoundCard::openContextMenu(){
    contextMenu->exec(QCursor::pos());
}

void SoundCard::mousePressEvent(QMouseEvent* evt) {
    if (evt->button() & Qt::RightButton){
        openContextMenu();
    }
    else if (evt->button() & Qt::LeftButton){
        if (firstClick){
            qDebug() << "single click";
            firstClick = false;
            QTimer::singleShot(500, this, SLOT(doubleClickExpired()));
        }
        else{
            qDebug() << "double click";
            addSelfToWorkspace();
        }
    }
    QWidget::mousePressEvent(evt);
}

SoundCard::~SoundCard(){
    delete ui;
}


void SoundCard::doubleClickExpired() {
    //qDebug() << "double click expired";
    if (!firstClick)
        firstClick = true;
}

void SoundCard::finishNameEdit(){
    ui->leName->clearFocus();
}

void SoundCard::updateSeekBar(qint64 pos){
    if(!ui->seekBar->isSliderDown()){
        ui->seekBar->setValue(
            ((double)pos / (double)mediaPlayer->duration())
            * ui->seekBar->maximum());
    }
}

void SoundCard::seekTo(int pos){
    mediaPlayer->setPosition(
                ((double)pos / (double)ui->seekBar->maximum())
                * mediaPlayer->duration());
}

void SoundCard::setupMediaPlayer(){
    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setNotifyInterval(200);
    mediaPlayer->setMedia(
                QMediaContent(
                    QUrl::fromLocalFile(soundFile)));

    QObject::connect(mediaPlayer, SIGNAL(positionChanged(qint64)),
                     this, SLOT(updateSeekBar(qint64)));

    QObject::connect(ui->seekBar, SIGNAL(sliderMoved(int)),
                     this, SLOT(seekTo(int)));

    QObject::connect(ui->seekBar, SIGNAL(sliderPressed()),
                     this, SLOT(toggleSeeking()));

    QObject::connect(ui->seekBar, SIGNAL(sliderReleased()),
                     this, SLOT(toggleSeeking()));

    QObject::connect(ui->btnStop, SIGNAL(pressed()),
                     this, SLOT(stopPlayback()));

    QObject::connect(ui->btnPlayPause, SIGNAL(pressed()),
                     this, SLOT(togglePlayback()));
}

void SoundCard::togglePlayback(){
    if(mediaPlayer->state() == QMediaPlayer::PlayingState){
        mediaPlayer->pause();
        ui->btnPlayPause->setIcon(QIcon(":/icons/play.svg"));
    }
    else{
        mediaPlayer->play();
        ui->btnPlayPause->setIcon(QIcon(":/icons/pause.svg"));
    }
}

void SoundCard::toggleSeeking(){
    static int i = 0;
    static bool wasPlaying = false;

    if(i == 0){
        wasPlaying = mediaPlayer->state() == QMediaPlayer::PlayingState;
        mediaPlayer->pause();
        ++i;
    }else{
        i = 0;
        if(wasPlaying)
            mediaPlayer->play();
    }
}

void SoundCard::stopPlayback(){
    mediaPlayer->stop();
    ui->btnPlayPause->setIcon(QIcon(":/icons/play.svg"));
}

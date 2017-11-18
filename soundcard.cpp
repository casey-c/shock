#include "soundcard.h"
#include "ui_soundcard.h"
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>

SoundCard::SoundCard(QWidget *parent, QString soundFile) :
    QWidget(parent),
    ui(new Ui::SoundCard),
    firstClick(true)
{
    ui->setupUi(this);
    setStyleSheet(":hover {background-color: #eeeeee;}");
    QObject::connect(ui->leName, SIGNAL(returnPressed()),
                     this, SLOT(finishNameEdit()));

    mediaPlayer = new QMediaPlayer();

    QObject::connect(mediaPlayer, SIGNAL(positionChanged(qint64)),
                     this, SLOT(updateSeekBar(qint64)));

    QObject::connect(ui->seekBar, SIGNAL(sliderMoved(int)),
                     this, SLOT(seekTo(int)));

    QObject::connect(ui->seekBar, SIGNAL(sliderPressed()),
                     mediaPlayer, SLOT(pause()));

    QObject::connect(ui->seekBar, SIGNAL(sliderReleased()),
                     mediaPlayer, SLOT(play()));

    mediaPlayer->setMedia(
                QMediaContent(
                    QUrl::fromLocalFile(soundFile)));

    mediaPlayer->setNotifyInterval(200);
    mediaPlayer->play();

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

#include "soundcard.h"
#include "ui_soundcard.h"
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QFileInfo>
#include <QFileDialog>
#include "Workspace/audioutil.h"

SoundCard::SoundCard(QWidget *parent, QString sndFile) :
    QWidget(parent),
    ui(new Ui::SoundCard),
    firstClick(true)
{
    ui->setupUi(this);
    setStyleSheet(":hover {background-color: #eeeeee;}");
    QObject::connect(ui->leName, SIGNAL(returnPressed()),
                     this, SLOT(finishNameEdit()));

    fileName = sndFile;
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

    QObject::connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
                     this, SLOT(mpStateChange(QMediaPlayer::State)));
}

void SoundCard::removeSelf(){
    emit removeMe(this);
}

void SoundCard::addSelfToWorkspace(){
    emit addMeToWorkspace(this);
}

void SoundCard::saveCopyOfSelf(){
    QString savefile = QFileDialog::getSaveFileName((QWidget*)this->parent(),tr("Save Project Settings"),"",tr("Sound file (*.wav)"));
    savefile.append(".wav");

    SF_INFO fInfo;
    fInfo.format = 0;

    SF_INFO sInfo;

    SNDFILE* orig = sf_open(fileName.toLatin1().data(), SFM_READ, &fInfo);

    sInfo.samplerate = fInfo.samplerate;
    sInfo.channels = fInfo.channels;
    sInfo.format = fInfo.format;

    SNDFILE* cpy = sf_open(savefile.toLatin1().data(), SFM_WRITE, &sInfo);

    //QVector<double> datapts;
    double d;
    while(sf_read_double(orig, &d, 1) > 0){
        sf_write_double(cpy, &d, 1);
    }

    sf_close(cpy);
    sf_close(orig);
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
            emit addMeToWorkspace(this);
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

//change the seekbar's position to match the mediaplayer
void SoundCard::updateSeekBar(qint64 pos){
    if(!ui->seekBar->isSliderDown()){
        double mediaPositionRatio = (double)pos / (double)mediaPlayer->duration();
        ui->seekBar->setValue(
            mediaPositionRatio * ui->seekBar->maximum());
    }
}

//change the mediaplayer's position to match the seekbar
void SoundCard::seekTo(int pos){
    double seekBarRatio = (double)pos / (double)ui->seekBar->maximum();
    mediaPlayer->setPosition(
                seekBarRatio * mediaPlayer->duration());
}

//initialize media, connect signals and slots for media player
void SoundCard::setupMediaPlayer(){
    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setNotifyInterval(200);
    mediaPlayer->setMedia(
                QMediaContent(
                    QUrl::fromLocalFile(fileName)));
//seeking
    QObject::connect(mediaPlayer, SIGNAL(positionChanged(qint64)),
                     this, SLOT(updateSeekBar(qint64)));

    QObject::connect(ui->seekBar, SIGNAL(sliderMoved(int)),
                     this, SLOT(seekTo(int)));

    QObject::connect(ui->seekBar, SIGNAL(sliderPressed()),
                     this, SLOT(toggleSeeking()));

    QObject::connect(ui->seekBar, SIGNAL(sliderReleased()),
                     this, SLOT(toggleSeeking()));

//stop & play/pause
    QObject::connect(ui->btnStop, SIGNAL(pressed()),
                     this, SLOT(stopPlayback()));

    QObject::connect(ui->btnPlayPause, SIGNAL(pressed()),
                     this, SLOT(togglePlayback()));
}

//play or pause the media and change button icon
// depending on current state
void SoundCard::togglePlayback(){
    if(mediaPlayer->state() == QMediaPlayer::PlayingState){
        mediaPlayer->pause();
    }else{
        mediaPlayer->play();
    }
}

//fires when the seekbar is pressed or released:
// pressing saves the state (playing or paused) and pauses media,
// releasing restores the previous state
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

// (static) valid path of a sound
bool SoundCard::validSoundFile(QString path){
    QFileInfo fi(path);
    return (fi.isFile()) && (fi.suffix() == "wav");
}

//stop media and update icon
void SoundCard::stopPlayback(){
    mediaPlayer->stop();
}

QVector<float> SoundCard::getData(){
    AudioUtil* util = new AudioUtil(fileName);
    QVector<double> d2 = util->getAllFrames();
    QVector<float> data;
    for (int i=0; i < d2.length(); ++i) {
        data.push_back((float)d2[i]);
    }

    return data;
}

QString SoundCard::getText(){
    return ui->leName->text();
}

void SoundCard::setText(QString txt){
    ui->leName->setText(txt);
}


void SoundCard::adjustVolume(){
    // slider value and volume modifier in the range [0..100]

    qreal value = ui->verticalSlider->value();

    //convert from logarithmic scale to linear
    qreal linearVolume = QAudio::convertVolume( value / qreal(100.0),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);

    actualVolume = qRound(linearVolume * 100);
    mediaPlayer->setVolume(actualVolume);
}

void SoundCard::on_verticalSlider_valueChanged(){
    adjustVolume();
}

void SoundCard::mpStateChange(QMediaPlayer::State s){
    if(s != QMediaPlayer::PlayingState){
        ui->btnPlayPause->setIcon(QIcon(":/icons/play.svg"));
    }else{
        ui->btnPlayPause->setIcon(QIcon(":/icons/pause.svg"));
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sound.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mediaPlaylist(new QMediaPlaylist),
    mediaPlayer(new QMediaPlayer)
{
    mediaPlayer->setPlaylist(mediaPlaylist);
    ui->setupUi(this);
    sndCont = new SoundContainer();
    ui->tab->setLayout(ui->grLayout);
    ui->grLayout->addWidget(sndCont);
    QVector<Sound*> soundVector;
}

MainWindow::~MainWindow()
{
    delete sndCont;
    delete ui;
    delete mediaPlaylist;
    delete mediaPlayer;
}

void MainWindow::loadIntoClearedPlaylist()
{
   QString fileName = QFileDialog::getOpenFileName(this,
                                                   "Import Sample",
                                                   "",
                                                   "Audio files (*.wav *.mp3)");
   qDebug() << fileName;
   mediaPlaylist->clear();
   mediaPlaylist->addMedia(QUrl::fromLocalFile(fileName));
   mediaPlaylist->setCurrentIndex(1);
}

void MainWindow::loadNewSound()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Import Sample",
                                                    "",
                                                    "Audio files (*.wav *.mp3)");
    qDebug() << fileName;
    Sound *s = new Sound(0, fileName);
    //s->setPath(fileName);
    soundVector.append(s);

    qDebug() << s->getFileName();

}

void MainWindow::on_open_file_button_clicked()
{
    //loadIntoClearedPlaylist();
    loadNewSound();
}

void MainWindow::on_play_sound_button_clicked()
{
    mediaPlaylist->clear();
    for (int i=0; i < soundVector.size(); ++i)
    {
        qDebug() << i << soundVector[i]->getFileName();
        mediaPlaylist->addMedia(QUrl::fromLocalFile(soundVector[i]->getFileName()));
    }

    mediaPlayer->play();
}

void MainWindow::on_pause_sound_button_clicked()
{
    mediaPlayer->pause();
}

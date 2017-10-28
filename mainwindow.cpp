#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sound.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QVector>

#include "ga.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mediaPlaylist(new QMediaPlaylist),
    mediaPlayer(new QMediaPlayer)
{
    abtWindow = nullptr;
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

void MainWindow::on_actionAbout_triggered()
{
    if(abtWindow != nullptr){
        delete abtWindow;
    }

    abtWindow = new AboutWindow();
    abtWindow->show();
    abtWindow->raise();
}

void MainWindow::on_shockButton_clicked(){
    //GA shock = new GA();
}

/*
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
*/

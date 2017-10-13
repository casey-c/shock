#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>

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

void MainWindow::on_open_file_button_clicked()
{
    loadIntoClearedPlaylist();
}

void MainWindow::on_play_sound_button_clicked()
{
    mediaPlayer->play();
}

void MainWindow::on_pause_sound_button_clicked()
{
    mediaPlayer->pause();
}

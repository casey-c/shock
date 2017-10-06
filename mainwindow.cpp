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
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
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

}

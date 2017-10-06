#include "mainwindow.h"
#include "ui_mainwindow.h"

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

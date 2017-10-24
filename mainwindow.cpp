#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    abtWindow = nullptr;
    mediaPlayer->setPlaylist(mediaPlaylist);
    ui->setupUi(this);
    sndCont = new SoundContainer();
    ui->tab1->setLayout(ui->grLayout);
    ui->grLayout->addWidget(sndCont);
    QVector<Sound*> soundVector;

    ctrlPanel = new ControlPanel();
    ui->gridFrame->layout()->addWidget(ctrlPanel);
}

MainWindow::~MainWindow()
{
    delete sndCont;
    delete ui;
    delete mediaPlaylist;
    delete mediaPlayer;
    delete ctrlPanel;
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

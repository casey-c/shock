#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waveformwidget.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    abtWindow = nullptr;
    ui->setupUi(this);
    sndCont = new SoundContainer();
    ui->tab1->setLayout(ui->grLayout);
    ui->grLayout->addWidget(sndCont);

    QObject::connect(sndCont, SIGNAL(sig_loadToWorkspace(Sound*)), this, SLOT(loadSoundToWorkspace(Sound*)));
    ctrlPanel = new ControlPanel();
    ui->gridFrame->layout()->addWidget(ctrlPanel);

    workspace = new Workspace();
    ui->shockframe->layout()->removeWidget(ui->shockButton);
    ui->shockframe->layout()->addWidget(workspace);
    ui->shockframe->layout()->addWidget(ui->shockButton);


    QObject::connect(this, SIGNAL(sig_loadSndToWorkspace(Sound*)), workspace, SLOT(loadSound(Sound*)));
}

MainWindow::~MainWindow()
{
    delete sndCont;
    delete ui;
    delete ctrlPanel;
    delete workspace;
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

void MainWindow::loadSoundToWorkspace(Sound* snd)
{
    emit sig_loadSndToWorkspace(snd);
}

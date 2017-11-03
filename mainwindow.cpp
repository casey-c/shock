#include "mainwindow.h"
#include "ui_mainwindow.h"
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

    ctrlPanel = new ControlPanel();
    ui->gridFrame->layout()->addWidget(ctrlPanel);

    workspace = new Workspace();
    ui->shockframe->layout()->removeWidget(ui->shockButton);
    ui->shockframe->layout()->addWidget(workspace);
    ui->shockframe->layout()->addWidget(ui->shockButton);
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

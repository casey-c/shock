#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindow.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutWindow* abtWindow = new AboutWindow();
    abtWindow->show();
}

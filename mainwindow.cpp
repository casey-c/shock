#include "mainwindow.h"
#include "ui_mainwindow.h"
<<<<<<< Updated upstream
=======
#include "aboutwindow.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
>>>>>>> Stashed changes

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

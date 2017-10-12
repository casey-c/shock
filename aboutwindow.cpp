#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    ui->lblAbout->setTextFormat(Qt::RichText);
    ui->lblAbout->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->lblAbout->setOpenExternalLinks(true);


    ui->lblAbout->setText(QString("Team Shock:<br>Brian Mottola<br>Casey Conway\
                          <br>Jesse Zhou\nShamus Cardon<br><br>\
                           <a href=\"https://github.com/casey-c/shock\">GitHub</a>"));
}

AboutWindow::~AboutWindow()
{
    delete ui;
}

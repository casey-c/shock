#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    ui->sectionsGrBox->setLayout(ui->verticalLayout);

    lbls.push_back(new QLabel(QString("Overview")));
    lbls.push_back(new QLabel(QString("Other")));
    ui->verticalLayout->addWidget(lbls[0]);
    ui->verticalLayout->addWidget(lbls[1]);

    ui->lblAbout->setTextFormat(Qt::RichText);
    ui->lblAbout->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->lblAbout->setOpenExternalLinks(true);


    ui->lblAbout->setText(QString("<b>Team Shock:</b><br>Brian Mottola<br>Casey Conway\
                          <br>Jesse Zhou<br>Shamus Cardon<br><br>\
                           <a href=\"https://github.com/casey-c/shock\">GitHub</a>"));
}

AboutWindow::~AboutWindow()
{
    for(int i = 0; i < lbls.size(); ++i)
        delete lbls[i];

    delete ui;
}

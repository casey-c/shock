#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint); //remove "?" button
    ui->sectionsGrBox->setLayout(ui->verticalLayout);

    addButton("The Project");
    addButton("The Developers");
    addButton("Other");

    //stick the spacer under the buttons
    ui->verticalLayout->removeItem(ui->verticalSpacer);
    ui->verticalLayout->addItem(ui->verticalSpacer);


    //format the text (html, wordwrap)
    ui->lblAbout->setTextFormat(Qt::RichText);
    ui->lblAbout->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->lblAbout->setOpenExternalLinks(true);
    ui->lblAbout->setWordWrap(true);
}

//add a button to the about window
void AboutWindow::addButton(QString name){
    QPushButton* btn = new QPushButton(QString(name));
    sectionBtns.push_back(btn);
    ui->verticalLayout->addWidget(btn);
    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(on_sectionBtn_clicked()));
    btn->setFlat(true);
}

void AboutWindow::on_sectionBtn_clicked(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString btnText = buttonSender->text();
    qint32 btnNum;

    QString bold = "QPushButton {\
        font-size: 8pt;\
        font-weight: bold;\
    }";

    QString normal = "QPushButton {\
        font-size: 8pt;\
    }";

    for(int i = 0; i < sectionBtns.size(); ++i){
        sectionBtns[i]->setStyleSheet(normal);

        if(btnText == sectionBtns[i]->text())
            btnNum = i;
    }

    sectionBtns[btnNum]->setStyleSheet(bold);

    QString txt;
    if(btnNum == 0){
        txt = "<b>Shock</b><br>\
               Shock is a program that uses machine learning \
               techniques to manufacture new sounds that imitate \
               existing ones, the results of which can be used in a \
               large variety of applications.";
    }
    else if(btnNum == 1){
        txt = "<b>Team Shock</b><br>Brian Mottola<br>Casey Conway\
               <br>Jesse Zhou<br>Shamus Cardon<br><br>\
               <a href=\"https://github.com/casey-c/shock\">GitHub</a>";
    }
    else if(btnNum == 2){
        txt = ":)";
    }

    ui->lblAbout->setText(txt);
}

AboutWindow::~AboutWindow()
{
    for(int i = 0; i < sectionBtns.size(); ++i)
        delete sectionBtns[i];

    delete ui;
}

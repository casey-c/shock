#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint); //remove "?" button
    ui->sectionsGrBox->setLayout(ui->verticalLayout);

    initSectionText();

    addButton("The Project", "proj");
    addButton("The Developers", "devs");
    addButton("Getting Started", "getstart");
    addButton("Other", "other");

    //stick the spacer under the buttons
    ui->verticalLayout->removeItem(ui->verticalSpacer);
    ui->verticalLayout->addItem(ui->verticalSpacer);

    //format the text (html, wordwrap)
    ui->lblAbout->setTextFormat(Qt::RichText);
    ui->lblAbout->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->lblAbout->setOpenExternalLinks(true);
    ui->lblAbout->setWordWrap(true);
}

void AboutWindow::initSectionText(){
    sectionText["proj"] = "<b>Shock</b><br>\
               Shock is a program that uses machine learning \
               techniques to manufacture new sounds that imitate \
               existing ones, the results of which can be used in a \
               large variety of applications.";
    sectionText["devs"] = "<b>Team Shock</b><br>Brian Mottola<br>Casey Conway\
               <br>Jesse Zhou<br>Shamus Cardon<br><br>\
               <a href=\"https://github.com/casey-c/shock\">GitHub</a>";
    sectionText["getstart"] = "<b>Getting Started</b><br> \
               If you use this program you're probably \
               a very bright individual so figure it out.";
    sectionText["other"] = ":)";
}

//add a button to the about window
void AboutWindow::addButton(QString btnLabel, QString whichDesc){
    QPushButton* btn = new QPushButton(QString(btnLabel));
    sectionBtns[btn] = whichDesc;
    ui->verticalLayout->addWidget(btn);
    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(on_sectionBtn_clicked()));
    btn->setFlat(true);
}

void AboutWindow::on_sectionBtn_clicked(){
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());

    for(QPushButton* p : sectionBtns.keys()){
        p->setStyleSheet(styleNormal);
    }

    buttonSender->setStyleSheet(styleBold);
    ui->lblAbout->setText(sectionText[sectionBtns[buttonSender]]);
}

AboutWindow::~AboutWindow(){
    for(QPushButton* p : sectionBtns.keys())
        delete p;

    delete ui;
}

const QString AboutWindow::styleBold = "QPushButton {\
                           font-size: 8pt;\
                           font-weight: bold;\
                           }";
const QString AboutWindow::styleNormal = "QPushButton {\
                             font-size: 8pt;\
                             }";

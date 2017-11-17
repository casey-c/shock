#include "soundcard.h"
#include "ui_soundcard.h"

SoundCard::SoundCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundCard)
{
    ui->setupUi(this);

    setStyleSheet(":hover {background-color: #eeeeee;}");

    //set the background of the line edit to match the background
    // (so it looks like a label but it's editable)
    //QPalette palette = ui->lineEdit->palette();
    //QColor color = palette.color( QPalette::Disabled, QPalette::Base );
    //palette.setColor( QPalette::Normal, QPalette::Base, color );
    //ui->lineEdit->setPalette( palette );
    //ui->lineEdit->clearFocus();
}

SoundCard::~SoundCard()
{
    delete ui;
}

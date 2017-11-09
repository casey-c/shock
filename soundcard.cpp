#include "soundcard.h"
#include "ui_soundcard.h"

SoundCard::SoundCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundCard)
{
    ui->setupUi(this);

    setStyleSheet(":hover {background-color: #eeeeee;}");
}

SoundCard::~SoundCard()
{
    delete ui;
}

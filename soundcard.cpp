#include "soundcard.h"
#include "ui_soundcard.h"

SoundCard::SoundCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundCard)
{
    ui->setupUi(this);
}

SoundCard::~SoundCard()
{
    delete ui;
}

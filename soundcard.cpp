#include "soundcard.h"
#include "ui_soundcard.h"
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>

SoundCard::SoundCard(SoundContainer2* ctr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundCard),
    firstClick(true)
{
    ui->setupUi(this);
    myContainer = ctr;
    setStyleSheet(":hover {background-color: #eeeeee;}");

    //set the background of the line edit to match the background
    // (so it looks like a label but it's editable)
    //QPalette palette = ui->lineEdit->palette();
    //QColor color = palette.color( QPalette::Disabled, QPalette::Base );
    //palette.setColor( QPalette::Normal, QPalette::Base, color );
    //ui->lineEdit->setPalette( palette );
    //ui->lineEdit->clearFocus();

    contextMenu = new QMenu();

    QAction* a = new QAction("Remove");
    QObject::connect(a, SIGNAL(triggered()),
                     this, SLOT(removeSelf()));
    contextMenu->addAction(a);
}

void SoundCard::removeSelf(){
    emit removeMe(this);
}

void SoundCard::openContextMenu(){
    contextMenu->exec(this->mapFromGlobal(QCursor::pos()));
}

void SoundCard::mousePressEvent(QMouseEvent* evt) {
    if (evt->button() & Qt::RightButton)
    {
        openContextMenu();
    }
    else if (evt->button() & Qt::LeftButton)
    {
        if (firstClick)
        {
            qDebug() << "single click";
            firstClick = false;
            QTimer::singleShot(1000, this, SLOT(doubleClickExpired()));
        }
        else
        {
            qDebug() << "double click";
            // add to workspace
        }

    }
    QWidget::mousePressEvent(evt);
}

SoundCard::~SoundCard()
{
    delete ui;
}


void SoundCard::doubleClickExpired() {
    //qDebug() << "double click expired";
    if (!firstClick)
        firstClick = true;
}

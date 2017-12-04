#include "soundcontainer.h"
#include "ui_soundcontainer.h"
#include <QListWidget>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QFileDialog>
#include <QLabel>
#include "command/commandinterpreter.h"
#include "command/caddsound.h"

// via https://stackoverflow.com/questions/36018010/how-to-change-remove-selection-active-color-of-qlistwidget
class Delegate : public QStyledItemDelegate {
private:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if((option.state & QStyle::State_Selected) || (option.state & QStyle::State_MouseOver))
    {
        // get the color to paint with
        QVariant var = index.model()->data(index, Qt::BackgroundRole);

        // draw the row and its content
        painter->fillRect(option.rect, var.value<QColor>());
        painter->drawText(option.rect, index.model()->data(index, Qt::DisplayRole).toString());
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}

SoundContainer::SoundContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundContainer)
{
    ui->setupUi(this);
    ui->listWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidget->setDefaultDropAction(Qt::MoveAction);
    ui->listWidget->setItemDelegate(new Delegate());
    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Base, QColor(245,245,245));
    ui->listWidget->setPalette(palette);


    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    item->setBackgroundColor(QColor(245,245,245));

    QLabel* lbl = new QLabel("Hey there. To add new files, press Ctrl + i or go to File->Import");
    lbl->setWordWrap(true);
    lbl->setMinimumHeight(150);
    lbl->setMargin(35);
    item->setSizeHint(lbl->minimumSizeHint());
    ui->listWidget->setItemWidget(item, lbl);
}

void SoundContainer::addItemToHash(SoundCard* sc, QListWidgetItem* item) {
    cardToItemWidget[sc] = item;
    QObject::connect(sc, SIGNAL(removeMe(SoundCard*)),
                     this, SLOT(removeSoundCard(SoundCard*)));

    QObject::connect(sc, SIGNAL(addMeToWorkspace(SoundCard*)),
                     this, SLOT(addToWS(SoundCard*)));
}

#if 0
SoundCard* SoundContainer::addSoundCard(QString fn){
    /*
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    item->setBackgroundColor(QColor(245,245,245));
    SoundCard* sc = new SoundCard(this, fn);

    cardToItemWidget[sc] = item;

    QObject::connect(sc, SIGNAL(removeMe(SoundCard*)),
                     this, SLOT(removeSoundCard(SoundCard*)));

    QObject::connect(sc, SIGNAL(addMeToWorkspace(SoundCard*)),
                     this, SLOT(addToWS(SoundCard*)));

    item->setSizeHint(sc->minimumSizeHint());
    ui->listWidget->setItemWidget(item, sc);

    return sc;
    */
}
#endif

void SoundContainer::addSoundCard(QString fn){
    CommandInterpreter::getInstance().run(new CAddSound(fn, ui->listWidget, this));
    //addSoundCard(fp)->setText(name); // TODO
}

void SoundContainer::removeSoundCard(SoundCard* sc){
    ui->listWidget->takeItem(
                ui->listWidget->row(cardToItemWidget[sc]));
}

QVector< QVector <float> > SoundContainer::getAllData(){
    SoundCard* snd;
    QVector<QVector<float> > allData;
    foreach(snd, cardToItemWidget.keys()){
        allData.append(snd->getData());
    }
    return allData;
}

void SoundContainer::on_sndFileDropped(QString fileName){
    addSoundCard(fileName); //todo
}

void SoundContainer::removeAllSounds(){
    for(SoundCard* sc : cardToItemWidget.keys()){
        removeSoundCard(sc);
    }
}

void SoundContainer::importSound()
{
    QStringList snds = QFileDialog::getOpenFileNames(this,
                                 "Import Sample",
                                 "",
                                 "Audio files (*.wav)");

    for(QList<QString>::const_iterator itr = snds.begin(); itr != snds.end(); ++itr){
        addSoundCard(*itr);
    }
}

void SoundContainer::addToWS(SoundCard* sc){
    emit sig_loadToWorkspace(sc);
}

SoundContainer::~SoundContainer()
{
    delete ui;
}





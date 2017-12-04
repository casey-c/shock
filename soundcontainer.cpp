#include "soundcontainer.h"
#include "ui_soundcontainer.h"
#include <QPainter>
#include <QStyledItemDelegate>
#include <QFileDialog>
#include <QKeyEvent>

// via https://stackoverflow.com/questions/36018010/how-to-change-remove-selection-active-color-of-qlistwidget
/*class Delegate : public QStyledItemDelegate {
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
*/
SoundContainer::SoundContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundContainer)
{
    ui->setupUi(this);
    ui->listWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidget->setDefaultDropAction(Qt::MoveAction);
    //ui->listWidget->setItemDelegate(new Delegate());
    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Base, QColor(245,245,245));
    ui->listWidget->setPalette(palette);

    ui->listWidget->setSelectionMode( QAbstractItemView::SingleSelection );

    helpItem = new QListWidgetItem(ui->listWidget);
    helpItem->setBackgroundColor(QColor(245,245,245));
    helpItem->setFlags(Qt::ItemIsEnabled);

    QLabel* lbl = new QLabel("Hey there. To add new files, press ctrl+i or go to File>Import");
    lbl->setWordWrap(true);
    lbl->setMinimumHeight(215);
    lbl->setMargin(35);
    helpItem->setSizeHint(lbl->minimumSizeHint());
    ui->listWidget->setItemWidget(helpItem, lbl);

    qApp->installEventFilter(this);
}

SoundCard* SoundContainer::addSoundCard(QString fn){
    ui->listWidget->setItemHidden(helpItem, true);
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    item->setBackgroundColor(QColor(245,245,245));
    SoundCard* sc = new SoundCard(this, fn);

    cardToItemWidget[sc] = item;
    itemWidgetToCard[item] = sc;

    QObject::connect(sc, SIGNAL(removeMe(SoundCard*)),
                     this, SLOT(removeSoundCard(SoundCard*)));

    QObject::connect(sc, SIGNAL(addMeToWorkspace(SoundCard*)),
                     this, SLOT(addToWS(SoundCard*)));

    item->setSizeHint(sc->minimumSizeHint());
    ui->listWidget->setItemWidget(item, sc);

    return sc;
}

void SoundContainer::addNamedSoundCard(QString fp, QString name){
    addSoundCard(fp)->setText(name);
}

bool SoundContainer::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Delete){
            QList<QListWidgetItem*> selected = ui->listWidget->selectedItems();
            if(!selected.empty()){
                auto li = itemWidgetToCard.find(selected.first());
                if(li != itemWidgetToCard.end()){
                    removeSoundCard(*li);
                    ui->listWidget->clearSelection();
                }
            }
        }
    }

    return QObject::eventFilter(obj, event);
}

void SoundContainer::removeSoundCard(SoundCard* sc){
    ui->listWidget->takeItem(
                ui->listWidget->row(cardToItemWidget[sc]));

    cardToItemWidget.remove(sc);

    if(ui->listWidget->count() == 1){
        ui->listWidget->setItemHidden(helpItem, false);
    }
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
    addSoundCard(fileName);
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





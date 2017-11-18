#include "soundcontainer2.h"
#include "ui_soundcontainer2.h"
#include <QListWidget>
#include <QPainter>
#include <QStyledItemDelegate>

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

SoundContainer2::SoundContainer2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundContainer2)
{
    ui->setupUi(this);
    ui->listWidget->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listWidget->setDefaultDropAction(Qt::MoveAction);
    ui->listWidget->setItemDelegate(new Delegate());
    QPalette palette = ui->listWidget->palette();
    palette.setColor(QPalette::Base, QColor(245,245,245));
    ui->listWidget->setPalette(palette);
    //ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    for (int i = 0; i < 1; ++i)
    {
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        item->setBackgroundColor(QColor(245,245,245));
        SoundCard* sc = new SoundCard(this);

        cardToItemWidget[sc] = item;

        QObject::connect(sc, SIGNAL(removeMe(SoundCard*)),
                         this, SLOT(removeSoundCard(SoundCard*)));

        item->setSizeHint(sc->minimumSizeHint());
        ui->listWidget->setItemWidget(item, sc);
    }
}

void SoundContainer2::removeSoundCard(SoundCard* sc){
    ui->listWidget->takeItem(
                ui->listWidget->row(cardToItemWidget[sc]));
}

SoundContainer2::~SoundContainer2()
{
    delete ui;
}

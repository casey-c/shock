#ifndef SOUNDCONTAINER2_H
#define SOUNDCONTAINER2_H

#include <QWidget>
#include <QListWidget>
#include "soundcard.h"

namespace Ui {
    class SoundContainer2;
}

class SoundContainer2 : public QWidget
{
    Q_OBJECT

public:
    explicit SoundContainer2(QWidget *parent = 0);
    ~SoundContainer2();

private:
    Ui::SoundContainer2 *ui;
    QListWidget* list;
    QHash<SoundCard*, QListWidgetItem*> cardToItemWidget;

private slots:
    void removeSoundCard(SoundCard* sc);
};

#endif // SOUNDCONTAINER2_H

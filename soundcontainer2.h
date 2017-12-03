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
    QVector< QVector <float> > getAllData();
    QList<SoundCard*> getAllSounds(){return cardToItemWidget.keys();}
    ~SoundContainer2();

signals:
    void sig_loadToWorkspace(SoundCard* snd);
    void sig_soundDeleted(SoundCard* snd);

private:
    Ui::SoundContainer2 *ui;
    QListWidget* list;
    QHash<SoundCard*, QListWidgetItem*> cardToItemWidget;

private slots:
    void removeSoundCard(SoundCard* sc);
    void addSoundCard(QString fn);
    void on_sndFileDropped(QString fileName);
    void removeAllSounds();
};

#endif // SOUNDCONTAINER2_H

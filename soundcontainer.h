#ifndef SOUNDCONTAINER_H
#define SOUNDCONTAINER_H

#include <QWidget>
#include <QListWidget>
#include "soundcard.h"

namespace Ui {
    class SoundContainer;
}

class SoundContainer : public QWidget
{
    Q_OBJECT

public:
    explicit SoundContainer(QWidget *parent = 0);
    QVector< QVector <float> > getAllData();
    QList<SoundCard*> getAllSounds(){return cardToItemWidget.keys();}
    void importSound();
    ~SoundContainer();

signals:
    void sig_loadToWorkspace(SoundCard* snd);
    void sig_soundDeleted(SoundCard* snd);

private:
    Ui::SoundContainer *ui;
    QListWidget* list;
    QHash<SoundCard*, QListWidgetItem*> cardToItemWidget;

private slots:
    void removeSoundCard(SoundCard* sc);
    void addSoundCard(QString fn);
    void on_sndFileDropped(QString fileName);
    void removeAllSounds();
};

#endif // SOUNDCONTAINER_H

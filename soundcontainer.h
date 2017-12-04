#ifndef SOUNDCONTAINER_H
#define SOUNDCONTAINER_H

#include <QWidget>
#include <QListWidget>
#include "soundcard.h"
#include <QLabel>
#include <QListWidget>

#include "command/caddsound.h"

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
    void addItemToHash(SoundCard* sc, QListWidgetItem* item);
    ~SoundContainer();

public slots:
    void removeSoundCard(SoundCard* sc);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void sig_loadToWorkspace(SoundCard* snd);
    void sig_soundDeleted(SoundCard* snd);

private:
    Ui::SoundContainer *ui;
    QListWidget* list;
    QHash<SoundCard*, QListWidgetItem*> cardToItemWidget;
    QHash<QListWidgetItem*, SoundCard*> itemWidgetToCard;
    QListWidgetItem* helpItem;

private slots:
    void addSoundCard(QString fn);
    //SoundCard* addSoundCard(QString fn); //todo
    void addNamedSoundCard(QString fp, QString name);
    void on_sndFileDropped(QString fileName);
    void removeAllSounds();
    void addToWS(SoundCard* sc);
    void onSoundGenerated(QString fileName);
};

#endif // SoundContainer_H

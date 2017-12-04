#ifndef CADDSOUND_H
#define CADDSOUND_H

#include "icommand.h"
#include <QList>
#include "../soundcontainer.h"
#include "../soundcard.h"

class SoundContainer;

class CAddSound : public ICommand
{
public:
    //CAddSound(const QList<QString>& s, SoundContainer* sc);
    CAddSound(QString s, QListWidget* list, SoundContainer* sc, QListWidgetItem* helpItem);
    ~CAddSound() override {}

    bool act() override;
    bool undo() override;

private:
    QString soundPath;
    SoundCard* addedSound;
    QListWidget* list;
    SoundContainer* container;
    QListWidgetItem* helpItem;
};

#endif // CADDSOUND_H

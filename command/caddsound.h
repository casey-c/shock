#ifndef CADDSOUND_H
#define CADDSOUND_H

#include "icommand.h"
#include <QList>
#include "../soundcontainer.h"

class SoundContainer;

class CAddSound : public ICommand
{
public:
    CAddSound(const QList<QString>& s, SoundContainer* sc);
    ~CAddSound() override {}

    bool act() override;
    bool undo() override;

private:
    QList<QString> soundList;
    QList<Sound*> addedSounds;
    SoundContainer* container;
};

#endif // CADDSOUND_H

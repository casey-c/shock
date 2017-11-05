#include "caddsound.h"
#include "sound.h"

CAddSound::CAddSound(const QList<QString>& soundList, SoundContainer* sc) {
    if (soundList.size() > 1)
        this->plainText = "Add sounds";
    else
        this->plainText = "Add sound";

    this->soundList = soundList;
    this->container = sc;
}

bool CAddSound::act() {
    if (soundList.empty())
        return false;

    for (QString s : soundList)
        addedSounds.push_back(new Sound(container, s));
    for (Sound* s : addedSounds)
        container->addSound(s);

    return true;
}

bool CAddSound::undo() {
    for (Sound* s : addedSounds) {
        container->removeSound(s);
        delete s;
    }

    addedSounds.clear();
    return true;
}

#include "caddsound.h"
#include "soundcard.h"

CAddSound::CAddSound(QString s, QListWidget* list, SoundContainer* sc ) {
    //if (soundList.size() > 1)
        //this->plainText = "Add sounds";
    //else
        this->plainText = "Add sound";

    this->soundPath = s;
    this->list = list;
    this->container = sc;
}

bool CAddSound::act() {
    QListWidgetItem* item = new QListWidgetItem(list);
    item->setBackgroundColor(QColor(245,245,245));
    addedSound = new SoundCard(container, soundPath);

    container->addItemToHash(addedSound, item);

    item->setSizeHint(addedSound->minimumSizeHint());
    list->setItemWidget(item, addedSound);

    return true;
}

bool CAddSound::undo() {
    container->removeSoundCard(addedSound);
    return true;
}

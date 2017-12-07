#include "caddsound.h"
#include "soundcard.h"

CAddSound::CAddSound(QString s, QListWidget* list, SoundContainer* sc, QListWidgetItem* helpItem) {
    //if (soundList.size() > 1)
        //this->plainText = "Add sounds";
    //else
        this->plainText = "Add sound";

    this->soundPath = s;
    this->list = list;
    this->container = sc;
    this->helpItem = helpItem;
}

bool CAddSound::act() {
    QListWidgetItem* item = new QListWidgetItem(list);
    item->setBackgroundColor(QColor(245,245,245));
    addedSound = new SoundCard(container, soundPath);

    container->addItemToHash(addedSound, item);

    item->setSizeHint(addedSound->minimumSizeHint());
    list->setItemWidget(item, addedSound);
    list->setItemHidden(helpItem, true);

    return true;
}

bool CAddSound::undo() {
    container->removeSoundCard(addedSound);
    return true;
}

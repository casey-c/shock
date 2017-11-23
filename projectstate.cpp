#include "projectstate.h"
#include <QJsonArray>
#include <QSettings>

ProjectState::ProjectState(QObject *parent) : QObject(parent)
{

}

void ProjectState::loadProject() {
    qDebug() << "removing current sound files";

    emit sig_removeLoadedSounds();


    qDebug() << "loading project";

    QSettings settings("Shock3", "Shock3");

    int size = settings.beginReadArray("sounds");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString filePath = settings.value("fileLocation").toString();
        emit sig_reloadSound(filePath);
    }
    settings.endArray();
}

void ProjectState::saveProject(QList<Sound*> loadedSounds) {
    //list of all sounds loaded is passed in

    qDebug() << "ceating qsettings";

    QSettings settings("Shock3", "Shock3");

    settings.beginWriteArray("sounds");
    for (int i=0; i < loadedSounds.size(); ++i) {
        // should get whatever the user named the file too (and cuts, depending on how we do that)
        // currently only keeps track of file location (which is all that is needed to reload the sounds)
        QString t_str = loadedSounds[i]->getFileName();
        qDebug() << t_str;
        settings.setArrayIndex(i);
        settings.setValue("fileLocation", t_str); // use similair calls to this for each trait of a 'sound'
    }
    settings.endArray();
}

#include "projectstate.h"
#include <QJsonArray>
#include <QSettings>
#include <QFileDialog>

ProjectState::ProjectState(QObject *parent) : QObject(parent)
{

}

// load previously saved project from disk
void ProjectState::loadProject() {

    QString saveFile = QFileDialog::getOpenFileName((QWidget*)this->parent(),"Open Project","","Shock Files (*.shock)");

    if (saveFile == "")
        return;

    emit sig_removeLoadedSounds();


    QSettings settings(saveFile, QSettings::IniFormat);

    int size = settings.beginReadArray("sounds");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QString filePath = settings.value("fileLocation").toString();
        QString fileText = settings.value("fileText").toString();

        emit sig_reloadSound(filePath,fileText);
    }
    settings.endArray();
}


bool isValidFileName(QString fileName) {
    bool valid = true;

    if (fileName.contains('.')) {
        if (fileName.length() < 6)
            valid = false;

        QString validEnd = "kcohs."; // ".shock" backwards

        if (valid) { // only perorm the loop ckeck if it can still be valid
            for (int i=0; i < 6; ++i) {
                if (fileName[fileName.length()-(i+1)] != validEnd[i]) {
                    valid = false;
                }
            }
        }
    }

    return valid;
}

void ProjectState::saveProject(QList<Sound*> loadedSounds) {
    //list of all sounds loaded is passed in

    QString fileName;

    while (true) { // loop until you get a valid file name
        fileName = QFileDialog::getSaveFileName((QWidget*)this->parent(),tr("Save Project Settings"),"",tr("Shock config file (*.shock)"));

        if (!fileName.contains('.')) {
            fileName.append(".shock");
        }

        if (isValidFileName(fileName))
            break;
        else
            qDebug() << "You must enter a valid file extension (or no extension)";
    }

    QSettings settings(fileName, QSettings::IniFormat);

    settings.beginWriteArray("sounds");
    for (int i=0; i < loadedSounds.size(); ++i) {
        // should get whatever the user named the file too (and cuts, depending on how we do that)
        // currently only keeps track of file location (which is all that is needed to reload the sounds)
        QString t_str = loadedSounds[i]->getFileName();
        settings.setArrayIndex(i);
        settings.setValue("fileLocation", t_str); // use similair calls to this for each trait of a 'sound'
        settings.setValue("fileText", loadedSounds[i]->getText());
    }
    settings.endArray();
}

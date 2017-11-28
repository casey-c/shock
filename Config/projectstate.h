#ifndef PROJECTSTATE_H
#define PROJECTSTATE_H

#include <QObject>
#include "sound.h"

class ProjectState : public QObject
{
    Q_OBJECT
public:
    explicit ProjectState(QObject *parent = nullptr);

signals:
    void sig_reloadSound(QString filePath, QString fileName);
    //void sig_reloadSound(QString filePath, QString fileName);
    void sig_removeLoadedSounds();

public slots:

private slots:
    void loadProject();
    void saveProject(QList<Sound*> loadedSounds);
};

#endif // PROJECTSTATE_H

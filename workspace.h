#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>
#include "sound.h"

namespace Ui {
    class Workspace;
}

class Workspace : public QWidget
{
    Q_OBJECT

public:
    explicit Workspace(QWidget *parent = 0);
    ~Workspace();
    void loadSound(Sound* sound);
    void unloadSound();

private slots:
    void slot_loadSound(Sound* snd);

private:
    Ui::Workspace *ui;
    bool soundLoaded;
    Sound* snd;
};

#endif // WORKSPACE_H

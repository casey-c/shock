#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>
#include "sound.h"
#include "waveformwidget.h"

namespace Ui {
    class Workspace;
}

class Workspace : public QWidget
{
    Q_OBJECT

public:
    explicit Workspace(QWidget *parent = 0);
    ~Workspace();
    //void loadSound(Sound* sound);
    void unloadSound();

private slots:
    void loadSound(Sound* snd);
    void checkSound(Sound* snd);

private:
    Ui::Workspace *ui;
    bool soundLoaded;
    Sound* snd;
    WaveformWidget* child;
};

#endif // WORKSPACE_H

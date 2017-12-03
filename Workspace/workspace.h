#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>
#include "soundcard.h"
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
    void loadSound(SoundCard* snd);
    void validateSound(SoundCard* snd);

private:
    Ui::Workspace *ui;
    bool soundLoaded;
    SoundCard* snd;
    WaveformWidget* dispWaveform;
};

#endif // WORKSPACE_H

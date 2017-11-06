#ifndef SOUNDCONTAINER_H
#define SOUNDCONTAINER_H

#include <QWidget>
#include <QList>
#include <sound.h>
#include <QFileDialog>
#include <QSpacerItem>
#include <QFrame>

namespace Ui {
class SoundContainer;
}

class SoundContainer : public QWidget
{
    Q_OBJECT

public:
    explicit SoundContainer(QWidget *parent = 0);
    int size();

    ~SoundContainer();

signals:
    void sig_loadToWorkspace(Sound* snd);

private slots:
    void on_btnAdd_clicked();
    void on_btnRemove_clicked();
    void shiftSndUp();
    void shiftSndDown();

    void on_btnSelectAll_clicked();

    void on_btnDeselectAll_clicked();

    void on_tabVolSlider_sliderMoved(int position);
    void loadSoundToWorkspace(Sound* snd);
    void on_sndFileDropped(QString path);

private:
    Ui::SoundContainer *ui;
    QList<Sound*> sounds;

    void shiftSoundPos(Sound* const &snd, int offset);
    void addSound(Sound* snd);
    void removeSound(Sound* snd);
};

#endif // SOUNDCONTAINER_H

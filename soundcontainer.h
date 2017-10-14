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
    ~SoundContainer();

private slots:
    void on_btnAdd_clicked();

    void on_btnRemove_clicked();

private:
    Ui::SoundContainer *ui;

    QList<Sound*> sounds;

    void addSound(Sound* snd);
};

#endif // SOUNDCONTAINER_H

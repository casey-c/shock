#ifndef SOUNDCARD_H
#define SOUNDCARD_H

#include <QWidget>
#include <QMenu>
#include <QMediaPlayer>
#include "Workspace/audioutil.h"

namespace Ui {
    class SoundCard;
}

class SoundCard : public QWidget
{
    Q_OBJECT

public:
    explicit SoundCard(QWidget* parent,
                       QString sndFile);
    QVector<float> getData();
    QString getFileName(){return fileName;}
    QString getText();
    void setText(QString txt);
    ~SoundCard();
    static bool validSoundFile(QString path);

signals:
    void removeMe(SoundCard*);
    void addMeToWorkspace(SoundCard*);

private:
    Ui::SoundCard *ui;
    QMenu* contextMenu;
    QMediaPlayer* mediaPlayer;
    void openContextMenu();
    bool firstClick;
    void mousePressEvent(QMouseEvent *event) override;
    QString fileName;
    void setupMediaPlayer();

    int actualVolume;
private slots:
    void doubleClickExpired();
    void finishNameEdit();

    void removeSelf();
    void addSelfToWorkspace();
    void saveCopyOfSelf();
    void updateSeekBar(qint64 pos);
    void seekTo(int pos);
    void togglePlayback();
    void toggleSeeking();
    void stopPlayback();
    void mpStateChange(QMediaPlayer::State);

    void adjustVolume();
    void on_verticalSlider_valueChanged();
};

#endif // SOUNDCARD_H

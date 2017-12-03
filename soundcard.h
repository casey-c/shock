#ifndef SOUNDCARD_H
#define SOUNDCARD_H

#include <QWidget>
#include <QMenu>
#include <QMediaPlayer>

namespace Ui {
    class SoundCard;
}

class SoundCard : public QWidget
{
    Q_OBJECT

public:
    explicit SoundCard(QWidget* parent = 0,
                       QString sndFile = "C:/Users/bcmwo/Downloads/165194__ryding__road.wav");
    ~SoundCard();

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
    QString soundFile;
    void setupMediaPlayer();
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
};

#endif // SOUNDCARD_H

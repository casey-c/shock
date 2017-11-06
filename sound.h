#ifndef SOUND_H
#define SOUND_H

#include <QWidget>
#include <QString>
#include <QMediaPlayer>
#include <QLayoutItem>
#include <QFileInfo>

namespace Ui {
class Sound;
}

class Sound : public QWidget
{
    Q_OBJECT

public:
    explicit Sound(QWidget *parent = 0, QString fn = "");
    ~Sound();

    QString getFileName();
    void pause();
    void play();
    void stop();

    bool selected();
    void setSelected(bool selected);
    void setVolumeMod(int x);
    static bool validSoundFile(QString path);

signals:
    void sig_shiftUp();
    void sig_shiftDown();
    void sig_loadToWorkspace();
    void sig_loadSoundToWorkspace(Sound* snd);


private slots:
    void on_btnPlay_clicked();
    void on_btnPause_clicked();
    void on_btnStop_clicked();
    void on_btnShiftUp_clicked();
    void on_btnShiftDown_clicked();
    void on_leName_returnPressed();
    void adjustVolume();
    void on_sliderVol_sliderMoved();
    void on_loadToWorkspace_clicked();

private:
    Ui::Sound *ui;
    QString fileName;
    QMediaPlayer player;
    int volumeMod;
    int actualVolume;

    void setPath(QString fn);
};

#endif // SOUND_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <soundcontainer.h>
#include "sound.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QVector<Sound*> soundVector;
    Ui::MainWindow* ui;
    QMediaPlaylist* mediaPlaylist;
    QMediaPlayer* mediaPlayer;
    SoundContainer* sndCont;

    void loadIntoClearedPlaylist();
    void loadNewSound();

private slots:
    void on_open_file_button_clicked();
    void on_play_sound_button_clicked();
    void on_pause_sound_button_clicked();
};

#endif // MAINWINDOW_H

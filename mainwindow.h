#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <soundcontainer.h>
#include "sound.h"
#include <aboutwindow.h>
#include <controlpanel.h>

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
    AboutWindow* abtWindow;
    ControlPanel* ctrlPanel;
private slots:
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H

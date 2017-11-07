#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "soundcontainer.h"
#include "sound.h"
#include "aboutwindow.h"
#include "controlpanel.h"
#include "workspace.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sig_sndFileDropped(QString path);
    void sig_loadSndToWorkspace(Sound* snd);

private:
    Ui::MainWindow* ui;
    SoundContainer* sndCont;

    AboutWindow* abtWindow;
    ControlPanel* ctrlPanel;
    Workspace* workspace;
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent* event);
private slots:
    void on_actionAbout_triggered();    
    void loadSoundToWorkspace(Sound* snd);
};

#endif // MAINWINDOW_H

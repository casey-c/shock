#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "soundcontainer2.h"
#include "soundcard.h"
#include "Windows/aboutwindow.h"
#include "ControlPanel/controlpanel.h"
#include "Workspace/workspace.h"
#include "Config/projectstate.h"

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
    void sig_SaveProject(QList<SoundCard*>);
    void sig_LoadProject();

private:
    Ui::MainWindow* ui;
    SoundContainer2* sndCont;

    AboutWindow* abtWindow;
    ControlPanel* ctrlPanel;
    Workspace* workspace;
    ProjectState* projState;
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent* event);
private slots:
    void on_actionAbout_triggered();
    void on_actionSave_Project_triggered();
    void on_actionOpen_Project_triggered();
    void loadSoundToWorkspace(SoundCard* snd);
    void on_actionNew_triggered();
    void on_actionImport_Sample_triggered();
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H

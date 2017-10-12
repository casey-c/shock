#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
<<<<<<< Updated upstream
    Ui::MainWindow *ui;
=======
    Ui::MainWindow* ui;
    QMediaPlaylist* mediaPlaylist;
    QMediaPlayer* mediaPlayer;

    void loadIntoClearedPlaylist();

private slots:
    void on_open_file_button_clicked();
    void on_play_sound_button_clicked();
    void on_pause_sound_button_clicked();
    void on_actionAbout_triggered();
>>>>>>> Stashed changes
};

#endif // MAINWINDOW_H

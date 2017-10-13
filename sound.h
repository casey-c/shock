#ifndef SOUND_H
#define SOUND_H

#include <QWidget>
#include <QString>
#include <QMediaPlayer>
#include <QLayoutItem>

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

private:
    Ui::Sound *ui;
    QString fileName;
    QMediaPlayer player;

    void setPath(QString fn);

};

#endif // SOUND_H

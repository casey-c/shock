#ifndef SOUND_H
#define SOUND_H

#include <QWidget>
#include <QString>

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

private:
    Ui::Sound *ui;
    QString fileName;

    void setPath(QString fn);

};

#endif // SOUND_H

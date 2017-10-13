#ifndef SOUND_H
#define SOUND_H

#include <QWidget>

namespace Ui {
class Sound;
}

class Sound : public QWidget
{
    Q_OBJECT

public:
    explicit Sound(QWidget *parent = 0);
    ~Sound();



private:
    Ui::Sound *ui;
};

#endif // SOUND_H

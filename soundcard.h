#ifndef SOUNDCARD_H
#define SOUNDCARD_H

#include <QWidget>

namespace Ui {
    class SoundCard;
}

class SoundCard : public QWidget
{
    Q_OBJECT

public:
    explicit SoundCard(QWidget *parent = 0);
    ~SoundCard();

private:
    Ui::SoundCard *ui;
};

#endif // SOUNDCARD_H

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
    explicit SoundCard(QWidget* parent = 0);
    ~SoundCard();

private:
    Ui::SoundCard *ui;
    bool firstClick;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void doubleClickExpired();
};

#endif // SOUNDCARD_H

#ifndef SOUNDCARD_H
#define SOUNDCARD_H

#include <QWidget>
#include <QMenu>
#include "soundcontainer2.h"

namespace Ui {
    class SoundCard;
}

class SoundCard : public QWidget
{
    Q_OBJECT

public:
    explicit SoundCard(SoundContainer2* ctr,QWidget* parent = 0);
    ~SoundCard();

signals:
    void removeMe(SoundCard*);

private:
    Ui::SoundCard *ui;
    SoundContainer2* myContainer;
    QMenu* contextMenu;
    void openContextMenu();
    bool firstClick;
    void mousePressEvent(QMouseEvent *event) override;
private slots:
    void doubleClickExpired();
    void removeSelf();
};

#endif // SOUNDCARD_H

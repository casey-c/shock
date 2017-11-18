#ifndef SOUNDCARD_H
#define SOUNDCARD_H

#include <QWidget>
#include <QMenu>

namespace Ui {
    class SoundCard;
}

class SoundCard : public QWidget
{
    Q_OBJECT

public:
    explicit SoundCard(QWidget* parent = 0);
    ~SoundCard();

signals:
    void removeMe(SoundCard*);
    void addMeToWorkspace(SoundCard*);

private:
    Ui::SoundCard *ui;
    QMenu* contextMenu;
    void openContextMenu();
    bool firstClick;
    void mousePressEvent(QMouseEvent *event) override;
private slots:
    void doubleClickExpired();
    void finishNameEdit();

    void removeSelf();
    void addSelfToWorkspace();
    void saveCopyOfSelf();
};

#endif // SOUNDCARD_H

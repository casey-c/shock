#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QVector>
#include <QPushButton>
#include <QLayout>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();

private:
    Ui::AboutWindow *ui;
    QHash<QPushButton*, QString> sectionBtns; //maps button to description tag
    QHash<QString, QString> sectionText;      //maps description tag to description

    void addButton(QString btnLabel, QString whichDesc);
    void initSectionText();

    static const QString styleNormal;
    static const QString styleBold;
private slots:
    void on_sectionBtn_clicked();
};

#endif // ABOUTWINDOW_H

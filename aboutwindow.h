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
    QVector<QPushButton*> sectionBtns;
    void AboutWindow::addButton(QString name);

private slots:
    void on_sectionBtn_clicked();
};

#endif // ABOUTWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waveformwidget.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QMimeData>
#include <QDirIterator>

#include "genealg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    abtWindow = nullptr;
    ui->setupUi(this);
    sndCont = new SoundContainer(this);
    ui->tab1->setLayout(ui->grLayout);
    ui->grLayout->addWidget(sndCont);

    QObject::connect(sndCont, SIGNAL(sig_loadToWorkspace(Sound*)), this, SLOT(loadSoundToWorkspace(Sound*)));
    ctrlPanel = new ControlPanel();
    ui->gridFrame->layout()->addWidget(ctrlPanel);

    workspace = new Workspace();
    ui->shockframe->layout()->removeWidget(ui->shockButton);
    ui->shockframe->layout()->addWidget(workspace);
    ui->shockframe->layout()->addWidget(ui->shockButton);


    QObject::connect(this, SIGNAL(sig_loadSndToWorkspace(Sound*)), workspace, SLOT(loadSound(Sound*)));
    //QObject::connect(parent, SIGNAL(addToWorkspace(Sound*)), this, SLOT(loadSound(Sound*)));

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete sndCont;
    delete ui;
    delete ctrlPanel;
    delete workspace;
}

void MainWindow::on_actionAbout_triggered()
{
    if(abtWindow != nullptr){
        delete abtWindow;
    }

    abtWindow = new AboutWindow();
    abtWindow->show();
    abtWindow->raise();
}

void MainWindow::loadSoundToWorkspace(Sound* snd)
{
    emit sig_loadSndToWorkspace(snd);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e){
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* event){
    const QMimeData* mimeData = event->mimeData();

    QList<QUrl> urlList = mimeData->urls();
    // extract the local paths of the files
    for (int i = 0; i < urlList.size(); ++i)
    {
        QString path = urlList.at(i).toLocalFile();
        if(Sound::validSoundFile(path)){
            emit sig_sndFileDropped(path);
            continue;
        }

        QDirIterator it(path, QDir::NoFilter, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            QFile f(it.next());
            QString fn = f.fileName();
            qDebug() << fn;

            if(Sound::validSoundFile(fn))
                emit sig_sndFileDropped(fn);

        }
    }
}


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
    abtWindow = nullptr; //initialize variables & ui
    ui->setupUi(this);
    sndCont = new SoundContainer(this); //create soundcontainer
    ui->tab1->setLayout(ui->grLayout);
    ui->grLayout->addWidget(sndCont);

    ctrlPanel = new ControlPanel(); //create control panel
    //QObject::connect(sndCont, SIGNAL(sig_loadToWorkspace(Sound*)), this, SLOT(loadSoundToWorkspace(Sound*)));
    ui->gridFrame->layout()->addWidget(ctrlPanel);
    setAcceptDrops(true);

    workspace = new Workspace();
    ui->shockframe->layout()->removeWidget(ui->shockButton);
    ui->shockframe->layout()->addWidget(workspace);
    ui->shockframe->layout()->addWidget(ui->shockButton);

    QObject::connect(sndCont, SIGNAL(sig_loadToWorkspace(Sound*)), workspace, SLOT(loadSound(Sound*)));
    QObject::connect(sndCont, SIGNAL(sig_soundDeleted(Sound*)), workspace, SLOT(validateSound(Sound*)));
    //QObject::connect(this, SIGNAL(sig_loadSndToWorkspace(Sound*)), workspace, SLOT(loadSound(Sound*)));
    //QObject::connect(parent, SIGNAL(addToWorkspace(Sound*)), this, SLOT(loadSound(Sound*)));

    setAcceptDrops(true);
}

MainWindow::~MainWindow(){
    delete sndCont;
    delete ui;
    delete ctrlPanel;
    delete workspace;
}

void MainWindow::on_actionAbout_triggered(){
    if(abtWindow != nullptr){ //make sure you get a fresh aboutWindow
        delete abtWindow;
    }

    abtWindow = new AboutWindow();
    abtWindow->show();
    abtWindow->raise();
}

void MainWindow::loadSoundToWorkspace(Sound* snd){
    emit sig_loadSndToWorkspace(snd);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e){
    if (e->mimeData()->hasUrls()) { //if the user is dragging files, it's ok
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* event){
    //get the dropped files
    const QMimeData* mimeData = event->mimeData();
    QList<QUrl> urlList = mimeData->urls();

    for (int i = 0; i < urlList.size(); ++i)
    {
        // extract the local paths of the files
        QString path = urlList.at(i).toLocalFile();

        if(Sound::validSoundFile(path)){
            emit sig_sndFileDropped(path);
            continue;
        }

        //iterate over every subdirectory in selection, looking for sounds
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


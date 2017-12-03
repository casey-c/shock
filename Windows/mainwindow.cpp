#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Workspace/waveformwidget.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QMimeData>
#include <QDirIterator>
#include "ControlPanel/genealg.h"
#include "Sound/sound.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    abtWindow = nullptr; //initialize variables & ui
    ui->setupUi(this);
    sndCont = new SoundContainer2(this); //create soundcontainer
    ui->frame_2->setLayout(ui->grLayout);
    ui->frame_3->setLayout(ui->grLayout2);
    ui->grLayout->addWidget(sndCont);

    ctrlPanel = new ControlPanel(); //create control panel
    ui->grLayout2->addWidget(ctrlPanel);
    setAcceptDrops(true);
    ctrlPanel->setCont(sndCont);
    workspace = new Workspace();
    ui->shockframe->layout()->addWidget(workspace);

    QObject::connect(sndCont, SIGNAL(sig_loadToWorkspace(SoundCard*)), workspace, SLOT(loadSound(SoundCard*)));
    QObject::connect(sndCont, SIGNAL(sig_soundDeleted(SoundCard*)), workspace, SLOT(validateSound(SoundCard*)));

    projState = new ProjectState();
    QObject::connect(this, SIGNAL(sig_SaveProject(QList<SoundCard*>)), projState, SLOT(saveProject(QList<SoundCard*>)));
    QObject::connect(this, SIGNAL(sig_LoadProject()), projState, SLOT(loadProject()));
    QObject::connect(projState,SIGNAL(sig_reloadSound(QString,QString)),sndCont,SLOT(on_sndFileDropped(QString)));
    QObject::connect(projState,SIGNAL(sig_removeLoadedSounds()),sndCont,SLOT(removeAllSounds()));

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

void MainWindow::on_actionSave_Project_triggered() {
    emit sig_SaveProject(sndCont->getAllSounds());
}

void MainWindow::on_actionOpen_Project_triggered() {
    emit sig_LoadProject();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e){
    if (e->mimeData()->hasUrls()) { //if the user is dragging files, it's ok
        e->acceptProposedAction();
    }
}

// drag and drop folders onto the application
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


void MainWindow::on_actionNew_triggered()
{
    MainWindow* newWindow = new MainWindow();
    newWindow->show();
}

void MainWindow::on_actionImport_Sample_triggered()
{
   sndCont->importSound();
}

void MainWindow::on_actionExit_triggered()
{
   close();
}

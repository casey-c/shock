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
#include "soundcard.h"
#include "command/commandinterpreter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    abtWindow = nullptr; //initialize variables & ui
    ui->setupUi(this);
    sndCont = new SoundContainer(this); //create soundcontainer
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

    QObject::connect(this, SIGNAL(sig_sndFileDropped(QString)), sndCont, SLOT(addSoundCard(QString)));

    projState = new ProjectState();
    QObject::connect(this, SIGNAL(sig_SaveProject(QList<SoundCard*>)), projState, SLOT(saveProject(QList<SoundCard*>)));
    QObject::connect(this, SIGNAL(sig_LoadProject()), projState, SLOT(loadProject()));
    //QObject::connect(projState,SIGNAL(sig_reloadSound(QString, QString)),sndCont,SLOT(addNamedSoundCard(QString, QString)));
    QObject::connect(projState,SIGNAL(sig_removeLoadedSounds()),sndCont,SLOT(removeAllSounds()));

    // Set up command interpreter
    // i.e. connect our slots to its signals
    //CommandInterpreter i = CommandInterpreter::getInstance();
    QObject::connect(&(CommandInterpreter::getInstance()), SIGNAL(updateRedoText(bool,QString)),
                     this, SLOT(updateRedoText(bool, QString)));
    QObject::connect(&(CommandInterpreter::getInstance()), SIGNAL(updateUndoText(bool,QString)),
                     this, SLOT(updateUndoText(bool, QString)));

    setAcceptDrops(true);
}

MainWindow::~MainWindow(){
    delete sndCont;
    delete ui;
    delete ctrlPanel;
    delete workspace;
}

void MainWindow::updateRedoText(bool valid, QString redoText)
{
    ui->actionRedo->setEnabled(valid);
    ui->actionRedo->setText(redoText);
}

void MainWindow::updateUndoText(bool valid, QString undoText)
{
    ui->actionUndo->setEnabled(valid);
    ui->actionUndo->setText(undoText);
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

        if(SoundCard::validSoundFile(path)){
            emit sig_sndFileDropped(path);
            continue;
        }

        //iterate over every subdirectory in selection, looking for sounds
        QDirIterator it(path, QDir::NoFilter, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            QFile f(it.next());
            QString fn = f.fileName();
            qDebug() << fn;

            if(SoundCard::validSoundFile(fn))
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

void MainWindow::on_actionUndo_triggered()
{
   CommandInterpreter::getInstance().undoLastCommand();
}
void MainWindow::on_actionRedo_triggered()
{
   CommandInterpreter::getInstance().redoLastCommand();
}

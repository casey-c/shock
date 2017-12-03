#-------------------------------------------------
#
# Project created by QtCreator 2017-10-03T09:14:47
#
#-------------------------------------------------

QT       += \
            core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Shock
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = shockicon.ico

SOURCES += \
        main.cpp \
        Windows/mainwindow.cpp \
        Windows/aboutwindow.cpp \
        ControlPanel/genealg.cpp \
        ControlPanel/algosettings.cpp \
        ControlPanel/param.cpp \
        ControlPanel/controlpanel.cpp \
        Workspace/workspace.cpp \
        Workspace/waveformwidget.cpp \
        Workspace/audioutil.cpp \
    ControlPanel/mutableparamelement.cpp \
    ControlPanel/mutableelement_lineedit.cpp \
    ControlPanel/mutableelement_slider.cpp \
    ControlPanel/mutableelement_checkbox.cpp \
    Config/jsontemplateinterpreter.cpp \
    Config/projectstate.cpp \
    soundcard.cpp \
    soundcontainer.cpp

HEADERS += \
        Windows/mainwindow.h \
        Windows/aboutwindow.h \
        ControlPanel/genealg.h \
        ControlPanel/ialgorithm.h \
        ControlPanel/algosettings.h \
        ControlPanel/param.h \
        ControlPanel/controlpanel.h \
        Workspace/workspace.h \
        Workspace/waveformwidget.h \
        Workspace/audioutil.h \
    ControlPanel/mutableparamelement.h \
    ControlPanel/mutableelement_lineedit.h \
    ControlPanel/mutableelement_slider.h \
    ControlPanel/mutableelement_checkbox.h \
    Config/jsoninterpreter.h \
    Config/jsontemplateinterpreter.h \
    Config/projectstate.h \
    soundcard.h \
    soundcontainer.h

FORMS += \
        Windows/mainwindow.ui \
        Windows/aboutwindow.ui \
        ControlPanel/controlpanel.ui \
        Workspace/workspace.ui \
    soundcard.ui \
    soundcontainer.ui

win32: LIBS += -L$$PWD/../../../../../../../libsndfile/lib/ -llibsndfile-1
unix: LIBS += -lsndfile

INCLUDEPATH += $$PWD/../../../../../../../libsndfile/include
DEPENDPATH += $$PWD/../../../../../../../libsndfile/include

RESOURCES += \
    resources.qrc

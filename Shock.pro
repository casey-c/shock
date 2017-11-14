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
        mainwindow.cpp \
        sound.cpp \
        soundcontainer.cpp \
        aboutwindow.cpp \
        genealg.cpp \
        algosettings.cpp \
        param.cpp \
        controlpanel.cpp \
        workspace.cpp \
        waveformwidget.cpp \
        audioutil.cpp \
    mutableparamelement.cpp \
    mutableelement_lineedit.cpp \
    mutableelement_slider.cpp \
    mutableelement_checkbox.cpp \
    jsontemplateinterpreter.cpp

HEADERS += \
        mainwindow.h \
        sound.h \
        soundcontainer.h \
        aboutwindow.h \
        genealg.h \
        ialgorithm.h \
        algosettings.h \
        param.h \
        controlpanel.h \
        workspace.h \
        waveformwidget.h \
        audioutil.h \
    mutableparamelement.h \
    mutableelement_lineedit.h \
    mutableelement_slider.h \
    mutableelement_checkbox.h \
    jsoninterpreter.h \
    jsontemplateinterpreter.h

FORMS += \
        mainwindow.ui \
        sound.ui \
        soundcontainer.ui \
        aboutwindow.ui \
        controlpanel.ui \
        workspace.ui

win32: LIBS += -L$$PWD/../../../../../../../libsndfile/lib/ -llibsndfile-1
unix: LIBS += -lsndfile

INCLUDEPATH += $$PWD/../../../../../../../libsndfile/include
DEPENDPATH += $$PWD/../../../../../../../libsndfile/include

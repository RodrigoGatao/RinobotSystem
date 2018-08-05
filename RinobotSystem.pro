#-------------------------------------------------
#
# Project created by QtCreator 2018-06-14T11:29:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RinobotSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "/usr/local/include/opencv2"
LIBS += `pkg-config --cflags --libs opencv`

SOURCES += main.cpp\
        mainwindow.cpp \
    vision.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    vision.h \
    utils.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    icons/atack2.jpg \
    icons/darth2.jpeg \
    icons/map.jpg \
    icons/taffarelIcon.jpg \
    icons/yoda2.jpg \
    icons/allyIcon.png \
    icons/ballIcon.png \
    icons/cameraIcon.png \
    icons/colorsIcon.png \
    icons/enemyIcon.png \
    icons/filterIcon.png \
    icons/luvasdegoleir.png \
    icons/off.png \
    icons/on.png \
    icons/robots.png \
    icons/romarioIcon.png \
    icons/zagueiro.png

RESOURCES += \
    resources.qrc

DISTFILES += \
    icons/CampoTamanhoTela.png

#-------------------------------------------------
#
# Project created by QtCreator 2019-02-01T14:09:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UV_Reader
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

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    videofilereader.cpp \
    ktime.cpp \
    labelevent.cpp \
    analysisform.cpp \
    qactionbuttom.cpp

HEADERS += \
        mainwindow.h \
    videofilereader.h \
    ktime.h \
    labelevent.h \
    analysisform.h \
    qactionbuttom.h

FORMS += \
        mainwindow.ui \
    videocotrollerframe.ui \
    analysisform.ui

INCLUDEPATH += C:/OpenCV-4.0.1/include

CONFIG (debug, debug|release) {
    #debug
    LIBS += "C:/OpenCV-4.0.1/lib/opencv_world401d.lib"
    message( "debug" )
} else {
    #release
    LIBS += "C:/OpenCV-4.0.1/lib/opencv_world401.lib"
    message( "release" )
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

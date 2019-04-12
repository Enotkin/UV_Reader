#-------------------------------------------------
#
# Project created by QtCreator 2019-02-01T14:09:21
#
#-------------------------------------------------

QT       += core gui axcontainer printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UV_Reader
TEMPLATE = app

#SUBDIRS +=


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
    addfragmentcommentdialog.cpp \
    fragmentinfo.cpp \
    fragmentmodel.cpp \
    videofilewriter.cpp \
    videosettings.cpp \
    fragmentsaver.cpp \
    excelhelper.cpp \
    excelreportcreator.cpp \
    WidgetFileTree/filetree.cpp \
    WidgetFileTree/filetreedialog.cpp \
    WidgetFileTree/treeitem.cpp \
    WidgetFileTree/treemodel.cpp \
    ReportCreator/htmlbuilder.cpp \
    ReportCreator/htmltemplatebuilder.cpp \
    ReportCreator/reportdialog.cpp \
    testanalysiswidget.cpp \
    coordinatesconverter.cpp \
    uvgraphicsview.cpp

HEADERS += \
        mainwindow.h \
    videofilereader.h \
    ktime.h \
    labelevent.h \
    analysisform.h \
    addfragmentcommentdialog.h \
    fragmentinfo.h \
    fragmentmodel.h \
    videofilewriter.h \
    videosettings.h \
    fragmentsaver.h \
    excelhelper.h \
    excelreportcreator.h \
    WidgetFileTree/filetree.h \
    WidgetFileTree/filetreedialog.h \
    WidgetFileTree/treeitem.h \
    WidgetFileTree/treemodel.h \
    ReportCreator/htmlbuilder.h \
    ReportCreator/htmltemplatebuilder.h \
    ReportCreator/reportdialog.h \
    testanalysiswidget.h \
    coordinatesconverter.h \
    uvgraphicsview.h

FORMS += \
        mainwindow.ui \
    analysisform.ui \
    addfragmentcommentdialog.ui \
    WidgetFileTree/filetree.ui \
    WidgetFileTree/filetreedialog.ui \
    ReportCreator/reportdialog.ui \
    testanalysiswidget.ui

INCLUDEPATH += C:/OpenCV-4.0.1/include \
                $$PWD/WidgetFileTree \
                $$PWD/ReportCreator

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

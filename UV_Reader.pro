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

CONFIG += c++17

SOURCES += \
    Analysis/analysisform.cpp \
    Analysis/contour.cpp \
    Analysis/crowncharge.cpp \
    Analysis/crownchargedetector.cpp \
    Analysis/fragmentmodel.cpp \
    Analysis/fragmentsaver.cpp \
    Analysis/testanalysiswidget.cpp \
    ReportCreator/htmlbuilder.cpp \
    ReportCreator/htmltemplatebuilder.cpp \
    ReportCreator/reportdialog.cpp \
    UVGraphicsView/uvgraphicsview.cpp \
    Video/crownchargepainter.cpp \
    Video/fragmentinfo.cpp \
    Video/videocontrolsform.cpp \
    Video/videofilereader.cpp \
    Video/videofilewriter.cpp \
    Video/videoplayer.cpp \
    Video/videosettings.cpp \
    WidgetFileTree/filetree.cpp \
    WidgetFileTree/filetreedialog.cpp \
    WidgetFileTree/treeitem.cpp \
    WidgetFileTree/treemodel.cpp \
    addfragmentcommentdialog.cpp \
    excelhelper.cpp \
    excelreportcreator.cpp \
    ktime.cpp \
    labelevent.cpp \
    main.cpp \
    mainwindow.cpp \
    Analysis/analyzer.cpp \
    maskcreateform.cpp \
    UVGraphicsView/rectitembuilder.cpp \
    masksaver.cpp \
    settingsbox.cpp \
    settingkeeper.cpp \
    Analysis/branch.cpp \
    Analysis/branchselector.cpp \
    percentkeeper.cpp \
    ColorSelectingSettings/colorselectionform.cpp \
    ColorSelectingSettings/colorselector.cpp \
    ColorSelectingSettings/colorselectorhsv.cpp \
    ColorSelectingSettings/colorselectorrgb.cpp \
    Analysis/binarizator.cpp

HEADERS += \
    Analysis/analysisform.h \
    Analysis/contour.h \
    Analysis/crowncharge.h \
    Analysis/crownchargedetector.h \
    Analysis/fragmentmodel.h \
    Analysis/fragmentsaver.h \
    Analysis/testanalysiswidget.h \
    ReportCreator/htmlbuilder.h \
    ReportCreator/htmltemplatebuilder.h \
    ReportCreator/reportdialog.h \
    UVGraphicsView/uvgraphicsview.h \
    Video/crownchargepainter.h \
    Video/fragmentinfo.h \
    Video/videocontrolsform.h \
    Video/videofilereader.h \
    Video/videofilewriter.h \
    Video/videoplayer.h \
    Video/videosettings.h \
    WidgetFileTree/filetree.h \
    WidgetFileTree/filetreedialog.h \
    WidgetFileTree/treeitem.h \
    WidgetFileTree/treemodel.h \
    addfragmentcommentdialog.h \
    excelhelper.h \
    excelreportcreator.h \
    ktime.h \
    labelevent.h \
    mainwindow.h \
    Analysis/analyzer.h \
    Video/asmOpenCV.h \
    Video/frame.h \
    maskcreateform.h \
    UVGraphicsView/rectitembuilder.h \
    masksaver.h \
    settingsbox.h \
    settingkeeper.h \
    abstractsettingstab.h \
    Analysis/branch.h \
    Analysis/branchsettings.h \
    Analysis/branchselector.h \
    percentkeeper.h \
    ColorSelectingSettings/colorselectionform.h \
    ColorSelectingSettings/colorselector.h \
    ColorSelectingSettings/colorselectorhsv.h \
    ColorSelectingSettings/colorselectorrgb.h \
    filtersettings.h \
    Analysis/binarizator.h

FORMS += \
    Analysis/analysisform.ui \
    Analysis/testanalysiswidget.ui \
    ReportCreator/reportdialog.ui \
    Video/videocontrolsform.ui \
    WidgetFileTree/filetree.ui \
    WidgetFileTree/filetreedialog.ui \
    addfragmentcommentdialog.ui \
    mainwindow.ui \
    maskcreateform.ui \
    settingsbox.ui \
    ColorSelectingSettings/colorselectionform.ui \
    ColorSelectingSettings/colorselector.ui

INCLUDEPATH += C:/OpenCV-4.0.1/include \
                $$PWD/WidgetFileTree \
                $$PWD/ReportCreator \
                $$PWD/UVGraphicsView \
                $$PWD/Analysis \
                $$PWD/Video \
                $$PWD/ColorSelectingSettings

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

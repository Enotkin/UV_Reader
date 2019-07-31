#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTimerEvent>
#include <QThread>
#include <memory>
#include <QTimer>
#include <ktime.h>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <addfragmentcommentdialog.h>
#include <analysisform.h>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "videofilereader.h"
#include "WidgetFileTree/filetreedialog.h"
#include "fragmentinfo.h"
#include "testanalysiswidget.h"
#include "maskcreateform.h"
#include "settingkeeper.h"

namespace Ui {
class MainWindow;
}

namespace ButtomTexts {
    const QString StartPlaying = "Начать воспроизведение";
    const QString PausePlaying = "Пауза";

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void playFragment(FragmentInfo fragment);
    void stopFragment();

private slots:

    void on_openFileAction_triggered();

    void on_closeFileAction_triggered();

    void on_closeAppAction_triggered();

    void on_addFragmentCommentAction_triggered();

    void openVideoFile(const QString &pathToFile);

    void on_toggleVideoZoomingAction_triggered();

    void on_settingsAction_triggered(bool checked);

    void on_showAnalysisPanelAction_triggered(bool checked);

    void on_startAnalysisAction_triggered();

private:
    Ui::MainWindow *ui;
    FileTreeDialog fileTreeDialog;

    QGraphicsPixmapItem pixmapItem;
    QTimer timer;
    QFileInfo fileInfo;
    int timerSpeed = 40;

    void connectMaskCreaterToGraphicsView();
    void connectColorSelectionForm();
    void setEnadledActions(bool state);

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTimerEvent>
#include <QThread>
#include <memory>
#include <QTimer>
#include <ktime.h>
#include <QSettings>
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

namespace Ui {
class MainWindow;
}

namespace ButtomTexts {
    const QString StartPlaying = "Начать воспроизведение";
    const QString PausePlaying = "Пауза";

}

namespace SettingTitles {
    const QString DefaultPathSettingsTitle = "Default_Path";
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void playFragment(FragmentInfo fragment);

private slots:

    void on_openFileAction_triggered();

    void on_closeFileAction_triggered();

    void on_closeAppAction_triggered();

    void on_addFragmentCommentAction_triggered();

    void openVideoFile(const QString &pathToFile);

    void on_toggleVideoZoomingAction_triggered();

    void on_actionTestMaskCreate_triggered(bool checked);

    void on_actionTestAnalysis_triggered(bool checked);

    void on_analysisPanelAction_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QSettings> settings;
    std::shared_ptr<VideoFileReader> videoData;
    FileTreeDialog fileTreeDialog;

    QGraphicsPixmapItem pixmapItem;
    QTimer timer;
    QFileInfo fileInfo;
    int timerSpeed = 40;

};

#endif // MAINWINDOW_H

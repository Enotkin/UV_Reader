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

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void timeChangeFrame();

    void on_horizontalSlider_sliderPressed();

    void on_currentFrameSpinBox_valueChanged(int arg1);

    void on_frameSpinBox_valueChanged(int arg1);

    void on_openFileAction_triggered();

    void on_closeFileAction_triggered();

    void on_closeAppAction_triggered();

    void on_stopPlayAction_triggered();

    void on_nextFrameAction_triggered();

    void on_prevFrameAction_triggered();

    void on_goToBeginAction_triggered();

    void on_goToEndAction_triggered();

    void on_playPauseAction_triggered();

    void on_addFragmentCommentAction_triggered();

    void on_analysisPanelAction_triggered();

    void openVideoFile(const QString &pathToFile);

    void on_actionTestAnalysis_triggered();

    void on_toggleVideoZoomingAction_triggered();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<QSettings> settings;
    std::shared_ptr<VideoFileReader> videoData;
    FileTreeDialog fileTreeDialog;
    std::unique_ptr<TestAnalysisWidget> testAnalysisWidget;

    QGraphicsScene scene;
    QGraphicsPixmapItem pixmapItem;
    QTimer timer;
    QFileInfo fileInfo;
    int timerSpeed = 40;


    void changeFrame(const int numberFrame);
    void setEmptyFrame();
    void setHorizontalSliderValue(const int value);
    void setTimeLabel(const double value);
    void setNumberFrameLabel(const int value);
    void setupMediaControlsToolBar();
    QString msecToStringFormat(const double value);
};

#endif // MAINWINDOW_H

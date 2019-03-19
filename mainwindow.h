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

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "videofilereader.h"

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

private:
    Ui::MainWindow *ui;
    std::unique_ptr<VideoFileReader> videoData;
    std::unique_ptr<QSettings> settings;
    QTimer timer;
    QFileInfo fileInfo;
    int timerSpeed = 40;
    const QString defaultPathSettingsTitle = "Default_Path";

    void changeFrame(const int numberFrame);
    void setEmptyFrame();
    void setSpinBoxValue(const int value);
    void setHorizontalSliderValue(const int value);
    void setTimeLabel(const double value);
    void setNumberFrameLabel(const int value);
    void setupMediaControlsToolBar();
    QString msecToStringFormat(const double value);
};

#endif // MAINWINDOW_H

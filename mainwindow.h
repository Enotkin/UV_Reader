#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTimerEvent>
#include <QThread>
#include <memory>
#include <QTimer>
#include <QSettings>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "videofilereader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

    void on_startStopPushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_prevFramePushButton_clicked();

    void on_nextFramePushButton_clicked();

    void timeToChangeFrame();

    void on_horizontalSlider_sliderPressed();

    void on_currentFrameSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    std::unique_ptr<VideoFileReader> videoData;
    std::unique_ptr<QSettings> settings;
    QTimer timer;
    QFileInfo fileInfo;
    int timerSpeed = 40;
    const QString defaultPathSettingsTitle = "Default_Path";

    void changeFrame(int numberFrame);
};

#endif // MAINWINDOW_H

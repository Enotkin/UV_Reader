#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QThread>
#include <memory>

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

public slots:
    void newQImage(QImage image, int count);
    void fileEnded();

private slots:
    void on_action_triggered();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_sliderPressed();

    void on_pushButtonPlayPause_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<VideoFileReader> videoData;
    QFileInfo fileInfo;

    void openfile();
    void connectVideoDataControl();
    void setStartPositionVideoData();
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newQImage(QImage image, int count)
{
    if (!image.isNull()) {
        QPixmap pixmap = QPixmap::fromImage(image);
        ui->horizontalSlider->setValue(count);
        ui->label->setPixmap(pixmap);
    }
}

void MainWindow::fileEnded()
{
    ui->pushButtonPlayPause->setText("Start");
}

void MainWindow::on_action_triggered()
{
    openfile();
    connectVideoDataControl();
    setStartPositionVideoData();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    videoData->setFrame(position);
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    videoData->stop();
}

void MainWindow::on_pushButtonPlayPause_clicked()
{
    if (videoData->isPlaying()){
        videoData->stop();
        ui->pushButtonPlayPause->setText("Start");
    } else {
        videoData->start();
        ui->pushButtonPlayPause->setText("Stop");
    }
}

void MainWindow::openfile()
{
    fileInfo.setFile(QFileDialog::getOpenFileName());
    ui->statusBar->showMessage(fileInfo.absoluteFilePath());
    videoData = std::make_unique<VideoFileReader>(fileInfo);
}

void MainWindow::connectVideoDataControl()
{
    connect(videoData.get(), &VideoFileReader::newImageReady, this, &MainWindow::newQImage, Qt::QueuedConnection);
    connect(videoData.get(), &VideoFileReader::fileEnded, this, &MainWindow::fileEnded);
}

void MainWindow::setStartPositionVideoData()
{
    ui->horizontalSlider->setRange(0, videoData->coutFrames());
    QPixmap pixmap = QPixmap::fromImage(videoData->getPreview());
    ui->label->setPixmap(pixmap);
}

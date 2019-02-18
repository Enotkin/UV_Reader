#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, &QTimer::timeout, this, &MainWindow::timeToChangeFrame);
    settings = std::make_unique<QSettings>("settings.ini", QSettings::IniFormat);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeFrame(int numberFrame)
{
    if (videoData){
        QPixmap pixmap = QPixmap::fromImage(videoData->getFrame(numberFrame));
        ui->displayOfImage->setPixmap(pixmap);
        ui->horizontalSlider->blockSignals(true);
        ui->horizontalSlider->setValue(numberFrame);
        ui->horizontalSlider->blockSignals(false);
        ui->currentFrameSpinBox->blockSignals(true);
        ui->currentFrameSpinBox->setValue(numberFrame);
        ui->currentFrameSpinBox->blockSignals(false);
        ui->currentFrameSpinBox->setValue(numberFrame);
        ui->timeLabel->setText(QString("%1 сек.").arg(static_cast<double>(videoData->getTime()/1000), 0, 'f', 1));
    }
}

void MainWindow::timeToChangeFrame()
{
    changeFrame(videoData->getCurrentFrameNumber());
    if (videoData->getCurrentFrameNumber() == videoData->getCountFrames()){
        timer.stop();
        videoData->setCurrentFrameNumber(0);
    }
}

void MainWindow::on_action_triggered()
{
    if (settings->value(defaultPathSettingsTitle).toString().isNull())
        fileInfo.setFile(QFileDialog::getOpenFileName(this, "Выбор файла"));
    else
        fileInfo.setFile(QFileDialog::getOpenFileName(this, "Выбор файла", settings->value(defaultPathSettingsTitle).toString()));
    settings->setValue(defaultPathSettingsTitle, fileInfo.absolutePath());

    ui->statusBar->showMessage(fileInfo.absoluteFilePath());
    videoData = std::make_unique<VideoFileReader>(fileInfo);

    ui->horizontalSlider->setRange(0, videoData->getCountFrames()-1);
    ui->maxFrameLabel->setText(" / " + QString::number(videoData->getCountFrames()-1));
    changeFrame(0);
}

void MainWindow::on_startStopPushButton_clicked()
{
    if (timer.isActive()) {
        timer.stop();
    }else {
        timer.start(timerSpeed);
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    changeFrame(value);
}

void MainWindow::on_prevFramePushButton_clicked()
{
    changeFrame(videoData->getCurrentFrameNumber()-2);
}

void MainWindow::on_nextFramePushButton_clicked()
{
    changeFrame(videoData->getCurrentFrameNumber());
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    timer.stop();
}

void MainWindow::on_currentFrameSpinBox_valueChanged(int arg1)
{
    changeFrame(arg1);
}

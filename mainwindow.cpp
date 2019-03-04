#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, &QTimer::timeout, this, &MainWindow::timeChangeFrame);
    settings = std::make_unique<QSettings>("settings.ini", QSettings::IniFormat);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeFrame(const int numberFrame)
{
    if (videoData){
        ui->displayOfImage->setPixmap(QPixmap::fromImage(videoData->getFrame(numberFrame)));
        this->setHorizontalSliderValue(numberFrame);
//        this->setSpinBoxValue(numberFrame);
        this->setTimeLabel(videoData->getTime());
        this->setNumberFrameLabel(numberFrame);
    }
}

void MainWindow::setSpinBoxValue(const int value)
{
    ui->frameSpinBox->blockSignals(true);
    ui->frameSpinBox->setValue(value);
    ui->frameSpinBox->blockSignals(false);
}

void MainWindow::setHorizontalSliderValue(const int value)
{
    ui->horizontalSlider->blockSignals(true);
    ui->horizontalSlider->setValue(value);
    ui->horizontalSlider->blockSignals(false);
}

void MainWindow::setTimeLabel(const double value)
{
    auto result = QString("%1 / %2")
            .arg(msecToStringFormat(value))
            .arg(msecToStringFormat(videoData->getVideoDuration()));
    ui->timeLabel->setText(result);
}

void MainWindow::setNumberFrameLabel(const int value)
{
    auto result = QString("%1 / %2")
            .arg(value)
            .arg(videoData->getCountFrames());
    ui->framesLabel->setText(result);
}

QString MainWindow::msecToStringFormat(const double value)
{
    KTime time(0, 0, 0, static_cast<int>(value));
    return time.toString();
}

void MainWindow::timeChangeFrame()
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
    ui->frameSpinBox->setRange(0, videoData->getCountFrames());
    this->changeFrame(0);
}

void MainWindow::on_startStopPushButton_clicked()
{
    if(videoData){
        if (timer.isActive()) {
            timer.stop();
            ui->startStopPushButton->setIcon(QIcon(":/play.png"));
        }else {
            timer.start(timerSpeed);
            ui->startStopPushButton->setIcon(QIcon(":/pause.png"));
        }
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    if (videoData){
      changeFrame(value);
    }
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

void MainWindow::on_frameSpinBox_valueChanged(int arg1)
{
    if (videoData){
      changeFrame(arg1);
    }
}

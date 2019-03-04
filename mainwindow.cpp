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
        this->setSpinBoxValue(numberFrame);
        this->setTimeValue(videoData->getTime());
    }
}

void MainWindow::setSpinBoxValue(const int value)
{
    ui->currentFrameSpinBox->blockSignals(true);
    ui->currentFrameSpinBox->setValue(value);
    ui->currentFrameSpinBox->blockSignals(false);
}

void MainWindow::setHorizontalSliderValue(const int value)
{
    ui->horizontalSlider->blockSignals(true);
    ui->horizontalSlider->setValue(value);
    ui->horizontalSlider->blockSignals(false);
}

void MainWindow::setTimeValue(const double value)
{
    QString result;
    result.append(msecToStringFormat(value));
    result.append("/");
    result.append(msecToStringFormat(videoData->getVideoDuration()));
    qDebug()<<value << videoData->getVideoDuration();
    ui->timeLabel->setText(result);
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
    ui->maxFrameLabel->setText(" / " + QString::number(videoData->getCountFrames()-1));
    qDebug()<< videoData->getVideoDuration();
    changeFrame(0);
}

void MainWindow::on_startStopPushButton_clicked()
{
    if(videoData){
        if (timer.isActive()) {
            timer.stop();
        }else {
            timer.start(timerSpeed);
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

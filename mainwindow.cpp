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

void MainWindow::setSpinBoxValue(const int value)
{
    ui->frameSpinBox->blockSignals(true);
    ui->frameSpinBox->setValue(value);
    ui->frameSpinBox->blockSignals(false);
}

void MainWindow::setHorizontalSliderValue(const int value)
{
    int sads = 44;
    ui->horizontalSlider->blockSignals(true);
    ui->horizontalSlider->setValue(value);
    ui->horizontalSlider->blockSignals(false);
}

void MainWindow::setTimeLabel(const double value)
{
    if (videoData){
        auto result = QString("%1 / %2")
                .arg(msecToStringFormat(value))
                .arg(msecToStringFormat(videoData->getVideoDuration()));
        ui->timeLabel->setText(result);
    } else {
        auto result = QString("%1 / %2")
                .arg("-")
                .arg("-");
        ui->timeLabel->setText(result);
    }
}

void MainWindow::setNumberFrameLabel(const int value)
{
    if (videoData){
        auto result = QString("%1 / %2")
                .arg(value)
                .arg(videoData->getCountFrames());
        ui->framesLabel->setText(result);
    } else {
        auto result = QString("%1 / %2")
                .arg("-")
                .arg("-");
        ui->framesLabel->setText(result);
    }
}

QString MainWindow::msecToStringFormat(const double value)
{
    KTime time(0, 0, 0, static_cast<int>(value));
    return time.toString();
}

void MainWindow::timeChangeFrame()
{
    this->changeFrame(videoData->getCurrentFrameNumber());
    if (videoData->getCurrentFrameNumber() == videoData->getCountFrames()){
        timer.stop();
        videoData->setCurrentFrameNumber(0);
    }
}

void MainWindow::changeFrame(const int numberFrame)
{
    if (videoData){
        ui->displayOfImage->setImage(videoData->getFrame(numberFrame));
        this->setTimeLabel(videoData->getTime());
        this->setHorizontalSliderValue(numberFrame);
        this->setNumberFrameLabel(numberFrame);
    }
}

void MainWindow::setEmptyFrame()
{
    ui->displayOfImage->clear();
    this->setTimeLabel(0.0);
    this->setHorizontalSliderValue(0);
    this->setNumberFrameLabel(0);
}

void MainWindow::on_startStopPushButton_clicked()
{
    if (videoData)
        if (timer.isActive()){
            ui->stopPlayAction->trigger();
        } else {
            timer.start(timerSpeed);
            ui->startStopPushButton->setIcon(QIcon(":/pause.png"));
        }
}

void MainWindow::on_playPauseAction_triggered()
{

    if (videoData)
        if (timer.isActive()){
            timer.stop();
            ui->startStopPushButton->setIcon(QIcon(":/play.png"));
        } else {
            timer.start(timerSpeed);
            ui->startStopPushButton->setIcon(QIcon(":/pause.png"));
        }
}

void MainWindow::on_startPlayAction_triggered()
{

}

void MainWindow::on_stopPlayAction_triggered()
{
    timer.stop();
    ui->startStopPushButton->setIcon(QIcon(":/play.png"));
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
      this->changeFrame(value);
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    timer.stop();
}

void MainWindow::on_currentFrameSpinBox_valueChanged(int arg1)
{
    this->changeFrame(arg1);
}

void MainWindow::on_frameSpinBox_valueChanged(int arg1)
{
    this->changeFrame(arg1);
}

void MainWindow::on_openFileAction_triggered()
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

void MainWindow::on_closeFileAction_triggered()
{
    if (videoData){
        videoData.release();
        ui->horizontalSlider->setRange(0, 1);
        ui->frameSpinBox->setRange(0, 1);
        ui->statusBar->showMessage("");
        setEmptyFrame();
    }
}

void MainWindow::on_closeAppAction_triggered()
{
    QCoreApplication::exit();
}

void MainWindow::on_prevFrameAction_triggered()
{
    this->changeFrame(videoData->getCurrentFrameNumber()-2);
}

void MainWindow::on_nextFrameAction_triggered()
{
    this->changeFrame(videoData->getCurrentFrameNumber());
}

void MainWindow::on_goToBeginAction_triggered()
{
    this->changeFrame(0);
}

void MainWindow::on_goToEndAction_triggered()
{
    this->changeFrame(videoData->getCountFrames());
}





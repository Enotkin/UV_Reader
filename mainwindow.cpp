#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->analysisWidget->hide();
    connect(&timer, &QTimer::timeout, this, &MainWindow::timeChangeFrame);
    settings = std::make_unique<QSettings>("settings.ini", QSettings::IniFormat);
    setupMediaControlsToolBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setHorizontalSliderValue(const int value)
{
    ui->horizontalSlider->blockSignals(true);
    ui->horizontalSlider->setValue(value);
    ui->horizontalSlider->blockSignals(false);
}

void MainWindow::setTimeLabel(const double value)
{
    if (videoData){
        auto result = QString("%1 / %2")
                .arg(msecToStringFormat(value))
                .arg(msecToStringFormat(videoData->getSettings().getDuration()));
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
                .arg(videoData->getSettings().getCountFrames());
        ui->framesLabel->setText(result);
    } else {
        auto result = QString("%1 / %2")
                .arg("-")
                .arg("-");
        ui->framesLabel->setText(result);
    }
}

void MainWindow::setupMediaControlsToolBar()
{
    auto toolbar = new QToolBar(ui->controlButtomsWidget);
    toolbar->setIconSize(QSize(24, 24));
    toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toolbar->addAction(ui->goToBeginAction);
    toolbar->addAction(ui->prevFrameAction);
    toolbar->addAction(ui->playPauseAction);
    toolbar->addAction(ui->nextFrameAction);
    toolbar->addAction(ui->goToEndAction);
    ui->controlButtomsWidget->layout()->addWidget(toolbar);
}

QString MainWindow::msecToStringFormat(const double value)
{
    KTime time(0, 0, 0, static_cast<int>(value));
    return time.toString();
}

void MainWindow::timeChangeFrame()
{
    this->changeFrame(videoData->getCurrentFrameNumber());
    if (videoData->getCurrentFrameNumber() == videoData->getSettings().getCountFrames()){
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

void MainWindow::on_playPauseAction_triggered()
{
    if (!videoData)
        return;
    if (timer.isActive()){
        timer.stop();
        ui->playPauseAction->setIcon(QIcon(":/mediaIcons/play.png"));
        ui->playPauseAction->setText(ButtomTexts::StartPlaying);
        ui->playPauseAction->setToolTip(ButtomTexts::StartPlaying);
    } else {
        timer.start(timerSpeed);
        ui->playPauseAction->setIcon(QIcon(":/mediaIcons/pausa.png"));
        ui->playPauseAction->setText(ButtomTexts::PausePlaying);
        ui->playPauseAction->setToolTip(ButtomTexts::PausePlaying);
    }
}

void MainWindow::on_stopPlayAction_triggered()
{
    timer.stop();
    ui->goToBeginAction->trigger();
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
    videoData = std::make_shared<VideoFileReader>(fileInfo);

    ui->videoPlaybackMenu->setEnabled(true);
    ui->analysisMenu->setEnabled(true);

    ui->horizontalSlider->setRange(0, videoData->getSettings().getCountFrames()-1);
    ui->frameSpinBox->setRange(0, videoData->getSettings().getCountFrames());
    this->changeFrame(0);
}

void MainWindow::on_closeFileAction_triggered()
{
    if (videoData){
        videoData.reset();
        ui->horizontalSlider->setRange(0, 1);
        ui->frameSpinBox->setRange(0, 1);
        ui->statusBar->showMessage("");
        ui->analysisWidget->clear();
        ui->videoPlaybackMenu->setEnabled(false);
        ui->analysisMenu->setEnabled(false);
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
    this->changeFrame(videoData->getSettings().getCountFrames());
}

void MainWindow::on_addFragmentCommentAction_triggered()
{
    ui->analysisWidget->setVisible(true);
    ui->analysisWidget->addIntervalComment();
}

void MainWindow::on_analysisPanelAction_triggered()
{
    ui->analysisWidget->setVisible(!ui->analysisWidget->isVisible());
}

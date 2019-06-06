#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showFullScreen();
    this->showMaximized();
    ui->analysisWidget->hide();
    connect(&timer, &QTimer::timeout, this, &MainWindow::timeChangeFrame);
    connect(&fileTreeDialog, &FileTreeDialog::signalSelectedFile, this, &MainWindow::openVideoFile);
    connect(ui->analysisWidget, &AnalysisForm::playFragmet, this, &MainWindow::playFragment);
    settings = std::make_unique<QSettings>("settings.ini", QSettings::IniFormat);

    auto view = ui->graphicsView;
    auto viewMethod = [view](const QImage &image) mutable {view->setImage(image);};
    ui->videoControls->setView(viewMethod);

    //setupMediaControlsToolBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playFragment(FragmentInfo fragment)
{
    qDebug()<<"FragmentInfo in MainWindow:"<<fragment.getFrameRange();

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
        ui->graphicsView->setImage(videoData->getFrame(numberFrame));
//        pixmapItem.setPixmap(QPixmap::fromImage(videoData->getFrame(numberFrame)));
//        ui->graphicsView->fitInView(scene.itemsBoundingRect(), Qt::KeepAspectRatio);
        this->setTimeLabel(videoData->getTime());
        this->setHorizontalSliderValue(numberFrame);
        this->setNumberFrameLabel(numberFrame);
    }
}

void MainWindow::setEmptyFrame()
{
//    scene.clear();
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
    ui->testAnalisysWidget->setFrame(value);
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
    fileTreeDialog.show();
    bool defaultPathIsExist = !settings->value(SettingTitles::DefaultPathSettingsTitle).toString().isNull();
    if (defaultPathIsExist)
        fileTreeDialog.setRootDir(settings->value(SettingTitles::DefaultPathSettingsTitle).toString());
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

void MainWindow::openVideoFile(const QString &pathToFile)
{
    if (pathToFile == fileInfo.absoluteFilePath())
        return;   
    fileInfo.setFile(pathToFile);
    ui->analysisWidget->setFileInfo(fileInfo);
    ui->videoControls->setSourceVideoFile(fileInfo);
//    videoPlayer.setSoureceFile(fileInfo);

    settings->setValue(SettingTitles::DefaultPathSettingsTitle, fileTreeDialog.getRootDir());

    ui->statusBar->showMessage(fileInfo.absoluteFilePath());
    videoData = std::make_shared<VideoFileReader>(fileInfo);
    ui->analysisWidget->setVideoData(videoData);

    ui->videoPlaybackMenu->setEnabled(true);
    ui->analysisMenu->setEnabled(true);

    ui->horizontalSlider->setRange(0, videoData->getSettings().getCountFrames()-1);
    ui->frameSpinBox->setRange(0, videoData->getSettings().getCountFrames());
    this->changeFrame(0);
}


void MainWindow::on_toggleVideoZoomingAction_triggered()
{
    ui->graphicsView->setResizeMode(!ui->graphicsView->getResizeMode());
}

void MainWindow::on_actionTestMaskCreate_triggered(bool checked)
{
    if (checked){
        ui->graphicsView->setEditMode(true);
    }else {
        ui->graphicsView->setEditMode(false);
        auto rects = ui->graphicsView->getMaskRect();
        ui->testAnalisysWidget->setMaskRects(ui->graphicsView->getMaskRect());
        ui->analysisWidget->setMask(ui->graphicsView->getMaskRect());
    }
}

void MainWindow::on_actionTestAnalysis_triggered(bool checked)
{
    ui->testAnalisysWidget->setVisible(checked);
    if (ui->testAnalisysWidget->isVisible()){
        ui->testAnalisysWidget->setSourceFile(fileInfo);
    }
}

void MainWindow::on_analysisPanelAction_triggered(bool checked)
{
    ui->analysisWidget->setVisible(checked);
}

void MainWindow::on_pushButton_clicked()
{
//    videoPlayer.reset();
}

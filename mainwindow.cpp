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
    connect(&fileTreeDialog, &FileTreeDialog::signalSelectedFile, this, &MainWindow::openVideoFile);
    connect(ui->analysisWidget, &AnalysisForm::playFragmet, this, &MainWindow::playFragment);
    settings = std::make_unique<QSettings>("settings.ini", QSettings::IniFormat);

    auto view = ui->graphicsView;
    auto viewMethod = [view](const QImage &image) mutable {view->setImage(image);};
    ui->videoControls->setView(viewMethod);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playFragment(FragmentInfo fragment)
{
    ui->videoControls->setFragment(fragment);
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
        ui->statusBar->showMessage("");
        ui->analysisWidget->clear();
        ui->videoPlaybackMenu->setEnabled(false);
        ui->analysisMenu->setEnabled(false);
}

void MainWindow::on_closeAppAction_triggered()
{
    QCoreApplication::exit();
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
    ui->graphicsView->resizeImage();

    settings->setValue(SettingTitles::DefaultPathSettingsTitle,
                       fileTreeDialog.getRootDir());

    ui->statusBar->showMessage(fileInfo.absoluteFilePath());
    videoData = std::make_shared<VideoFileReader>(fileInfo);
    ui->analysisWidget->setVideoData(videoData);

    ui->videoPlaybackMenu->setEnabled(true);
    ui->analysisMenu->setEnabled(true);
}


void MainWindow::on_toggleVideoZoomingAction_triggered()
{
    ui->graphicsView->setResizeMode(ui->toggleVideoZoomingAction->isChecked());
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

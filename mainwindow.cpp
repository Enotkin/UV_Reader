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
    setEnadledActions(false);

    connectMaskCreaterToGraphicsView();
    connectColorSelectionForm();
    connect(&fileTreeDialog, &FileTreeDialog::signalSelectedFile, this, &MainWindow::openVideoFile);

    connect(ui->analysisWidget, &AnalysisForm::playFragment, this, &MainWindow::playFragment);
    connect(ui->analysisWidget, &AnalysisForm::stopFragment, this, &MainWindow::stopFragment);

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
    ui->videoControls->play();
}

void MainWindow::stopFragment()
{
    ui->videoControls->stop();
}

void MainWindow::on_openFileAction_triggered()
{
    fileTreeDialog.show();
    auto defaultPath = SettingKeeper::getInstance()->loadDefaultPath();
    if (defaultPath)
        fileTreeDialog.setRootDir(defaultPath.value());
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

    SettingKeeper::getInstance()->setCurrentFile(fileInfo);
    ui->graphicsView->setFileName(fileInfo.baseName());
    setEnadledActions(true);
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

void MainWindow::on_settingsAction_triggered(bool checked)
{
    if (checked)
        ui->settingsWidget->showTabs(SettingsMode::MaskMode);
    else
        ui->settingsWidget->hideTabs();
    ui->graphicsView->resizeImage();
}

void MainWindow::connectMaskCreaterToGraphicsView()
{
    auto maskForm = ui->settingsWidget->getMaskWidget();

    connect(ui->graphicsView, &UvGraphicsView::addRect, maskForm, &MaskCreateForm::addItem);
    connect(ui->graphicsView, &UvGraphicsView::rectSelected, maskForm, &MaskCreateForm::selectItem);

    connect(maskForm, &MaskCreateForm::itemSelected, ui->graphicsView, &UvGraphicsView::selectItemRect);
    connect(maskForm, &MaskCreateForm::itemRemoved, ui->graphicsView, &UvGraphicsView::removeItemRect);
    connect(maskForm, &MaskCreateForm::setEditMode, ui->graphicsView, &UvGraphicsView::setEditMaskMode);
    connect(maskForm, &MaskCreateForm::setShowMode, ui->graphicsView, &UvGraphicsView::setShowMaskMode);
    connect(maskForm, &MaskCreateForm::clearAll, ui->graphicsView, &UvGraphicsView::clearMasks);
}

void MainWindow::connectColorSelectionForm()
{
    auto colorForm = ui->settingsWidget->getColorWidget();

    connect(colorForm, &ColorSelectionForm::turnOnColorSelection, ui->graphicsView, &UvGraphicsView::setColorSelectionMode);
    connect(ui->graphicsView, &UvGraphicsView::colorSelected, colorForm, &ColorSelectionForm::setColor);
}

void MainWindow::setEnadledActions(bool state)
{
    ui->settingsAction->setEnabled(state);
    ui->showAnalysisPanelAction->setEnabled(state);
    ui->startAnalysisAction->setEnabled(state);
}

void MainWindow::on_showAnalysisPanelAction_triggered(bool checked)
{
    if (ui->settingsWidget->isVisible()){
        on_settingsAction_triggered(false);
        ui->settingsAction->setChecked(false);
    }
     ui->analysisWidget->setVisible(checked);
}

void MainWindow::on_startAnalysisAction_triggered()
{
    if (ui->settingsWidget->isVisible()){
        on_settingsAction_triggered(false);
        ui->settingsAction->setChecked(false);
    }
    ui->analysisWidget->setVisible(true);
    ui->analysisWidget->startAnalysis();
}

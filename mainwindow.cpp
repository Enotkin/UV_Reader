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
    connectMaskCreaterToGraphicsView();
    connectColorSelectionForm();
    connect(&fileTreeDialog, &FileTreeDialog::signalSelectedFile, this, &MainWindow::openVideoFile);
    connect(ui->analysisWidget, &AnalysisForm::playFragmet, this, &MainWindow::playFragment);

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
        ui->settingsWidget->showTabs(SettingsMode::MaskMode);
    } else {
        ui->settingsWidget->hideTabs();
    }
    ui->graphicsView->resizeImage();
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

void MainWindow::on_actionSettings_triggered()
{
    ui->settingsWidget->show();
}

#include "analysisform.h"
#include "ui_analysisform.h"

AnalysisForm::AnalysisForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::analysisForm)
{
    ui->setupUi(this);
    ui->infoPanel->setVisible(false);
    setupUI();

    model = std::make_unique<FragmentModel>();
    model->addFragment(FragmentInfo(FrameRange{51,85},PillarRange{QString(),QString()}, TimeRange{QTime(), QTime()}, QString()));
    connect(model.get(), &FragmentModel::rowsInserted, this, &AnalysisForm::buttomEnableSwitcher);
    connect(model.get(), &FragmentModel::rowsRemoved, this, &AnalysisForm::buttomEnableSwitcher);

    ui->tableView->setModel(model.get());
    ui->tableView->resizeColumnsToContents();
    buttomEnableSwitcher(QModelIndex(), 0, 0);
}

void AnalysisForm::addIntervalComment()
{
    ui->actionAddIntervalComment->trigger();
}

void AnalysisForm::clear()
{
    model->clearModel();
}

AnalysisForm::~AnalysisForm()
{
    delete ui;
}

void AnalysisForm::buttomEnableSwitcher(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    model->isContainsVideoFragment() ? setVideoControlButtomEnabled(true)
                                     : setVideoControlButtomEnabled(false);
    model->isEmpty() ?  setDeleteButtomEnabeled(false)
                     : setDeleteButtomEnabeled(true);
}

void AnalysisForm::on_actionAddIntervalComment_triggered()
{
    AddFragmentCommentDialog dialog;
    dialog.setFrameInfo(50, 174);
    connect(&dialog, &AddFragmentCommentDialog::data, this, [&](FragmentInfo fragmentInfo){
        model->addFragment(fragmentInfo);
    });
    dialog.exec();
}

void AnalysisForm::on_tableView_doubleClicked(const QModelIndex &index)
{
    auto fragment = model->getFragment(index);
    qDebug()<<"FragmentInfo in AnalisysForm:"<<fragment.getFrameRange();
    emit playFragmet(fragment);
}

void AnalysisForm::on_actionDelete_triggered()
{
    model->removeFragment(ui->tableView->selectionModel()->selectedRows());
}

void AnalysisForm::on_actionClear_triggered()
{
    model->clearModel();
}

void AnalysisForm::on_actionHideAnalysisPanel_triggered()
{
    this->hide();
}

void AnalysisForm::setVideoControlButtomEnabled(const bool &state)
{
    ui->actionPlay->setEnabled(state);
    ui->actionStop->setEnabled(state);
    ui->actionPlayNext->setEnabled(state);
    ui->actionPlayPrev->setEnabled(state);
    ui->actionDeleteAndPlayNext->setEnabled(state);
    ui->actionSaveVideoFragment->setEnabled(state);
}

void AnalysisForm::setDeleteButtomEnabeled(const bool &state)
{
    ui->actionDelete->setEnabled(state);
    ui->actionClear->setEnabled(state);
    ui->actionExcelExport->setEnabled(state);
}



void AnalysisForm::setupUI()
{
    auto toolbar = new QToolBar(ui->groupBox);
    toolbar->setOrientation(Qt::Vertical);
    toolbar->setIconSize(QSize(32, 32));
    toolbar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toolbar->addAction(ui->actionDisplayFrame);
    toolbar->addAction(ui->actionPlayPrev);
    toolbar->addAction(ui->actionPlay);
    toolbar->addAction(ui->actionStop);
    toolbar->addAction(ui->actionPlayNext);
    toolbar->addAction(ui->actionDeleteAndPlayNext);
    toolbar->addAction(ui->actionDelete);
    toolbar->addAction(ui->actionClear);
    toolbar->addAction(ui->actionAddIntervalComment);
    toolbar->addAction(ui->actionExcelExport);
    toolbar->addAction(ui->actionSaveVideoFragment);
    toolbar->addAction(ui->actionHideAnalysisPanel);
    ui->groupBox->layout()->addWidget(toolbar);
    this->setVideoControlButtomEnabled(false);
}

void AnalysisForm::on_actionSaveVideoFragment_triggered()
{
    FragmentSaver saver(QFileDialog::getExistingDirectory(this, tr("Выбор директории для сохранений фрагментов")),
                        fileInfo.absoluteFilePath());
    auto fragments = model->getSelectedFragments();
    for (auto fragment : fragments){
         saver.saveFragment(fragment);
    }
}

void AnalysisForm::setVideoData(const std::shared_ptr<VideoFileReader> &value)
{
    videoData = value;
}

void AnalysisForm::setMask(const QList<QRect> &value)
{
    mask = value;
}

void AnalysisForm::on_actionExcelExport_triggered()
{
    ExcelHelper excel(true);
    QDir dir(QFileDialog::getExistingDirectory(this, tr("Выбор директории для сохранения отчёта")),
          fileInfo.absoluteFilePath());
    int numTrip = 0;
    while(dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs).contains(QString("Отчёт участок name%1").arg(numTrip)))
        numTrip++;
    dir.mkdir(QString("Отчёт участок name%1").arg(numTrip));
    dir.cd(QString("Отчёт участок name%1").arg(numTrip));

    //Установка заголовка
    excel.MergeCells("B2:I2");
    excel.SetCellValue(2, 2, "Ведомость УФ обследования");
    excel.SetHorizontalAlignment("B2", ExcelHelper::HA_CENTER);

    //Установка информации о привязке
    //Название поездки
    excel.MergeCells("B3:I3");
    excel.SetCellValue(3, 2, "Поездка: <нет>");
    excel.SetHorizontalAlignment("B3", ExcelHelper::HA_LEFT);

    //Название Участка
    excel.MergeCells("B4:I4");
    excel.SetCellValue(4, 2, "Участок: <нет>");
    excel.SetHorizontalAlignment("B4", ExcelHelper::HA_LEFT);

    //Дата
    excel.MergeCells("B5:I5");
    excel.SetCellValue(5, 2, "Дата: чч.мм.гг");
    excel.SetHorizontalAlignment("B5", ExcelHelper::HA_LEFT);

    //Название файла
    excel.MergeCells("B6:I6");
    excel.SetCellValue(6, 2, "Файл: <нет>");
    excel.SetHorizontalAlignment("B6", ExcelHelper::HA_LEFT);

    //Создание шапки таблицы
    excel.MergeCells("A7:A8");
    excel.SetCellValue(7, 1, "№");

    excel.MergeCells("B7:C7");
    excel.SetCellValue(7, 2, "Кадры");
    excel.SetCellValue(8, 2, "Начало");
    excel.SetCellValue(8, 3, "Конец");

    excel.MergeCells("D7:E7");
    excel.SetCellValue(7, 4, "Опора");
    excel.SetCellValue(8, 4, "Начало");
    excel.SetCellValue(8, 5, "Конец");

    excel.MergeCells("F7:G7");
    excel.SetCellValue(7, 6, "Время");
    excel.SetCellValue(8, 6, "Начало");
    excel.SetCellValue(8, 7, "Конец");

    excel.MergeCells("H7:H8");
    excel.SetCellValue(7, 8, "Примечание");


    int row = 9;
    int imageNumber = 1;
    int imageRowNumber = model->getFragments().size() + 1 + row;
    for (auto &fragment : model->getFragments()){
        excel.SetCellValue(row, 1, QString::number(imageNumber));
        excel.SetCellValue(row, 2, QString::number(fragment.getFrameRange().first));
        excel.SetCellValue(row, 3, QString::number(fragment.getFrameRange().second));
        excel.SetCellValue(row, 4, fragment.getPillarRange().first);
        excel.SetCellValue(row, 5, fragment.getPillarRange().second);
        excel.SetCellValue(row, 6, fragment.getTime().first.toString("hh:mm:ss"));
        excel.SetCellValue(row, 7, fragment.getTime().second.toString("hh:mm:ss"));
        excel.SetCellValue(row, 8, QString("См. рис. %1").arg(imageNumber));
        row++;
        imageNumber++;

        QString imageFileName = QString("Рисунок %1.png").arg(imageNumber);

        videoData->getQImage(fragment.getFrameNumberReport()).save(dir.absoluteFilePath(imageFileName));
        excel.SetCellValue(imageRowNumber, 1, QString("См. рис. %1").arg(imageNumber));

        QString range = QString("A%1:H%1").arg(imageRowNumber+1);
        excel.SetRowsHeight(range, 288);
        excel.AddPicture(range, dir.absoluteFilePath(imageFileName).replace("/", "\\"), true);
        imageRowNumber+=10;

    }
    excel.SaveAs(dir.absoluteFilePath("imageFileName.xlsx").replace("/", "\\"));
}

void AnalysisForm::setFileInfo(const QFileInfo &value)
{
    fileInfo = value;
}

void AnalysisForm::on_actionPlay_triggered()
{

}

void AnalysisForm::on_pushButtonStartAnalysis_clicked()
{
    auto analysis = new Analyzer(fileInfo);
    auto settings = assemblyBranchSettings();

    analysis->setSettings(settings);
    analysis->analyze();
    for (const auto &fragment : analysis->getFragments()){
        model->addFragment(fragment);
    }
}

void AnalysisForm::on_spinBoxDistanceBetweenCenterMass_valueChanged(int arg1)
{

}

BranchSettings AnalysisForm::assemblyBranchSettings()
{
    BranchSettings settings;
    settings.size = ui->spinBoxMinSizeCrownCharge->value();
    settings.lifeTime = ui->spinBoxLifeTime->value();
    settings.delta = ui->spinBox->value();
    return settings;
}

#include "analysisform.h"
#include "ui_analysisform.h"

AnalysisForm::AnalysisForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::analysisForm)
{
    ui->setupUi(this);
    setupUI();

    model = std::make_unique<FragmentModel>();
    connect(model.get(), &FragmentModel::rowsInserted, this, &AnalysisForm::buttomEnableSwitcher);
    connect(model.get(), &FragmentModel::rowsRemoved, this, &AnalysisForm::buttomEnableSwitcher);
    model->addFragment(FragmentInfo(64, "434D", QTime(0,3,4,0), "Добавленно"));
    model->addFragment(FragmentInfo(43, "423r", QTime(0,33,4,0), "Добавленно"));
    model->addFragment(FragmentInfo(12, "4T", QTime(0,3,34,0), "Добавленно"));
    model->addFragment(FragmentInfo(FrameRange(32, 214), PillarRange("5", "23d"), TimeRange(QTime(0,3,4,0), QTime(0,4,4,0)), "Добавленно"));

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
    //    this->setDeleteButtomEnabeled(false);
}

void AnalysisForm::on_actionSaveVideoFragment_triggered()
{
    QDir saveDir(QFileDialog::getExistingDirectory(this, tr("Выбор директории для сохранений фрагментов")));
    auto fragments = model->getSelectedFragments();
    for (auto fragment : fragments){
        if (fragment.isVideoFragment()){

        }else {

        }
    }
}

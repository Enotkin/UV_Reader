#include "analysisform.h"
#include "ui_analysisform.h"

AnalysisForm::AnalysisForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::analysisForm)
{
    ui->setupUi(this);
    setupUI();
    model = new FragmentModel();
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

void AnalysisForm::addIntervalComment()
{
//    ui->addIntervalCommentAction->trigger();
}

AnalysisForm::~AnalysisForm()
{
    delete ui;
}

void AnalysisForm::on_hideAnalysisPanelAction_triggered()
{
    this->hide();
}

void AnalysisForm::on_addIntervalCommentAction_triggered()
{
    AddFragmentCommentDialog dialog;
    dialog.setFrameInfo(50, 174);
    connect(&dialog, &AddFragmentCommentDialog::data, this, [&](FragmentInfo fragmentInfo){
        model->addFragment(fragmentInfo);
    });
    dialog.exec();
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

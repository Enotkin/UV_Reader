#include "analysisform.h"
#include "ui_analysisform.h"

AnalysisForm::AnalysisForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::analysisForm)
{
    ui->setupUi(this);
    model = new FragmentModel();
    ui->tableView->setModel(model);
}

void AnalysisForm::addIntervalComment()
{
    ui->addIntervalCommentAction->trigger();
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

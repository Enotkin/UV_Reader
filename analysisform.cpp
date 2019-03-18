#include "analysisform.h"
#include "ui_analysisform.h"

analysisForm::analysisForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::analysisForm)
{
    ui->setupUi(this);
}

analysisForm::~analysisForm()
{
    delete ui;
}

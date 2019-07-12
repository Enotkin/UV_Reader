#include "maskcreateform.h"
#include "ui_maskcreateform.h"

maskCreateForm::maskCreateForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::maskCreateForm)
{
    ui->setupUi(this);
}

maskCreateForm::~maskCreateForm()
{
    delete ui;
}

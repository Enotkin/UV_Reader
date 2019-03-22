#include "addfragmentcommentdialog.h"
#include "ui_addfragmentcommentdialog.h"

AddFragmentCommentDialog::AddFragmentCommentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFragmentCommentDialog)
{
    ui->setupUi(this);
}

void AddFragmentCommentDialog::setFrameInfo(int currentFrame, int maxFrame)
{
    ui->frameNumberSpinBox->setRange(0, maxFrame);
    ui->frameNumberSpinBox->setValue(currentFrame);
}

AddFragmentCommentDialog::~AddFragmentCommentDialog()
{
    delete ui;
}

void AddFragmentCommentDialog::on_addFragmentPushButton_clicked()
{
    emit data(FragmentInfo(ui->frameNumberSpinBox->value(),
                           ui->towerNameLineEdit->text(),
                           QTime(),
                           "Добавлено"));
    this->close();
}

void AddFragmentCommentDialog::on_cancelPushButton_clicked()
{
    this->close();
}

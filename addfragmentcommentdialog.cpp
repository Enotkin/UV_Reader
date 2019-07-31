#include "addfragmentcommentdialog.h"
#include "ui_addfragmentcommentdialog.h"

AddFragmentCommentDialog::AddFragmentCommentDialog(int maxFrame, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFragmentCommentDialog)
{
    ui->setupUi(this);
    ui->frameNumberMinSpinBox->setRange(0, maxFrame);
    ui->frameNumberMaxSpinBox->setRange(0, maxFrame);
}

AddFragmentCommentDialog::~AddFragmentCommentDialog()
{
    delete ui;
}

void AddFragmentCommentDialog::on_addFragmentPushButton_clicked()
{
    int minFrame = ui->frameNumberMinSpinBox->value();
    int maxFrame = ui->frameNumberMaxSpinBox->value();
    if (minFrame > maxFrame){
        QMessageBox::warning(this, tr("Ошибка"), tr("Диапазон задан не правильно"));
        return;
    }

    FragmentInfo info(FrameRange(minFrame, maxFrame), PillarRange(), TimeRange(), QString());

    emit data(info);
    this->close();
}

void AddFragmentCommentDialog::on_cancelPushButton_clicked()
{
    this->close();
}

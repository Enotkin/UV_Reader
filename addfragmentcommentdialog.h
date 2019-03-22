#ifndef ADDFRAGMENTCOMMENTDIALOG_H
#define ADDFRAGMENTCOMMENTDIALOG_H

#include <QDialog>
#include <QPair>

#include "fragmentinfo.h"

namespace Ui {
class addFragmentCommentDialog;
}

using FrameInfo = QPair<int, int>;

class AddFragmentCommentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFragmentCommentDialog(QWidget *parent = nullptr);
    void setFrameInfo(int currentFrame, int maxFrame);

    ~AddFragmentCommentDialog();

signals:
    void data(FragmentInfo);

private slots:
    void on_addFragmentPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::addFragmentCommentDialog *ui;
};

#endif // ADDFRAGMENTCOMMENTDIALOG_H

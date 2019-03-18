#ifndef ANALYSISFORM_H
#define ANALYSISFORM_H

#include <QWidget>

namespace Ui {
class analysisForm;
}

class analysisForm : public QWidget
{
    Q_OBJECT

public:
    explicit analysisForm(QWidget *parent = nullptr);
    ~analysisForm();

private:
    Ui::analysisForm *ui;
};

#endif // ANALYSISFORM_H

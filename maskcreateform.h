#ifndef MASKCREATEFORM_H
#define MASKCREATEFORM_H

#include <QWidget>

namespace Ui {
class maskCreateForm;
}

class maskCreateForm : public QWidget
{
    Q_OBJECT

public:
    explicit maskCreateForm(QWidget *parent = nullptr);
    ~maskCreateForm();

private:
    Ui::maskCreateForm *ui;
};

#endif // MASKCREATEFORM_H

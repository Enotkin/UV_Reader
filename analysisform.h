#ifndef ANALYSISFORM_H
#define ANALYSISFORM_H

#include <QWidget>
#include <QScopedPointer>
#include <QDebug>
#include <memory>

#include "addfragmentcommentdialog.h"
#include "fragmentinfo.h"
//#include "fragmentsmodel.h"
//#include "testmodel.h"

namespace Ui {
class analysisForm;
}

class AnalysisForm : public QWidget
{
    Q_OBJECT

public:
    explicit AnalysisForm(QWidget *parent = nullptr);
    void addIntervalComment();
    ~AnalysisForm();

private slots:
    void on_hideAnalysisPanelAction_triggered();

    void on_addIntervalCommentAction_triggered();

private:
    Ui::analysisForm *ui;

};

#endif // ANALYSISFORM_H
